#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2_image/SDL_image.h>

enum COLLISION {COLLISION_HORIZONTAL,COLLISION_VERTICAL,COLLISION_INEXISTENT};

class Object
{
    float _x, _y;
    int _width, _height;
    float _velx, _vely;
    double _angle = 0;
    SDL_Rect rect;
    SDL_Texture *texture;

public:
    Object(const char *file, float x=0, float y=0);
    ~Object();

    enum COLLISION colide(Object *obj);
    
    void move();
    
    float x();
    float y();
    int width();
    int height();
    float velx();
    float vely();
    double angle();
    
    void x(float x);
    void y(float y);
    void xy(float x, float y);
    void velx(float velx);
    void vely(float vely);
    void width(int width);
    void height(int height);
    void angle(double angle);
    
    void draw(float x, float y);
    void draw();

protected:
    Object();
    void load(SDL_Surface *temp);
};

#endif // OBJECT_H
