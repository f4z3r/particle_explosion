// Name         Swarm.cpp

#include "Swarm.hpp"

Swarm::Swarm(): m_time(0) {
    m_p_particles = new Particle[NPARTICLES];
}

Swarm::~Swarm() {
    delete[] m_p_particles;
}

void Swarm::update(int elapsed) {
    int interval = elapsed - m_time;

    for(int i=0; i<NPARTICLES; i++) {
        m_p_particles[i].update(interval);
    }

    m_time = elapsed;
}
