#include "Display.h"
#include <glew\GL\glew.h>
Display::Display(int width, int height, const std::string title) {
	//init
	std::cout << title;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr,
			"\nUnable to initialize SDL:  %s\n",SDL_GetError());}
	//init feilds
	is_closed = false;


	//set attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);//2^8 shades of red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);//2^8 shades of green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);//2^8 shades of blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);//2^8 shades of opacity
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);//total bits used per pixel= sum of ones above
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//sets up a second window that is not displayed
	//openGLwill write on the window we cant see then will swap with the window we can see
												//create a new window
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!m_window) {
		std::cerr << "sdl failed to initialize window"<<SDL_GetError() << std::endl;
	}
	m_glContext = SDL_GL_CreateContext(m_window);

	//begin using glew here
	GLenum status = glewInit();//status sees if everything was set up ok
	if (status != GLEW_OK) {
		std::cerr << "glew failed to initialize" << std::endl;
	}

}

Display::~Display() {
	//destroy
	//destroy context and window in opposite order like stack
	SDL_GL_DeleteContext(m_window);
	SDL_DestroyWindow(m_window);

	SDL_Quit();


}

void Display::update() {
	//swap buffer and display windows
	SDL_GL_SwapWindow(m_window);

	SDL_Event event;

	while (SDL_PollEvent(&event)) {//this is like a foreach of all current events
		if (event.type == SDL_QUIT) {
			is_closed = true;
		}
	}
}

bool Display::isClosed() {

	return is_closed;
}

void Display::clear(float r, float g, float b, float a){
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}