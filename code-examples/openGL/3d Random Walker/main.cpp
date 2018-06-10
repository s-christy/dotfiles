#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int screen_width=800, screen_height=600;
float angle=0;
float dScale=1;
float rotSpeed=15;
float globScale=1;
GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
GLuint vbo_line_vertices, vbo_line_colors, ibo_line_elements;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_mvp;
GLuint program;
glm::vec3 camPos;

void printV(glm::vec3 v){
	printf("%f %f %f\n",v.x,v.y,v.z);
}

void init_cube(){
	GLfloat cube_vertices[]={-1.0,-1.0,1.0,1.0,-1.0,1.0,1.0,1.0,1.0,-1.0,1.0,1.0,-1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,-1.0,-1.0,1.0,-1.0,};
	glGenBuffers(1,&vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	//GLfloat cube_colors[]={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,};
	GLfloat cube_colors[]={0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5,0.5,0.5,0.5,0.5,0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5,0.5,0.5,0.5,0.5,};
	//GLfloat cube_colors[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	glGenBuffers(1,&vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	GLushort cube_elements[]={0,1,2,2,3,0,1,5,6,6,2,1,7,6,5,5,4,7,4,0,3,3,7,4,4,5,1,1,0,4,3,2,6,6,7,3,};
	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
}

void init_resources(){
	camPos=glm::vec3(0,.5,-3.);
	init_cube();

	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source =
		"attribute vec3 coord3d;"
		"attribute vec3 v_color;"
		"uniform mat4 mvp;"
		"varying vec3 f_color;"
		""
		"void main(void) {"
		"  gl_Position = mvp * vec4(coord3d, 1.0);"
		"  f_color = v_color;"
		"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
		"varying vec3 f_color;"
		"void main(void) {"
		"  gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, 1);"
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);

	const char* attribute_name;
	attribute_name = "coord3d";
	attribute_coord3d = glGetAttribLocation(program, attribute_name);
	attribute_name = "v_color";
	attribute_v_color = glGetAttribLocation(program, attribute_name);
	const char* uniform_name;
	uniform_name = "mvp";
	uniform_mvp = glGetUniformLocation(program, uniform_name);
}

void drawCube(glm::vec3 pos,glm::vec3 axis,float scale,int style){
	glLineWidth(1);
	glm::mat4 model = glm::mat4(1.0f);
	model= glm::translate(model, camPos);
	model= glm::rotate(model, glm::radians(angle), axis);
	model= glm::scale(model, glm::vec3(scale));
	model= glm::translate(model, pos);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width/screen_height, 0.1f, 10.0f);
	glm::mat4 mvp = projection * view * model;
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glVertexAttribPointer(attribute_coord3d,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(attribute_v_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glVertexAttribPointer(attribute_v_color,3,GL_FLOAT,GL_FALSE,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(style, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_v_color);
}

void drawLine(glm::vec3 start,glm::vec3 end,float scale,int style){

	glLineWidth(1);
	//line
	GLfloat line_vertices[]={start.x,start.y,start.z,end.x,end.y,end.z};
	glGenBuffers(1,&vbo_line_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_STATIC_DRAW);

	//GLfloat line_colors[]={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,};
	GLfloat line_colors[]={0.0,0.0,0.0,0.0,0.0,0.0};
	glGenBuffers(1,&vbo_line_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_colors), line_colors, GL_STATIC_DRAW);

	GLushort line_elements[]={0,1,0,1,0,1};
	glGenBuffers(1, &ibo_line_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_line_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_elements), line_elements, GL_STATIC_DRAW);

	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_BLEND);

	glm::mat4 model = glm::mat4(1.0f);
	model= glm::translate(model, camPos);
	model= glm::rotate(model, glm::radians(angle), glm::vec3(0,1,0));
	model= glm::scale(model, glm::vec3(scale));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width/screen_height, 0.1f, 10.0f);
	glm::mat4 mvp = projection * view * model;
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_vertices);
	glVertexAttribPointer(attribute_coord3d,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(attribute_v_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line_colors);
	glVertexAttribPointer(attribute_v_color,3,GL_FLOAT,GL_FALSE,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_line_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(style, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_v_color);
}

glm::vec3 normalize(glm::vec3 v){
	float scale=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	v.x/=scale;
	v.y/=scale;
	v.z/=scale;
	return v;
}

glm::vec3 add(glm::vec3 a,glm::vec3 b){
	glm::vec3 v=glm::vec3(0);
	v.x=a.x+b.x;
	v.y=a.y+b.y;
	v.z=a.z+b.z;
	return v;
}

void randomWalk(){
	srand(0);
	glm::vec3 pos=glm::vec3(0);
	//pos.z=3;
	for(int i=0;i<10000;i++){
		//pos.x+=1./500.;
		pos.x+=(float)(rand()%3-1);
		pos.y+=(float)(rand()%3-1);
		pos.z+=(float)(rand()%3-1);
		//pos.z+=(float)(-rand()%2)/500.;
		drawCube(pos,glm::vec3(0,1,0),globScale*.01,GL_TRIANGLES);
	}
}

void render(SDL_Window* window) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawCube(glm::vec3(0),glm::vec3(0,1,0),globScale,GL_LINES);
	//drawCube(glm::vec3(0),glm::vec3(0,1,0),globScale,GL_TRIANGLES);
	randomWalk();
	SDL_GL_SwapWindow(window);
}

void onResize(int width, int height) {
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, screen_width, screen_height);
}

void free_resources(){
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo_cube_vertices);
	glDeleteBuffers(1, &vbo_cube_colors);
	glDeleteBuffers(1, &ibo_cube_elements);
	glDeleteBuffers(1, &vbo_line_vertices);
	glDeleteBuffers(1, &vbo_line_colors);
	glDeleteBuffers(1, &ibo_line_elements);
}

void mainLoop(SDL_Window* window) {
	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				return;
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				onResize(e.window.data1, e.window.data2);
			if (e.type == SDL_MOUSEMOTION){
				//angle+=e.motion.xrel*.5;
			}
			if (e.type == SDL_MOUSEMOTION && e.button.button==SDL_BUTTON(1)){
			}
			if (e.type == SDL_MOUSEMOTION && e.button.button==SDL_BUTTON(3)){
			}
			if (e.type == SDL_MOUSEWHEEL){
				globScale+=.01;
			}
			if (e.type == SDL_KEYDOWN){
				printf("%d\n",e.key.keysym.sym);
				switch(e.key.keysym.sym){
					case 113:
						return;
						break;
					case SDLK_ESCAPE:
						return;
						break;
					case 97://a
						angle+=10;
						break;
					case 115://s
						break;
					case 100://d
						angle-=10;
						break;
					case 119://w
						break;
				}
			}
		}
		render(window);
	}
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("BASE",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,screen_width, screen_height,SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	glewInit();
	init_resources();
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_NEVER);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mainLoop(window);
	free_resources();
	return EXIT_SUCCESS;
}

