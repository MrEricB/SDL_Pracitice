#include "Partical.hpp"


Partical::Partical(){
    //set x, y to random number [-1,1]
    m_xPos = (2.0 * rand())/RAND_MAX - 1;
    m_yPos = (2.0 * rand())/RAND_MAX - 1;

    m_xspeed = 0.01 * (((2.0 * rand())/RAND_MAX) - 1); // [0,1];
    m_yspeed = 0.01 * (((2.0 * rand())/RAND_MAX) - 1);
}

Partical::~Partical(){

}

void Partical::update(){
    m_xPos += m_xspeed;
    m_yPos += m_yspeed;

    //keep particals from moving off edge of screen
    if(m_xPos < -1 || m_xPos >= 1){
        m_xspeed = -m_xspeed;
    }
    if(m_yPos < -1 || m_yPos >= 1){
        m_yspeed = -m_yspeed;
    }
    

}