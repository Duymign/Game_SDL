#ifndef Boss_H
#define Boss_H

#include "BaseObject.h"
#include "Graphics.h"
#include "defs.h"
using namespace std::chrono;
class Boss :public BaseObject
{
protected:
    float x_pos;
    float y_pos;
    float x_pos_skill;
    float y_pos_skill;

    int status;
    int statusSkill;
    int map_x;
    int map_y;
    int hp;
    int frame_attack ;
    int frame_run;
    int frame_die;
    int frame_skill;
    int range_of_skill;

    bool move_skill;

    SDL_Texture* Boss_Right;
    SDL_Texture* Boss_Left;
    SDL_Texture* Run_Right;
    SDL_Texture* Run_Left;
    SDL_Texture* Attack_Right;
    SDL_Texture* Attack_Left;
    SDL_Texture* Die_Right;
    SDL_Texture* Die_Left;
    SDL_Texture* Skill;

    SDL_Rect frame_clip_run[6];
    SDL_Rect frame_clip_attack[7];
    SDL_Rect frame_clip_die[6];
    SDL_Rect frame_clip_skill[5];

    SDL_Rect attackRect;
    SDL_Rect dieRect;
    SDL_Rect skillRect;

    high_resolution_clock::time_point currentTime;

    high_resolution_clock::time_point lastAttack ;
    high_resolution_clock::time_point lastRun ;
    high_resolution_clock::time_point lastLoseHp ;
    high_resolution_clock::time_point lastDie;
    high_resolution_clock::time_point lastUseSkill;
    high_resolution_clock::time_point lastSkillFrame;

    duration<int, milli> timeSinceLastAttack ;
    duration<int, milli> timeSinceLastRun ;
    duration<int, milli> timeSinceLastLoseHp ;
    duration<int, milli> timeSinceLastDie;
    duration<int, milli> timeSinceLastUseSkill;
    duration<int, milli> timeSinceLastSkillFrame;

    bool _run ;
    bool _attack;
    Mix_Chunk *gAttack;

public:
    Boss();
    ~Boss(){;}
    void setTime();
    void loseHp(const int &damage);
    int getHp(){return hp;}
    void setImg(Graphics &graphics);
    void set_clip_run();
    void set_clip_attack();
    void set_clip_die();
    void set_clip_skill();
    void Run(Graphics &graphics);
    void setPos(const float &x, const float &y, const float& mapx, const float& mapy);
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
    void UseSkill(Graphics& graphics);
    void moveSkill(Graphics& graphics);

    void reset();
    void loadSound(Graphics &graphics);

    float get_x_skill_pos(){return x_pos_skill;}
    float get_y_skill_pos(){return y_pos_skill;}
    bool isUseSkill(){return move_skill;}

};



#endif // Boss_H
