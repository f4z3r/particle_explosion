// Name     Screen.cpp

#include "Screen.hpp"

namespace jhb {

Screen::Screen():
    m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL),
    m_buffer2(NULL){
}

bool Screen::init(const char* title) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    // Initialise window
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(m_window == NULL) {
        SDL_Quit();
        return false;
    }

    // Initialise renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_renderer == NULL) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    // Initialise texture
    m_texture = SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_STATIC,
                                  SCREEN_WIDTH, SCREEN_HEIGHT);
    if(m_texture == NULL) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    // Initialise buffer and fill with black
    m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;
}

bool Screen::process_events() {
    while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                return false;
            }
        }
    return true;
}

void Screen::set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xff;

    m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1,
                      SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::close() {
    delete[] m_buffer1;
    delete[] m_buffer2;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Screen::gaussian_blur() {
    Uint32* tmp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = tmp;

    for(int y=0; y<SCREEN_HEIGHT; y++) {
        for(int x=0; x<SCREEN_WIDTH; x++) {
            double red_tot = 0;
            double green_tot = 0;
            double blue_tot = 0;

            for(int row=0; row<=2; row++) {
                for(int col=0; col<=2; col++) {
                    int current_x = x + col - 1;
                    int current_y = y + row - 1;

                    if(current_x >= 0 && current_x < SCREEN_WIDTH &&
                       current_y >= 0 && current_y < SCREEN_HEIGHT) {
                        Uint32 color = m_buffer2[current_y*SCREEN_WIDTH +
                                                 current_x];
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        red_tot += red * m_blur[row][col];
                        green_tot += green * m_blur[row][col];
                        blue_tot += blue * m_blur[row][col];
                    }
                }
            }

            Uint8 red = red_tot;
            Uint8 green = green_tot;
            Uint8 blue = blue_tot;

            set_pixel(x, y, red, green, blue);
        }
    }
}

} // namespace jhb
