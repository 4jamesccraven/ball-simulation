#include <SDL2/SDL.h>

namespace circle {
    enum Direction {
        UP, DOWN, LEFT, RIGHT
    };
}

class Circle {
    public:
        Circle(int x, int y, int radius, Uint32 color = 0xffffffff);
        void render(SDL_Window* window, SDL_Surface* surface);
        void step(SDL_Window* window);
        void nudge(double nudge_amount, circle::Direction dir);
    protected:
        const double GRAVITY = 0.5;
        const double LOSS_COEFF = 0.5;
        const double EPSILON = 2.5;
        int x_;
        int y_;
        int radius_;
        double dx;
        double dy;
        Uint32 color;
};
