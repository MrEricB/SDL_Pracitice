#include "Screen.hpp"

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL){

}

bool Screen::init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        // std::cout << "SDL could not initialize. SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create the window 
    m_window = SDL_CreateWindow("Partical Simulator",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HIEGHT, SDL_WINDOW_SHOWN);
    
    //check if window creation worked
    if(m_window == NULL){
        SDL_Quit();
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HIEGHT);

    if(m_renderer == NULL){
        // std::cout << "Could not create renderer " << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    if(m_texture == NULL){
        // std::cout << "Could not create texture " << std::endl;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    //array of all the pixels
    m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HIEGHT];

    
    memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HIEGHT*sizeof(Uint32)); // set all pixels to black

    //set one pixal at a time to WSU crimson
    for(int i = 0; i< SCREEN_WIDTH*SCREEN_HIEGHT; i++){
        m_buffer[i] = 0x981E32FF;
    }

    SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32)); 
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);

    return true;
}

bool Screen::processEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){ //i.e. if hit close 'X' button in corner
                return false;
        }
    }

    return true;
}

void Screen::close(){
    delete [] m_buffer;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}