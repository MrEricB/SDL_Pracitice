#include "Swarm.hpp"

Swarm::Swarm(){
    m_particales = new Partical[NUM_PARTICALS];
}

Swarm::~Swarm(){
    delete [] m_particales;
}