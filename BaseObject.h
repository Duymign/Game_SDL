#ifndef BaseObject_H
#define BaseObject_H
#include "graphics.h"

class BaseObject {
protected:
    SDL_Rect rect;
    SDL_Texture* object;

public:
    BaseObject();
    ~BaseObject();
    void setRect(const int& x, const int& y, const int& w, const int &h)
    {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }
    SDL_Rect getRect () const {
        return rect;
    }
    void setTexture(const char* fileName, Graphics &graphics)
    {
        object = graphics.loadTexture(fileName);
    }
    SDL_Texture* getTexture() const
    {
        return object;
    }
};
#endif // BaseObject_H
