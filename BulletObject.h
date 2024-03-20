#ifndef _BulletObject_H
#define _BulletObject_H

#include "BaseObject.h"
#include "defs.h"

class BulletObject : public BaseObject
{
private:

    bool ismove;
    int bullet_status;

public:
    BulletObject();
    ~BulletObject();
    void setTexture(SDL_Texture* bull){object = bull;}
    void setStatus(const int& status)
    {
        bullet_status = status;
    }
    void setRect(const int& x, const int& y);

    bool isMoving()
    {
        return ismove;
    }

    void setmove(bool b)
    {
        ismove = b;
    }
    void MoveBullet(const int& x_border, const int &y_border);

    enum BulletStatus
    {
        Right_ =0,
        Left_ = 1,
    };
};

#endif // _BulletObject_H
