//  SDL_Test
//
//  Created by Eric Biersner on 2/6/18.
//  Copyright © 2018 Eric Biersner. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"

int main(int argc, const char * argv[]) {

    Screen screen;

    if(!screen.init()){
        std::cout << "Error initializing SDL " << std::endl;
    }

    //loop of window
    
    
    while (true) {
        //Upadate particles
        //draw particles
        //check for messages/events
       if(!screen.processEvents()){
           break;
       }
    }


    screen.close();

    std::cout << "We are done " << std::endl;
    
    return 0;
    
}
