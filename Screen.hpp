#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL2/SDL.h>
#include <iostream>

class Screen {
public: 
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HIEGHT = 600;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer;

public:
    Screen();
    bool init();
    bool processEvents();
    void close();



};
#endif