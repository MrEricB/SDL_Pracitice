#include "Partical.hpp"
#include <cstdlib>

Partical::Partical(){
    //set x, y to random number [-1,1]
    m_xPos = (2.0 * rand())/RAND_MAX - 1;
    m_yPos = (2.0 * rand())/RAND_MAX - 1;
}

Partical::~Partical(){

}