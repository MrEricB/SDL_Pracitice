#include "Partical.hpp"
#include <math.h> //needed for M_PI, maybe better to use cmath instead of math.h, but quick fix since cmaht doesnt have PI constant

Partical::Partical() {
    //fix starting postition
    m_xPos = 0;
    m_yPos = 0;

    //radnom direction
    m_direction = (2 * M_PI * rand())/RAND_MAX; //angle
    m_speed = (0.01 * rand())/RAND_MAX; //speed
}

Partical::~Partical(){

}

void Partical::update(){
    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    m_xPos += xspeed;
    m_yPos += yspeed;

    // //keep particals from moving off edge of screen
    // if(m_xPos < -1 || m_xPos >= 1){
    //     m_xspeed = -m_xspeed;
    // }
    // if(m_yPos < -1 || m_yPos >= 1){
    //     m_yspeed = -m_yspeed;
    // }
}