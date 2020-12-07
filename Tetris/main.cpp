#include <cstdlib>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <SDL2/SDL.h>

using namespace std;

namespace program {
    namespace rnd {
        //default_random_engine rng;

        int randInt(int mn, int mx) {
            //uniform_int_distribution<int> d(mn, mx);
            //return d(rng);
            int n = mx - mn + 1;
            return mn + rand() % n;
        }
    };

    SDL_Window *win = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Texture *tex = nullptr;
    double posX = 10, posY = 10;
    double vx = 0, vy = 0;

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();

        win = SDL_CreateWindow("Tetrys [nic11]", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        if (win == nullptr) throw SDL_GetError();
        
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) throw SDL_GetError();

        SDL_Surface *surf = SDL_LoadBMP("res/hello.bmp");
        if (surf == nullptr) throw SDL_GetError();
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        if (tex == nullptr) throw SDL_GetError();
        SDL_FreeSurface(surf);
    }

    void quit() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);

        SDL_Quit();
        exit(0);
    }

    void onKeyboardEvent(const SDL_KeyboardEvent &evt) {
        switch (evt.keysym.scancode) {
        case SDL_SCANCODE_W:
            if (evt.type == SDL_KEYDOWN) vy = -1000;
            else vy = 0;
            break;
        case SDL_SCANCODE_A:
            if (evt.type == SDL_KEYDOWN) vx = -1000;
            else vx = 0;
            break;
        case SDL_SCANCODE_S:
            if (evt.type == SDL_KEYDOWN) vy = 1000;
            else vy = 0;
            break;
        case SDL_SCANCODE_D:
            if (evt.type == SDL_KEYDOWN) vx = 1000;
            else vx = 0;
            break;
        default:
            break;
        }
    }

    void onEvent(const SDL_Event &evt) {
        switch (evt.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            onKeyboardEvent(evt.key);
            break;
        case SDL_QUIT:
            quit();
            break;
        default:
            //cout << "Unhandled event #" << evt.type << "\n";
            break;
        }
    }
    
    void loopTick(double deltaTime) {
        posX += vx * deltaTime;
        posY += vy * deltaTime;
    }

    void loopDraw(double deltaTime) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect dest;
        dest.x = (int)posX;
        dest.y = (int)posY;
        dest.w = 100;
        dest.h = 100;
        SDL_RenderCopy(renderer, tex, nullptr, &dest);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, nullptr);

        //cout << 1 / deltaTime << " FPS\n";
        double wait = max(0., 1. / 100 - deltaTime);
        //cout << "wait = " << wait << "\n";
        SDL_Delay(wait * 1000);

        SDL_RenderPresent(renderer);
    }
};

int main() {
    cout << "Tetris [nic11]\n";
    cout << "Starting\n";

    try {
        program::init();
        auto timeOld = chrono::steady_clock::now();
        while (1) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                program::onEvent(e);
            }

            auto timeNow = chrono::steady_clock::now();
            double deltaTime = (timeNow - timeOld).count() / 1e9;
            timeOld = timeNow;

            program::loopTick(deltaTime);
            program::loopDraw(deltaTime);
        }
    } catch (const char *s) {
        cout << "Error: " << s << "\n";
        return 1;
    }

    cout << "Warning: Unreachable code reached!!!\n";
}
