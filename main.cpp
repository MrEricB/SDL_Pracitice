#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"

#include <cstdlib>

int main(int argc, const char * argv[]) {

    Screen screen;

    if(!screen.init()){
        std::cout << "Error initializing SDL " << std::endl;
    }

    //loop for window
    while (true) {
        //Upadate particles
        //draw particles
        for(int y=0; y < Screen::SCREEN_HIEGHT; y++){
            for(int x=0; x < Screen::SCREEN_WIDTH; x++){
                //geerate random value for each RGR
                int r = rand()%255;
                int g = rand()%255;
                int b = rand()%255;
                // screen.setPixel(x, y, 128, 0, 255);
                screen.setPixel(x, y, r,g,b); //creates a cool static TV screen.
            }
        }

        screen.setPixel(400, 300, 255, 255, 255);

        //Draw the screen
        screen.update();

        //check for messages/events
       if(!screen.processEvents()){
           break;
       }
    }


    screen.close();

    std::cout << "We are done " << std::endl;
    
    return 0;
    
}
