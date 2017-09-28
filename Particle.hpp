// Name         Particle.hpp

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

struct Particle {
    Particle();
    ~Particle();

    void update(int interval);
    void init();

    double m_x;
    double m_y;

private:
    double m_speed;
    double m_direction;
};

#endif // PARTICLE_HPP_
