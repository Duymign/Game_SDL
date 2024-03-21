#ifndef BossObject_H
#define BossObject_H

#include "BaseObject.h"
#include "BaseFunc.h"
#include "defs.h"
using namespace std::chrono;
class BossObject :public BaseObject
{
protected:
    float x_pos;
    float y_pos;
    int status;
    int map_x;
    int map_y;
    int hp;
    int frame_attack ;
    int frame_run;
    int frame_die;

    SDL_Texture* Boss_Right;
    SDL_Texture* Boss_Left;
    SDL_Texture* Run_Right;
    SDL_Texture* Run_Left;
    SDL_Texture* Attack_Right;
    SDL_Texture* Attack_Left;
    SDL_Texture* Die_Right;
    SDL_Texture* Die_Left;

    SDL_Rect frame_clip_run[6];
    SDL_Rect frame_clip_attack[7];
    SDL_Rect frame_clip_die[6];

    SDL_Rect attackRect;
    SDL_Rect dieRect;

    high_resolution_clock::time_point currentTime;

    high_resolution_clock::time_point lastAttack ;
    high_resolution_clock::time_point lastRun ;
    high_resolution_clock::time_point lastLoseHp ;
    high_resolution_clock::time_point lastDie;

    duration<int, milli> timeSinceLastAttack ;
    duration<int, milli> timeSinceLastRun ;
    duration<int, milli> timeSinceLastLoseHp ;
    duration<int, milli> timeSinceLastDie;

    bool _run ;
    bool _attack;

public:
    BossObject();
    ~BossObject(){;}
    void setTime();
    void loseHp(const int &damage);
    int getHp(){return hp;}
    void setImg(Graphics &graphics);
    void set_clip_run();
    void set_clip_attack();
    void set_clip_die();
    void Run(Graphics &graphics);
    void setPos(const int &x, const int &y, const int& mapx, const int& mapy);
    enum walkStatus{
        walkRight = 0,
        walkLeft = 1,
    };
    SDL_Rect getRect(){return rect;}
    SDL_Rect getAttackRect(){return attackRect;}

    float get_x_pos(){return x_pos;}
    float get_y_pos(){return y_pos;}
    void setStatus(const int&x){status = x;}
    void setHp(const int& x){hp = x;}
    void setFrameDie(){frame_die = -1;}

    int getStatus(){return status;}
    SDL_Rect* get_frame_clip_run(){return frame_clip_run;}
    SDL_Texture* get_texture_right(){return Boss_Right;}
    SDL_Texture* get_texture_left(){return Boss_Left;}
    SDL_Texture* get_texture_run_left(){return Run_Left;}
    SDL_Texture* get_texture_run_right(){return Run_Right;}
    SDL_Texture* get_texture_attack_left(){return Attack_Left;}
    SDL_Texture* get_texture_attack_right() {return Attack_Right;}
    void setToMap(const int&x, const int &y){map_x = x; map_y = y; rect.x = x_pos - map_x; rect.y = y_pos - map_y;}
    void renderIDLE(Graphics &graphics);
    void Attack(Graphics &graphics);
    void setAttackRect(const SDL_Rect &attackRect){this->attackRect = attackRect;}
    void change_status_attack(const bool& attack){_attack = attack;}
    void change_status_run(const bool &run){_run = run;}
    int get_frame_attack(){return frame_attack;}
    int get_frame_run(){return frame_run;}
    int get_frame_die(){return frame_die;}
    bool get_status_attack(){return _attack;}
    void Die(Graphics &graphics);
    void reset();

};



#endif // BossObject_H
