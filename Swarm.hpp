#ifndef SWARM_HPP
#define SWARM_HPP

#include "Partical.hpp"

class Swarm {
public:
    const static int NUM_PARTICALS = 2500;
private:
Partical * m_particales; 

public: 
    Swarm();
    virtual ~Swarm();

    const Partical * const getParticals(){ return m_particales;} //const point to const partical retur type
    void update();

};

#endif