// Name         Swarm.hpp

#ifndef SWARM_HPP_
#define SWARM_HPP_

#include "Particle.hpp"

class Swarm{
public:
    Swarm();
    ~Swarm();

    const Particle* const get_particles() {return m_p_particles;}
    void update(int elapsed);

    const static int NPARTICLES = 6000;

private:
    Particle* m_p_particles;
    int m_time;

};

#endif // SWARM_HPP_
