#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include "circle.h"
#include <iostream>

using namespace circle;
using std::abs;

Circle::Circle(int x, int y, int radius, Uint32 color):
    x_(x), y_(y), radius_(radius), dx(0), dy(0), color(color) {}


void Circle::step(SDL_Window* window) {
    x_ += dx;
    y_ += dy;
    dy += GRAVITY;

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    if (x_ - radius_ < 0) {
        x_ = radius_;
        dx = -dx * LOSS_COEFF;
        if (abs(dx) < EPSILON) {
            dx = 0;
        }
    }
    if (x_ + radius_ > w) {
        x_ = w - radius_;
        dx = -dx * LOSS_COEFF;
        if (abs(dx) < EPSILON) {
            dx = 0;
        }
    }
    if (y_ - radius_ < 0) {
        y_ = radius_;
        dy = -dy * LOSS_COEFF;
    }
    if(y_ + radius_ > h - 1) {
        y_ = h - radius_;
        dy = -dy * LOSS_COEFF;
        if (abs(dy) < EPSILON) {
            dy = 0;
        }
    }
}

void Circle::render(SDL_Window* window, SDL_Surface* surface) {
    int low_x = x_ - radius_;
    int low_y = y_ - radius_;
    int high_x = x_ + radius_;
    int high_y = y_ + radius_;

    int radius_squared = radius_ * radius_;

    for (int i = low_x; i < high_x; i++) {
        for (int j = low_y; j < high_y; j++) {
            int dist = (i - x_)*(i - x_) + (j - y_)*(j - y_);
            if (dist < radius_squared) {
                SDL_Rect pixel = SDL_Rect({i, j, 1, 1});
                SDL_FillRect(surface, &pixel, this->color);
            }
        }
    }
}

void Circle::nudge(double nudge_amount, circle::Direction dir) {
    switch (dir) {
        case DOWN:
            dy += nudge_amount;
            break;
        case UP:
            dy -= nudge_amount;
            break;
        case LEFT:
            dx -= nudge_amount;
            break;
        case RIGHT:
            dx += nudge_amount;
            break;
    }
}
