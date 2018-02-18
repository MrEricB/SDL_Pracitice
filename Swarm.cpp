#include "Swarm.hpp"

Swarm::Swarm(){
    m_particales = new Partical[NUM_PARTICALS];
}

Swarm::~Swarm(){
    delete [] m_particales;
}

void Swarm::update(){
    for(int i = 0; i < Swarm::NUM_PARTICALS; i++){
        m_particales[i].update(); //update each partical location
    }
}