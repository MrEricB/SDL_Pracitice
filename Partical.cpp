#include "Partical.hpp"
#include <math.h> //needed for M_PI, maybe better to use cmath instead of math.h, but quick fix since cmaht doesnt have PI constant

Partical::Partical() {
    init();
}

Partical::~Partical(){

}

void Partical::init(){
    //fix starting postition
    m_xPos = 0;
    m_yPos = 0;

    //radnom direction
    m_direction = (2 * M_PI * rand())/RAND_MAX; //angle
    m_speed = (0.035 * rand())/RAND_MAX; //speed

    m_speed *= m_speed; //makes particals at the edge look further away, ie makes explosion look more natural
}

void Partical::update(int change){
    m_direction += change*0.0005; //spin effect on the particals, smaller means a more subtle spin, too small and it colapes in on its self


    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);


    //*change makes amount the partical moves is porportional to the amount of time since last time partical moved. ie help with slower systems?
    //should make speeds constant regardlest of system.
    m_xPos += xspeed*change;
    m_yPos += yspeed*change;


    //check if partical is off the screen
    // if(m_xPos < -1 || m_xPos > 1 || m_yPos < -1 || m_yPos > 1){
    //     init();
    // }


    // re initialize some particals
    if(rand() < RAND_MAX/100){
        init();
    }
}