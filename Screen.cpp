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

    return true;
}


void Screen::update(){
    SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32)); 
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    Uint32 color = 0;

    //bit shifting to add RBGA values to color.
    color += red;
    color <<= 8;
    color += green;
    color <<= 8; 
    color += blue;
    color <<= 8;
    color += 0xFF; //the alpha

    //coverting x,y quardinat to an index. y*screen_width will give the colum, and x will give the row.
    //the result is an index of the specific pixal at (x,y)
    m_buffer[(y*SCREEN_WIDTH) + x] = color;
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

