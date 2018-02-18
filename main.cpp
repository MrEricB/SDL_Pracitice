#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <time.h>
// #include <cmath>
#include "Screen.hpp"
#include "Swarm.hpp"

int main(int argc, const char * argv[]) {

    srand(time(NULL));

    Screen screen;

    if(!screen.init()){
        std::cout << "Error initializing SDL " << std::endl;
    }

    Swarm swarm;

    //loop for window
    while (true) {
        //Upadate particles
        //draw particles

        int timeElapsed = SDL_GetTicks(); //time in milliseconds since start
        screen.clearScreen();
        // unsigned char used to make sure the value stays within 255;
        unsigned char green = (1 + sin(timeElapsed * 0.001)) * 128; // *0.001 need to make jumps smoother
        unsigned char red = (1 + sin(timeElapsed * 0.002)) * 128;
        unsigned char blue = (1 + sin(timeElapsed * 0.003)) * 128;

        const Partical * const pParticals = swarm.getParticals();

        swarm.update(); //update all the particals
    

        for(int i = 0; i < Swarm::NUM_PARTICALS; i++){
            Partical partical = pParticals[i]; // get individual partical one by one.

            int x = (partical.m_xPos + 1) * Screen::SCREEN_WIDTH/2; //make middle of screen the center of the x,y plane
            int y = (partical.m_yPos + 1) * Screen::SCREEN_HIEGHT/2;

            screen.setPixel(x, y, red, green, blue);
        }

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
