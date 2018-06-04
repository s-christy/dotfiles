#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int screen_width=800, screen_height=600;
GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
GLuint program;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_mvp;
float angle=0;

int init_resources(){
	GLfloat cube_vertices[]={-1.0,-1.0,1.0,1.0,-1.0,1.0,1.0,1.0,1.0,-1.0,1.0,1.0,-1.0,-1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,-1.0,-1.0,1.0,-1.0,};
	glGenBuffers(1,&vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

	//GLfloat cube_colors[]={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,};
	GLfloat cube_colors[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	glGenBuffers(1,&vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

	GLushort cube_elements[]={0,1,2,2,3,0,1,5,6,6,2,1,7,6,5,5,4,7,4,0,3,3,7,4,4,5,1,1,0,4,3,2,6,6,7,3,};
	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

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
		"  gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, .5);"
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

	return 1;
}

void onIdle() {
	glm::vec3 axis(0, 1, 0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*screen_width/screen_height, 0.1f, 10.0f);

	glm::mat4 mvp = projection * view * model * anim;

	glUseProgram(program);
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
	glutPostRedisplay();
}

void drawCube(int style){
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glVertexAttribPointer(attribute_coord3d,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(attribute_v_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glVertexAttribPointer(attribute_v_color,3,GL_FLOAT,GL_FALSE,0,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(style, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);//

	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_v_color);

}

void onDisplay(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord3d);
	//drawCube(GL_TRIANGLES);
	drawCube(GL_LINES);
	glutSwapBuffers();
}

void onReshape(int width, int height) {
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, screen_width, screen_height);
}

void free_resources(){
	glDeleteProgram(program);
	glDeleteBuffers(1, &vbo_cube_vertices);
	glDeleteBuffers(1, &vbo_cube_colors);
	glDeleteBuffers(1, &ibo_cube_elements);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'q':
			glutLeaveMainLoop();
			break;
		case 27:
			glutLeaveMainLoop();
			break;
	}
}

void keyboardSpecial(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			angle-=10;
			break;
		case GLUT_KEY_RIGHT:
			angle+=10;
			break;
	}
}

void motion(int x, int y){
	angle=x;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow("BASE");

	glewInit();

	init_resources();
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);

	//https://en.wikibooks.org/wiki/Guide_to_Game_Development/Rendering_and_Game_Engines/OpenGL/GLUT/Handling_input
	glutSpecialFunc(keyboardSpecial);
	glutKeyboardFunc(keyboard);
	//glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);

	glutIdleFunc(onIdle);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();

	free_resources();
	return 0;
}
