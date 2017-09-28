// Name         sdl_basic.cpp

#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Screen.hpp"
#include "Swarm.hpp"
using namespace std;

int main() {

    srand(time(NULL));

    jhb::Screen screen;

    if(screen.init("Particle Fire Explosion") == false) {
        cout << "Error initialising SDL." << endl;
    }

    Swarm swarm;

    const int SCREEN_RANGE = min(jhb::Screen::SCREEN_WIDTH / 2,
                                 jhb::Screen::SCREEN_HEIGHT / 2);

    while(true) {
        // Update particles
        int elapsed = SDL_GetTicks();
        swarm.update(elapsed);

        // Draw particles
        unsigned char red = (1 + sin(elapsed * 0.0003)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.0004)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.0002)) * 128;

        const Particle* const p_particles = swarm.get_particles();
        for(int i=0; i<Swarm::NPARTICLES; i++) {
            int x = p_particles[i].m_x * SCREEN_RANGE + \
                    jhb::Screen::SCREEN_WIDTH / 2;
            int y = p_particles[i].m_y * SCREEN_RANGE + \
                    jhb::Screen::SCREEN_HEIGHT / 2;

            screen.set_pixel(x, y, red, green, blue);
        }

        screen.gaussian_blur();

        // Draw the screen
        screen.update();

        // Check for messages/events
        if(screen.process_events() == false) {
            break;
        }
    }

    screen.close();

    return 0;
}
