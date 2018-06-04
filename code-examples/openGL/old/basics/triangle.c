#include <stdlib.h>
#include <GL/glew.h>
#include <SDL.h>

GLuint program;
GLfloat triangle_vertices[] = {0.0,1.0,-1.0,-1.0,1.0,-1.0,};
GLint attribute_coord2d;

void init_resources(void) {
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source =
		"#version 120\n"
		"attribute vec2 coord2d;                  "
		"void main(void) {                        "
		"  gl_Position = vec4(coord2d, 0.0, 1.0); "
		"}";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
		"#version 120\n"
		"void main(void) {        "
		"  gl_FragColor[0] = gl_FragCoord.x/640.0; "
		"  gl_FragColor[1] = 0.0; "
		"  gl_FragColor[2] = 1.0; "
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);

	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
}

void render(SDL_Window* window) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord2d);
	glVertexAttribPointer(attribute_coord2d,2,GL_FLOAT,GL_FALSE,0,triangle_vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attribute_coord2d);
	SDL_GL_SwapWindow(window);
}

void mainLoop(SDL_Window* window) {
	while (1) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				return;
			if (ev.type==SDL_KEYDOWN){
				return;
			}
		}
		render(window);
	}
}

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("BASE",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640, 480,SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);SDL_GL_CreateContext(window);
	glewInit();
	init_resources();
	mainLoop(window);
	return EXIT_SUCCESS;
}
