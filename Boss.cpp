#include "Boss.h"
Boss::Boss()
{
    range_of_skill = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = Width_boss_object;
    rect.h = Height_boss_object;
    status = walkLeft;
    x_pos = 0;
    y_pos = 0;
    hp = BOSS_MAX_HP;
    _attack = false;
    _run = false;
    attackRect.w = Width_boss_object * 1.4;
    attackRect.h = Height_boss_object * 1.3;
    dieRect.w = Width_boss_object * 1.5;
    dieRect.h = Height_boss_object;

    skillRect.w = boss_width_skill;
    skillRect.h = boss_heigh_skill;

    move_skill = false;
    frame_attack = 6;
    frame_run = -1;
    frame_die = -1;
    frame_skill = -1;

    lastAttack = high_resolution_clock::now();
    lastRun = high_resolution_clock::now();
    lastLoseHp = high_resolution_clock::now();
    currentTime = high_resolution_clock::now();
    lastDie = high_resolution_clock::now();
    lastUseSkill = high_resolution_clock::now();
    lastSkillFrame = high_resolution_clock::now();
}

void Boss ::setImg(Graphics &graphics)
{
    Boss_Right = graphics.loadTexture("BOSS_IMG/Boss_Right.png");
    Boss_Left = graphics.loadTexture("BOSS_IMG/Boss_Left.png");
    Run_Right = graphics.loadTexture("BOSS_IMG/Boss_Run_Right.png");
    Run_Left = graphics.loadTexture("BOSS_IMG/Boss_Run_Left.png");
    Attack_Right = graphics.loadTexture("BOSS_IMG/Boss_Attack_Right.png");
    Attack_Left = graphics.loadTexture("BOSS_IMG/Boss_Attack_Left.png");
    Die_Right = graphics.loadTexture("BOSS_IMG/Boss_Die_Right.png");
    Die_Left = graphics.loadTexture("BOSS_IMG/Boss_Die_Left.png");
    Skill = graphics.loadTexture("BOSS_IMG/Boss_Skill.png");
}
void Boss::set_clip_skill()
{
    if (boss_frame_width_skill > 0 && boss_frame_height_skill > 0)
    {
        for (int i=0; i < 5; i++)
        {
            frame_clip_skill[i].x = boss_frame_width_skill * i;
            frame_clip_skill[i].y = 0;
            frame_clip_skill[i].w = boss_frame_width_skill;
            frame_clip_skill[i].h = boss_frame_height_skill;
        }
    }
}
void Boss::set_clip_run()
{
    if (boss_frame_width_run > 0 && boss_frame_height_run > 0)
    {
        for (int i=0; i < 6; i++)
        {
            frame_clip_run[i].x = boss_frame_width_run * i;
            frame_clip_run[i].y = 0;
            frame_clip_run[i].w = boss_frame_width_run;
            frame_clip_run[i].h = boss_frame_height_run;
        }

    }
}
void Boss::set_clip_attack()
{
    if (boss_frame_width_attack > 0 && boss_frame_height_attack > 0)
    {
        for (int i=0; i < 7; i++)
        {
            frame_clip_attack[i].x = boss_frame_width_attack * i;
            frame_clip_attack[i].y = 0;
            frame_clip_attack[i].w = boss_frame_width_attack;
            frame_clip_attack[i].h = boss_frame_height_attack;
        }
    }
}
void Boss::set_clip_die()
{

for (int i=0; i < 6; i++)
{
    frame_clip_die[i].x = boss_frame_width_die * i;
    frame_clip_die[i].y = 0;
    frame_clip_die[i].h = boss_frame_height_die;
    frame_clip_die[i].w = boss_frame_width_die;

}

}
void Boss::Attack(Graphics &graphics)
{
    if (_attack == true)
    {
        if ( timeSinceLastAttack.count() >= 200)
        {
            if (frame_attack == 4)
            {
                graphics.playSound(gAttack);
            }
            if (frame_attack < 6)
            {
                frame_attack ++;
            }else if (frame_attack == 6)
            {
                frame_attack = 0;
            }
            lastAttack = currentTime;

        }
        if (status == walkLeft)
        {
            attackRect.x = rect.x - (attackRect.w - rect.w);
            attackRect.y = rect.y - (attackRect.h - rect.h);
            SDL_Rect* currentClip = &frame_clip_attack[6- frame_attack];
            graphics.RenderFrame(Attack_Left, currentClip, attackRect);
        }else
        {
            attackRect.x = rect.x;
            attackRect.y = rect.y - (attackRect.h - rect.h);

            SDL_Rect* currentClip = &frame_clip_attack[frame_attack];
            graphics.RenderFrame(Attack_Right, currentClip, attackRect);
        }
    }
}
void Boss::Run(Graphics &graphics)
{
        if (timeSinceLastRun.count() >= 200)
        {
            if (frame_run < 5){
                    frame_run ++;

            }
            else {frame_run = 0;}
            if (status == walkLeft)
            {
                 x_pos -= boss_speed;
                 rect.x = x_pos - map_x;
            }else{
                x_pos += boss_speed;
                rect.x = x_pos - map_x;
            }
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
void Boss::setPos(const float &x, const float &y, const float& mapx, const float& mapy){
    x_pos = x;
    y_pos = y;
    map_x = mapx;
    map_y = mapy;
    rect.x = x_pos - map_x;
    rect.y = y_pos - map_y;
}

void Boss::renderIDLE(Graphics &graphics)
{
    if (status == walkLeft)
    {
        graphics.RenderObject(Boss_Left, rect);
    }else{
        graphics.RenderObject(Boss_Right, rect);
    }
}
void Boss::setTime()
{
    currentTime = high_resolution_clock::now();
    timeSinceLastAttack = duration_cast<milliseconds> (currentTime - lastAttack);
    timeSinceLastRun = duration_cast<milliseconds> (currentTime - lastRun);
    timeSinceLastLoseHp = duration_cast<milliseconds> (currentTime - lastLoseHp);
    timeSinceLastDie = duration_cast<milliseconds> (currentTime - lastDie);
    timeSinceLastUseSkill = duration_cast<milliseconds> (currentTime - lastUseSkill);
    timeSinceLastSkillFrame = duration_cast<milliseconds> (currentTime - lastSkillFrame);
}
void Boss::loseHp(const int &damge)
{
    if (timeSinceLastLoseHp.count() >= 300 || damge == SHOOT_DAMGE)
    {
        hp-= damge;
        lastLoseHp = currentTime;
    }
}
void Boss::Die(Graphics& graphics)
{
    dieRect.x = rect.x;
    dieRect.y = rect.y + 30;
    if (timeSinceLastDie.count() >= 160)
    {
        frame_die ++;
        lastDie = currentTime;
    }
    if (status == walkRight)
    {
        SDL_Rect* currentClip = &frame_clip_die[frame_die];
        graphics.RenderFrame(Die_Right, currentClip, dieRect);
    }else
    {
        SDL_Rect* currentClip = &frame_clip_die[5- frame_die];
        graphics.RenderFrame(Die_Left, currentClip, dieRect);
    }
}
void Boss::UseSkill(Graphics &graphics)
{
    if (rect.x > 0 && rect.x <= SCREEN_WIDTH)
    {
        if (timeSinceLastUseSkill.count() >= 2500)
        {
            _attack = true;
        }
        if (timeSinceLastUseSkill.count() >= 2500 && frame_attack ==5)
        {
            if (status == walkLeft)
            {
                statusSkill = walkLeft;
                x_pos_skill = x_pos;
                skillRect.y = rect.y + Height_boss_object - skillRect.h;
                y_pos_skill = skillRect.y;
            }else{
                statusSkill = walkRight;
                x_pos_skill = x_pos + attackRect.w;
                skillRect.y = rect.y + Height_boss_object - skillRect.h;
                y_pos_skill = skillRect.y;
            }
            move_skill = true;
            lastUseSkill = currentTime;
        }
    }
}
void Boss::moveSkill(Graphics &graphics)
{
    if (range_of_skill >= 120 )
        {
            move_skill = false;
            range_of_skill = 0;
        }
    if (move_skill == true)
    {

        if (statusSkill == walkRight)
        {
            x_pos_skill += boss_skill_speed;
            skillRect.x = x_pos_skill - map_x;
            range_of_skill ++;
        }
        else
        {
            x_pos_skill -= boss_skill_speed;
            skillRect.x = x_pos_skill - map_x;
            range_of_skill ++;
        }
    }

    if (timeSinceLastSkillFrame.count() >= 100 && move_skill == true)
    {
        if (frame_skill < 4)
        {
            frame_skill ++;

        }else{
            frame_skill = 0;
        }
        SDL_Rect* currentClip = &frame_clip_skill[frame_skill];
        graphics.RenderFrame(Skill, currentClip, skillRect);
        lastSkillFrame = currentTime;
    }else if (move_skill == true)
    {
        SDL_Rect* currentClip = &frame_clip_skill[frame_skill];
        graphics.RenderFrame(Skill, currentClip, skillRect);
    }
    else if (move_skill == false)
    {
        frame_skill =-1;
    }

}
void Boss::reset()
{
    rect.x = 0;
    rect.y = 0;

    status = walkLeft;
    x_pos = 0;
    y_pos = 0;
    x_pos_skill =0;
    y_pos_skill =0;
    skillRect.x = 0;
    skillRect.y =0;
    hp = BOSS_MAX_HP;
    _attack = false;
    _run = false;

    frame_attack = 6;
    frame_run = -1;
    frame_die = -1;
}
void Boss::loadSound(Graphics& graphics)
{
    gAttack = graphics.loadSound("assets/BossAttack.wav");
    Mix_VolumeChunk(gAttack, MIX_MAX_VOLUME/8);
}
