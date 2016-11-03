#ifndef DISPLAY_H
#define DISPLAY_H


#include <iostream>
#include <SDL2\SDL.h>
#include <string>


class Display{
public:
	Display(int width, int height, const std::string title);
	virtual ~Display();
	bool isClosed();
	void update();
	void clear(float r, float b, float g, float a);
protected:
private:
	bool is_closed;
	Display(const Display& other) {}
	void operator=(const Display& other){}
    SDL_Window* m_window;

    SDL_GLContext m_glContext;//	OPenGL context makes OS give up control of window and allows GPU to write to it

};






#endif //DISPLAY_H
