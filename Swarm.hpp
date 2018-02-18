#ifndef SWARM_HPP
#define SWARM_HPP

#include "Partical.hpp"

class Swarm {
public:
    const static int NUM_PARTICALS = 1500; //Total number of particals on the screen
private:
Partical * m_particales; 

public: 
    Swarm();
    virtual ~Swarm();

    const Partical * const getParticals(){ return m_particales;} //const point to const partical retur type
    void update();

};

#endif