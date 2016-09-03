#include "object.h"
#include "global.h"

Object::Object(){}
Object::~Object(){
    SDL_DestroyTexture(texture);
}

Object::Object(const char *file, float x, float y)
{
    xy(x, y);
    load(IMG_Load(file));
}

float Object::x() { return _x; }
float Object::y() { return _y; }
float Object::velx() { return _velx; }
float Object::vely() { return _vely; }
int Object::width() { return _width; }
int Object::height() { return _height; }
double Object::angle() { return _angle; }

void Object::x(float x)
{
    rect.x = _x = x;
}

void Object::y(float y)
{
    rect.y = _y = y;
}

void Object::width(int width)
{
    rect.w = _width = width;
}

void Object::height(int height)
{
    rect.h = _height = height;
}

void Object::velx(float velx)
{
    _velx = velx;
}

void Object::vely(float vely)
{
    _vely = vely;
}

void Object::xy(float x, float y)
{
    this->x(x);
    this->y(y);
}

void Object::angle(double angle) {
    _angle = angle;
}

void Object::move()
{
    x(x() + velx());
    y(y() + vely());
}

void Object::draw()
{
    if(angle())
        SDL_RenderCopyEx(renderer,texture,NULL,&rect,angle(),NULL,SDL_FLIP_NONE);
    else
        SDL_RenderCopy(renderer,texture,NULL,&rect);
}

void Object::draw(float x, float y)
{
    xy(x, y);
    draw();
}

void Object::load(SDL_Surface *temp)
{
    texture = NULL;
    if(temp)
    {
        width(temp->w);
        height(temp->h);
        texture = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_FreeSurface(temp);
    }
}

enum COLLISION Object::colide(Object *obj)
{
    int t = obj->y() + obj->height() - y(); //top
    int r = x()+width() - obj->x(); //right
    int d = y()+height() - obj->y(); //down
    int l = obj->x() + obj->width() - x(); //left
    if(t>=0 && r>=0 && d>=0 && l>=0)
    {
        if((obj->vely()<0 && l>d && r>d) || (obj->vely()>0 && l>t && r>t))
            return COLLISION_VERTICAL;
        else
            return COLLISION_HORIZONTAL;
    }

    return COLLISION_INEXISTENT;
}
