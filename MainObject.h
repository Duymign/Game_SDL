#ifndef _MainObject_H
#define _MainObject_H

#include "BaseObject.h"
#include "BulletObject.h"
#include "BaseFunc.h"
#include "defs.h"
using namespace std::chrono;

class MainObject:public BaseObject
{
private:
    int hp;
    int score;
    int status;
    bool on_the_ground;
    float y_;
    vector <BulletObject*> bullets;
    float x_pos;
    float y_pos;

    int map_x;
    int map_y;

    SDL_Texture* character_left;
    SDL_Texture* character_in_air_right;
    SDL_Texture* character_in_air_left;

    SDL_Rect rectAttack;
    SDL_Rect skillRect;
    SDL_Rect dieRect;

    SDL_Rect frame_clip[6];
    SDL_Rect frame_clip_jump[9];
    SDL_Rect frame_clip_attack[5];
    SDL_Rect frame_clip_shoot[3];
    SDL_Rect frame_clip_skill[6];
    SDL_Rect frame_clip_die[5];

    SDL_Texture* runRight;
    SDL_Texture* runLeft;
    SDL_Texture* jumpLeft;
    SDL_Texture* jumpRight;
    SDL_Texture* attackRight;
    SDL_Texture* attackLeft;
    SDL_Texture* shootRight;
    SDL_Texture* shootLeft;
    SDL_Texture* skillRight;
    SDL_Texture* skillLeft;
    SDL_Texture* dieRight;
    SDL_Texture* dieLeft;

    high_resolution_clock::time_point lastWalk ;
    high_resolution_clock::time_point lastShoot ;
    high_resolution_clock::time_point lastAttack ;
    high_resolution_clock::time_point lastJump;
    high_resolution_clock::time_point lastSkill;
    high_resolution_clock::time_point lastUseSkill;
    high_resolution_clock::time_point lastUseAttack;
    high_resolution_clock::time_point lastUseShoot;
    high_resolution_clock::time_point lastLoseHp;
    high_resolution_clock::time_point lastDie;
    high_resolution_clock::time_point currentTime;

    duration<int, milli> timeSinceLastWalk;
    duration<int, milli> timeSinceLastShoot;
    duration<int, milli> timeSinceLastAttack;
    duration<int, milli> timeSinceLastJump;
    duration<int, milli> timeSinceLastSkill;
    duration<int, milli> timeSinceLastUseSkill;
    duration<int, milli> timeSinceLastUseAttack;
    duration<int, milli> timeSinceLastUseShoot;
    duration<int, milli> timeSinceLastLoseHp;
    duration<int, milli> timeSinceLastDie;

    int frame_walk ;
    int frame_attack ;
    int frame_shoot ;
    int frame_jump ;
    int frame_skill;
    int frame_die;

    bool up_ = false, down_ = false, left_ = false, right_ = false, attack_ = false, shoot_= false, skill_ = false;
    //Sound
    Mix_Chunk* gJump;
    Mix_Chunk* gAttack;
    Mix_Chunk* gSkill;
    Mix_Chunk* gShoot;

public:
    MainObject();
    ~MainObject();
    void setTime();
    SDL_Rect get_attack_rect(){return rectAttack;}
    void setRect(const int &x, const int &y){
        rect.x = x;
        rect.y = y;
        rect.w = Width_main_object;
        rect.h = Height_main_Object;
    }
    void setImg(Graphics &graphics);
    void setFrameDie(){frame_die = -1;}

    void Action(SDL_Event &event);

    int getStatus() {return status;}
    int getFrameDie(){return frame_die;}
    SDL_Texture* get_skill_right_texture(){return skillRight;}
    SDL_Texture* get_skill_left_texture(){return skillLeft;}

    SDL_Texture* get_run_right_texture()
    {
        return runRight;
    }
    SDL_Texture* get_run_left_texture()
    {
        return runLeft;
    }
    SDL_Texture * get_jump_right_texture()
    {
        return jumpRight;
    }
    SDL_Texture * get_jump_left_texture()
    {
        return jumpLeft;
    }
    SDL_Rect* get_frame_clip_walk()
    {
        return frame_clip;
    }
    SDL_Rect* get_frame_clip_jump()
    {
        return frame_clip_jump;
    }
    SDL_Rect* get_frame_clip_skill(){return frame_clip_skill;}
    SDL_Rect getSkillRect(){return skillRect;}
    void loseHp(const int &damge);
    int getHp()
    {
       return hp;
    }
    enum walkType
    {
        walkRight = 0,
        walkLeft =1,
    };
    void setclip();
    void set_clip_jump();
    void set_clip_attack();
    void set_clip_shoot();
    void set_clip_skill();
    void set_clip_die();
    void setHp(const int &hp){this->hp = hp;}

    void walk(const MAP &mapdata,Graphics &graphics);
    void MoveInAir(const MAP& mapdata, Graphics &graphics);
    void Jump(Graphics &graphics);
    void attack(Graphics &graphics);
    vector <BulletObject*> get_list_bullet(){return bullets;}
    void shoot(Graphics &graphics);
    void skill( Graphics &graphics, const MAP& mapdata);
    void check_map_collision(const MAP &map_data);
    void centre_on_map(MAP &map_data);
    void is_on_the_ground()
    {
        if (y_ >= MAX_FALL_SPEED)
        {
            y_ = MAX_FALL_SPEED;
        }else{
            y_ += gravity_speed;
        }
        if (on_the_ground == false)
        {
            y_pos += y_;
        }
        if(on_the_ground == true)
        {
            y_ = 0;
        }
        rect.y = y_pos - map_y;
    }
    bool get_status_on_ground()
    {
        return on_the_ground;
    }
    //void setMapXY(const int& map_x_, const int &map_y_){map_x = map_x_; map_y = map_y_;}
    void setPos(const int& x, const int &y)
    {
        x_pos = x;
        y_pos =y;
    }

    int get_x_pos(){return x_pos;}
    int get_y_pos(){return y_pos;}
    void setMapXY(const int& x, const int &y){map_x = x; map_y = y;}
    void renderPlayerNotMove(Graphics &graphics);
    bool get_status_attack(){return attack_;}
    bool get_status_skill(){return skill_;}
    bool get_status_shoot(){return shoot_;}
    float get_time_set_skill(){return timeSinceLastUseSkill.count();}
    float get_time_set_attack(){return timeSinceLastUseAttack.count();}
    float get_time_set_shoot(){return timeSinceLastUseShoot.count();}

    int get_attack_frame(){return frame_attack;}
    void die(Graphics &graphics);
    void reset();
    void loadSound(Graphics& graphics);

};
#endif // _MainObject_H
