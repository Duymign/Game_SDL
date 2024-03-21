#include "EnemyObject.h"
EnemyObject::EnemyObject()
{
    rect.x =0;
    rect.y = 0;
    rect.w = Width_enemy_object;
    rect.h = Height_enemy_object;
    x_pos = 0;
    y_pos = 0;
    map_x =0;
    map_y = 0;
    status = walkRight;
    attackRect.w = Width_enemy_object * 1.3;
    attackRect.h = Height_enemy_object;
    dieRect.w = Width_enemy_object * 1.6;
    dieRect.h = Height_enemy_object;

    _attack = false;
    _hurt = false;

    frame_attack = -1;
    frame_run = -1;
    frame_hurt = -1;
    frame_die = -1;
    lastAttack = high_resolution_clock::now();
    lastRun = high_resolution_clock::now();
    lastLoseHp = high_resolution_clock::now();
    lastHurt = high_resolution_clock::now();
    lastDie = high_resolution_clock::now();

    currentTime = high_resolution_clock::now();
    hp = ENEMY_MAX_HP;
}
EnemyObject::~EnemyObject()
{
    ;
}
void EnemyObject::setImg(Graphics &graphics)
{
    Run_Left = graphics.loadTexture ("ENEMY_IMG/Enemy_Walk_Left.png");
    Run_Right = graphics.loadTexture("ENEMY_IMG/Enemy_Walk_Right.png");
    Attack_Right = graphics.loadTexture("ENEMY_IMG/Enemy_Attack_Right.png");
    Attack_Left = graphics.loadTexture("ENEMY_IMG/Enemy_Attack_Left.png");
    Hurt_Right = graphics.loadTexture("ENEMY_IMG/Enemy_Hurt_Right.png");
    Hurt_Left = graphics.loadTexture("ENEMY_IMG/Enemy_Hurt_Left.png");
    Die_Right = graphics.loadTexture("ENEMY_IMG/Enemy_Die_Right.png");
    Die_Left = graphics.loadTexture("ENEMY_IMG/Enemy_Die_Left.png");
}
void EnemyObject::set_clip_run()
{
    for (int i=0; i < 6; i++)
    {
        frame_clip_run[i].x = enemy_frame_width_run * i;
        frame_clip_run[i].y = 0;
        frame_clip_run[i].w = enemy_frame_width_run;
        frame_clip_run[i].h = enemy_frame_height_run;
    }

}
void EnemyObject::set_clip_attack()
{
    for (int i=0; i < 4; i++)
    {
        frame_clip_attack[i].x = enemy_frame_width_attack * i;
        frame_clip_attack[i].y = 0;
        frame_clip_attack[i].w = enemy_frame_width_attack;
        frame_clip_attack[i].h = enemy_frame_height_attack;
    }

}
void EnemyObject::set_clip_hurt()
{
    for (int i=0; i < 2; i++)
    {
        frame_clip_hurt[i].x = enemy_frame_width_hurt * i;
        frame_clip_hurt[i].y = 0;
        frame_clip_hurt[i].w = enemy_frame_width_hurt;
        frame_clip_hurt[i].h = enemy_frame_height_hurt;
    }


}
void EnemyObject::set_clip_die()
{
    for (int i=0; i < 4; i++)
    {
        frame_clip_die[i].x = enemy_frame_width_die * i;
        frame_clip_die[i].y =0;
        frame_clip_die[i].w = enemy_frame_width_die;
        frame_clip_die[i].h = enemy_frame_height_die;
    }

}
void EnemyObject::Run( Graphics &graphics)
{
    if (_attack == false && _hurt == false){
        if (timeSinceLastRun.count() >= 150)
        {
            if (frame_run < 5){
                frame_run ++;
            }
            if (status == walkLeft)
            {
            x_pos -= enemy_speed;
            if (frame_run == 5){
                status = walkRight;
                frame_run = 0;
            }
            }else
            {
            x_pos += enemy_speed;
            if (frame_run == 5)
            {
                status = walkLeft;
                frame_run = 0;
            }
            }
            rect.x = x_pos - map_x;
            lastRun = currentTime;
        }
            if (status == walkLeft)
            {
            SDL_Rect* currentClip = &frame_clip_run[5 - frame_run];

            graphics.RenderFrame(Run_Left, currentClip, rect);
            }else{
                SDL_Rect* currentClip = &frame_clip_run[frame_run];

                graphics.RenderFrame(Run_Right, currentClip, rect);
            }
    }

}
void EnemyObject::Attack( Graphics &graphics)
{
    if (_attack == true && _hurt == false)
    {
        if ( timeSinceLastAttack.count() >= 150)
        {
            if (frame_attack < 3)
            {
                frame_attack ++;
                lastAttack = currentTime;
            }else if (frame_attack == 3)
            {
                frame_attack = -1;
                _attack = false;
            }

        }

        if (status == walkLeft && _attack == true)
        {
            attackRect.x = rect.x - (attackRect.w - rect.w) ;
            attackRect.y = rect.y;
            SDL_Rect* currentClip = &frame_clip_attack[3- frame_attack];

            graphics.RenderFrame(Attack_Left, currentClip, attackRect);
        }else if (_attack == true)
        {
            attackRect.x = rect.x;
            attackRect.y = rect.y;
            SDL_Rect* currentClip = &frame_clip_attack[frame_attack];
            graphics.RenderFrame(Attack_Right, currentClip, attackRect);
        }
    }
}
void EnemyObject::setTime()
{
    BossObject::setTime();
    timeSinceLastHurt = duration_cast<milliseconds> (currentTime - lastHurt);
}

void EnemyObject::check_to_map(const MAP &mapdata)
{
    int x1 = (x_pos) / TILE_SIZE;
    int x2 = (x_pos + Width_enemy_object -1)/ TILE_SIZE;

    int y1 = y_pos / TILE_SIZE;
    int y2 = (y_pos + TILE_SIZE -1)/ TILE_SIZE;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if ((mapdata.tile[y1][x2] >= 1 && mapdata.tile[y1][x2] <= 15) || (mapdata.tile[y2][x2] >= 1 && mapdata.tile[y2][x2] <= 15) )
        {
            status = walkLeft;
        }
        else if ((mapdata.tile[y1][x1] >= 1 && mapdata.tile[y1][x1] <= 15) || (mapdata.tile[y2][x1] >= 1 && mapdata.tile[y2][x1] <= 15))
        {
            status = walkRight;
        }
    }

    x1 = x_pos / TILE_SIZE;
    x2 = (x_pos + TILE_SIZE )/ TILE_SIZE;
    y1 = y_pos / TILE_SIZE;
    y2 = (y_pos + Height_enemy_object + 1)/ TILE_SIZE;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
            if (mapdata.tile[y2][x2] == 0 && mapdata.tile[y2][x1] == 0)
            {
                y_pos += TILE_SIZE;
            }
            if(mapdata.tile[y2][x2] == 0)
            {
                status = walkLeft;
            }else if (mapdata.tile[y2][x1] == 0)
            {
                status = walkRight;
            }
    }
}
void EnemyObject::loseHp(const int &damge, Graphics& graphics)
{

    if (timeSinceLastLoseHp.count() >= 300 || damge == SHOOT_DAMGE)
    {
        hp -= damge;
        lastLoseHp = currentTime;
        _hurt = true;
    }
}
void EnemyObject::Hurt(Graphics& graphics)
{
    if (_hurt == true)
    {
        if (timeSinceLastHurt.count() >= 180)
        {
            if (frame_hurt < 1)
            {
                frame_hurt ++;
                lastHurt = currentTime;

            }else if (frame_hurt == 1)
            {
                frame_hurt = -1;
                _hurt = false;
            }

        }
        if (status == walkRight && _hurt == true)
        {
            SDL_Rect* currentclip = &frame_clip_hurt[frame_hurt];
            graphics.RenderFrame(Hurt_Right, currentclip, rect);
        }else if (_hurt == true){
            SDL_Rect* currentclip = &frame_clip_hurt[1 - frame_hurt];
            graphics.RenderFrame(Hurt_Left, currentclip, rect);
        }
    }
}

void EnemyObject::Die(Graphics &graphics)
{
    dieRect.x = rect.x;
    dieRect.y = rect.y ;
    if (timeSinceLastDie.count() >= 150)
    {
        frame_die ++;
        lastDie = currentTime;
    }

    if (status == walkRight && frame_die <=3)
    {
        SDL_Rect* currentClip = &frame_clip_die[frame_die];
        graphics.RenderFrame(Die_Right, currentClip, dieRect);
    }else if (frame_die <= 3)
    {
        SDL_Rect* currentClip = &frame_clip_die[4- frame_die];
        graphics.RenderFrame(Die_Left, currentClip, dieRect);
    }
}
