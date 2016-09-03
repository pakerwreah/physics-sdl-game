#include <iostream>
#include "object.h"
#include "compat.h"
#include "global.h"

using namespace std;

#define EVENT_FPS 300
#define VELO 1
#define VELO_MAX 10
#define GRAVITY 1
#define LAR 840
#define ALT 650
#define ELASTIC 0.3
#define FRICTION 3
#define ANGLE 3
#define TITLE "C++ SDL Game"

SDL_Renderer *renderer;

int main(int argc, char *argv[])
{
    setup();
    
    SDL_Event event;
    bool gameloop = true;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) ==-1)
    {
        printf("Error initializing SDL \n %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    else
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    SDL_Window *janela = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LAR, ALT, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(janela,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (!janela) {
        printf("Error initializing window");
        exit(1);
    }
    
    Object alien("alien.png");
    
    cout << TITLE << endl;
    
    while(gameloop)
    {
        int start = SDL_GetTicks();
        
        SDL_RenderClear(renderer);
        
        SDL_PollEvent(&event);
        
        if(event.type== SDL_QUIT|| event.key.keysym.sym == SDLK_ESCAPE)
            gameloop = false;
        
        float vx = alien.velx(), vy = alien.vely();
        
        bool keydown = false;
        
        const Uint8 *key = SDL_GetKeyboardState(NULL);
        
        if(key[SDL_SCANCODE_LEFT] && vx > -VELO_MAX) {
            vx -= VELO;
            keydown = true;
        }
        
        if(key[SDL_SCANCODE_RIGHT] && vx < VELO_MAX) {
            vx += VELO;
            keydown = true;
        }
        
        if(key[SDL_SCANCODE_UP] && vy > -VELO_MAX) {
            vy -= VELO + GRAVITY;
            keydown = true;
        }
        
        if(key[SDL_SCANCODE_DOWN] && vy < VELO_MAX) {
            vy += VELO;
            keydown = true;
        }
        
        bool ground = alien.y() + alien.height() >= ALT;
        
        if(ground || alien.y() <= 0) {
            if(vx > 0) {
                vx -= VELO * FRICTION;
                vx = vx > 0 ? vx : 0;
            } else if(vx < 0)
            {
                vx += VELO * FRICTION;
                vx = vx < 0 ? vx : 0;
            }
        }
        
        if(!ground)
            vy += GRAVITY;
        
        alien.velx(vx);
        alien.vely(vy);
        alien.angle(vx * ANGLE);
        alien.move();
        
        if(alien.x() < 0) {
            alien.x(0);
            alien.velx(-vx * ELASTIC);
        } else if(alien.x() + alien.width() > LAR) {
            alien.x(LAR - alien.width());
            alien.velx(-vx * ELASTIC);
        }
        
        if(alien.y() < 0) {
            alien.y(0);
            alien.vely(-vy * ELASTIC);
        } else if(alien.y() + alien.height() > ALT) {
            alien.y(ALT - alien.height());
            alien.vely(-vy * ELASTIC);
        }
        
        alien.draw();
        
        SDL_RenderPresent(renderer);
        
        if(1000.0/EVENT_FPS>SDL_GetTicks()-start)
            SDL_Delay(1000.0/EVENT_FPS-(SDL_GetTicks()-start));
    }
    
    return(EXIT_SUCCESS);
}
