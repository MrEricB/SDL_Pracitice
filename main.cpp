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

    //used in widow loop to help determin the center of the screen
    const int centerX = Screen::SCREEN_WIDTH/2;
    const int centerY = Screen::SCREEN_HIEGHT/2;

    //loop for window
    while (true) {
        //Upadate particles
        //draw particles

        int timeElapsed = SDL_GetTicks(); //time in milliseconds since start

        // screen.clearScreen();



        // unsigned char used to make sure the value stays within 255;
        unsigned char green = (1 + sin(timeElapsed * 0.001)) * 128; // *0.001 need to make jumps smoother
        unsigned char red = (1 + sin(timeElapsed * 0.002)) * 128;
        unsigned char blue = (1 + sin(timeElapsed * 0.003)) * 128;

        const Partical * const pParticals = swarm.getParticals();

        swarm.update(timeElapsed); //updates all the particals

        for(int i = 0; i < Swarm::NUM_PARTICALS; i++){
            Partical partical = pParticals[i]; // get individual partical

            /*
            make middle of screen the center of the x,y plane
            becasuse screen is rectagle, this here is causeing oval explosion rather than circular
            basically we have two ranges we are using to map partical to screen.
            too fix, only use SCREEN_WIDTH
            then to start in the middle. of the screen, shift to top by removing m_ypos +1 then add half screen height, to shift correctl to the middle of the screen.
            */
            //set particals x, y location
            int x = (partical.m_xPos + 1) * centerX; 
            int y = partical.m_yPos * centerX + centerY;

            //color the partical, at the current x, y location
            screen.setPixel(x, y, red, green, blue);
        }

        /********** Replaces screen.clearScreen() above ************/
        screen.boxBlur(); //blur partical movemnet


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
