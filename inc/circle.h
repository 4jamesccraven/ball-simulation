#include <SDL2/SDL.h>

typedef unsigned int uint ;

namespace circle {
    enum Direction {
        UP, DOWN, LEFT, RIGHT
    };
}

class Circle {
    public:
        Circle(int x, int y, int radius, Uint32 color = 0xffffffff);
        void render(SDL_Window* window, SDL_Surface* surface);
        void nudge(uint nudge_amount, circle::Direction dir);
    protected:
        const int GRAVITY = 1;
        int x_;
        int y_;
        int radius_;
        int dx;
        int dy;
        Uint32 color;
};
