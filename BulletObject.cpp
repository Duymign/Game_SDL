#include "BulletObject.h"
BulletObject ::BulletObject()
{
    rect.x = 0;
    rect.y = 0;
    rect.h =0;
    rect.w = 0;

}

BulletObject :: ~BulletObject()
{

}
void BulletObject::setRect(const int &x,const int &y)
    {
        rect.x = x;
        rect.y = y;
        rect.h = Height_Bullet;
        rect.w = Width_Bullet;

    }
void BulletObject::MoveBullet(const int& x_border, const int &y_border)
{
    if(bullet_status == Right_) // Walk Right
     {
         rect.x += BULLET_SPEED;
        if (rect.x >= x_border)
        {
            ismove = false;
        }
     }
     else{
        rect.x -= BULLET_SPEED;
        if (rect.x <= 0)
        {
            ismove = false;
        }
     }

}

