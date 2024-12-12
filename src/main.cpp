#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "circle.h"

const int WIDTH = 1000;
const int HEIGHT = 800;
const int FPS = 1000 / 60;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Bouncy Ball",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0
    );

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    bool application_running = true;
    SDL_Event event;

    Circle ball(WIDTH / 2, HEIGHT / 2, 50);
    SDL_Rect background({0, 0, WIDTH, HEIGHT});

    ball.nudge(50, circle::Direction::RIGHT);

    double nudge_amt = 10.0;
    while (application_running) {
        Uint32 frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    application_running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        application_running = false;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            ball.nudge(nudge_amt, circle::Direction::UP);
                            break;
                        case SDLK_DOWN:
                            ball.nudge(nudge_amt, circle::Direction::DOWN);
                            break;
                        case SDLK_LEFT:
                            ball.nudge(nudge_amt, circle::Direction::LEFT);
                            break;
                        case SDLK_RIGHT:
                            ball.nudge(nudge_amt, circle::Direction::RIGHT);
                            break;
                    }
            }
        }

        ball.step(window);

        SDL_FillRect(surface, &background, 0x00000000);
        ball.render(window, surface);

        SDL_UpdateWindowSurface(window);

        Uint32 frame_end = SDL_GetTicks() - frame_start;
        if (frame_end < FPS) {
            SDL_Delay(FPS - frame_end);
        }
    }
}
