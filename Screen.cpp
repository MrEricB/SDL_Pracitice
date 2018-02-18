#include "Screen.hpp"

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){

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
    m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HIEGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HIEGHT];

    
    memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HIEGHT*sizeof(Uint32)); // set all pixels to black
    memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HIEGHT*sizeof(Uint32));

    return true;
}


//SDL methods to draw to the screen
void Screen::update(){
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32)); 
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

//set pixal color,
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    
    //check if partical is off the screen , if is don't draw it
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HIEGHT){ //not a very efficient way to check if pixal is off screen
        // don't render pixals that are not on the screen
        return;
    } 
    
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
    //set the individual pixal's color
    m_buffer1[(y*SCREEN_WIDTH) + x] = color;
}

//user exits the simulation
bool Screen::processEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){ //i.e. if hit close 'X' button in corner
                return false;
        }
    }

    return true;
}

//free memory when the sim is over
void Screen::close(){
    delete [] m_buffer1;
    delete [] m_buffer2;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

// // clear the screen of previous partical, ie where the partical use to be
// void Screen::clearScreen(){
//     memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HIEGHT*sizeof(Uint32)); //re-set all pixals to black
//     memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HIEGHT*sizeof(Uint32));
// }

void Screen::boxBlur(){
    // swap buffers so pixal info is in buffer2 and then drawing to buffer1.
    Uint32 *temp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = temp;

    for(int y = 0; y < SCREEN_HIEGHT; y++){
        for(int x = 0; x < SCREEN_WIDTH; x++){

            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            
            for(int row = -1; row<=1; row++){
                for(int col = -1; col<=1; col++){
                    int currentX = x + col;
                    int currentY = y + row;

                    //check if pixal is on screen
                    if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HIEGHT){
                        Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX]; //from x,y to array index.

                        //get componets out of this color
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;
                        // unsigned char red = (color & 0xFF000000) >> 24;
                        // unsigned char green = (color & 0x00FF0000) >> 16;
                        // unsigned char blue = (color & 0x0000FF00) >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }

                }
            } //end inner nested for loops, to get 9 pixals for an average.

            Uint8 red = redTotal/9;
            Uint8 green = greenTotal/9;
            Uint8 blue = blueTotal/9;

            setPixel(x, y, red, green, blue);

        }
    }
}

