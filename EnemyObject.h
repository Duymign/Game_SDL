#ifndef EnemyObject_H
#define EnemyObject_H
#include "BossObject.h"
using namespace std::chrono;

class EnemyObject : public BossObject
{
private:
    SDL_Rect attackRect;
    bool _hurt;

    int frame_hurt;
    SDL_Rect frame_clip_hurt[2];
    SDL_Rect frame_clip_die[4];
    SDL_Texture* Hurt_Right;
    SDL_Texture* Hurt_Left;

    high_resolution_clock::time_point lastHurt ;
    duration<int, milli> timeSinceLastHurt;

public:
    EnemyObject();
    ~EnemyObject();
    void Run(Graphics &graphics);
    void Attack(Graphics &graphics);
    void setImg(Graphics &graphics);
    void set_clip_run();
    void set_clip_attack();
    void set_clip_hurt();
    void set_clip_die();

    void setTime();
    SDL_Rect getAttackRect(){return attackRect;}
    int getFrameAttack(){return frame_attack;}
    int getFrameDie(){return frame_die;}
    void check_map_collision(const MAP &mapdata);
    void loseHp(const int &damge, Graphics& graphics);
    void Hurt(Graphics &graphics);
    void Die(Graphics &graphics);
    bool get_status_hurt(){return _hurt;}
    void loadSound(Graphics& graphics);
};

#endif // EnemyObject_H
