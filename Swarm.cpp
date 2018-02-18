#include "Swarm.hpp"

Swarm::Swarm(){
    lastRun = 0;
    m_particales = new Partical[NUM_PARTICALS];
}

Swarm::~Swarm(){
    delete [] m_particales;
}

void Swarm::update(int timeElapsed){
    int change = timeElapsed - lastRun;

    for(int i = 0; i < Swarm::NUM_PARTICALS; i++){
        m_particales[i].update(change); //update each partical location
    }

    lastRun = timeElapsed;
}