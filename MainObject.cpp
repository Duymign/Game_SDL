#include "MainObject.h"
MainObject::MainObject()
{
    rect.x = 0;
    rect.y = 0;
    rect.h =0;
    rect.w = 0;
    y_ =0;
    x_pos = 0;
    y_pos = 0;
    map_x = 0;
    map_y = 0;
    dieRect.w = Width_main_object * 1.5;
    dieRect.h = Height_main_Object;

    frame_walk = -1;
    frame_attack = -1;
    frame_shoot = -1;
    frame_jump = -1;
    frame_skill = -1;
    frame_die = -1;

    status = walkRight;
    object = NULL;
    hp = Main_Max_Hp;
    score = 0;
    on_the_ground = false;

    lastWalk = high_resolution_clock::now();
    lastShoot = high_resolution_clock::now();
    lastAttack = high_resolution_clock::now();
    lastJump = high_resolution_clock::now();
    lastSkill = high_resolution_clock::now();
    lastLoseHp = high_resolution_clock::now();
    lastUseSkill = high_resolution_clock::now();
    lastUseAttack = high_resolution_clock::now();
    lastUseShoot = high_resolution_clock::now();
    lastDie = high_resolution_clock::now();
    currentTime = high_resolution_clock::now();

}
MainObject::~MainObject()
{
;
}
void MainObject::setTime()
{
    currentTime = high_resolution_clock::now();
    timeSinceLastWalk = duration_cast<milliseconds> (currentTime - lastWalk);
    timeSinceLastShoot = duration_cast<milliseconds> (currentTime - lastShoot);
    timeSinceLastAttack = duration_cast<milliseconds> (currentTime - lastAttack);
    timeSinceLastJump = duration_cast<milliseconds> (currentTime - lastJump);
    timeSinceLastSkill = duration_cast<milliseconds> (currentTime - lastSkill);
    timeSinceLastUseSkill =duration_cast<milliseconds> (currentTime - lastUseSkill);
    timeSinceLastUseAttack = duration_cast<milliseconds> (currentTime - lastUseAttack);
    timeSinceLastUseShoot = duration_cast<milliseconds> (currentTime - lastUseShoot);
    timeSinceLastLoseHp = duration_cast<milliseconds> (currentTime - lastLoseHp);
    timeSinceLastDie = duration_cast<milliseconds> (currentTime - lastDie);
}
void MainObject::setImg(Graphics &graphics)
{
    runRight = graphics.loadTexture("IMG/Character_Run_Right.png");
    runLeft = graphics.loadTexture("IMG/Character_Run_Left.png");
    jumpRight = graphics.loadTexture("IMG/Character_Jump_Right.png");
    jumpLeft = graphics.loadTexture("IMG/Character_Jump_Left.png");
    attackRight = graphics.loadTexture("IMG/Attack_Right.png");
    attackLeft = graphics.loadTexture("IMG/Attack_Left.png");
    shootRight = graphics.loadTexture("IMG/Character_Shoot_Right.png");
    shootLeft = graphics.loadTexture("IMG/Character_Shoot_Left.png");
    skillRight = graphics.loadTexture("IMG/Character_Skill_Right.png");
    skillLeft = graphics.loadTexture("IMG/Character_Skill_Left.png");

    character_left = graphics.loadTexture("IMG/Character_Left.png");
    character_in_air_right = graphics.loadTexture("IMG/Character_In_Air_Right.png");
    character_in_air_left = graphics.loadTexture("IMG/Character_In_Air_Left.png");
    dieRight = graphics.loadTexture("IMG/Character_Die_Right.png");
    dieLeft = graphics.loadTexture("IMG/Character_Die_Left.png");

}
void MainObject::set_clip_shoot()
{
    if (frame_height_shoot > 0 && frame_width_shoot > 0)
    {
        for (int i=0; i < 3; i++)
        {
            frame_clip_shoot[i].x = frame_width_shoot * i;
            frame_clip_shoot[i].y =0;
            frame_clip_shoot[i].w = frame_width_shoot;
            frame_clip_shoot[i].h = frame_height_shoot;
        }

    }
}
void MainObject::setclip()
{
    if (frame_width > 0 && frame_height > 0)
    {
        for (int i=0; i< 6; i++)
        {
            frame_clip[i].x = frame_width * i;
            frame_clip[i].y = 0;
            frame_clip[i].w = frame_width;
            frame_clip[i].h = frame_height;
        }
    }
}
void MainObject::set_clip_jump()
{
    if (frame_width_jump > 0 && frame_height_jump > 0)
    {
        for (int i=0;i < 7; i++)
        {
            frame_clip_jump[i].x = frame_width_jump * i;
            frame_clip_jump[i].y = 0;
            frame_clip_jump[i].w = frame_width_jump;
            frame_clip_jump[i].h = frame_height_jump;
        }
    }
}
void MainObject::set_clip_attack()
{
    for (int i=0; i < 5; i++)
    {
        frame_clip_attack[i].x = frame_width_attack * i;
        frame_clip_attack[i].y = 0;
        frame_clip_attack[i].w = frame_width_attack;
        frame_clip_attack[i].h = frame_height_attack;
    }

}
void MainObject::set_clip_skill()
{
    for (int i=0; i < 6; i++)
    {
        frame_clip_skill[i].x = frame_width_skill * i;
        frame_clip_skill[i].y = 0;
        frame_clip_skill[i].w = frame_width_skill;
        frame_clip_skill[i].h = frame_height_skill;
    }

}
void MainObject::set_clip_die()
{
    for (int i=0; i < 5; i++)
    {
        frame_clip_die[i].x = frame_width_die *i;
        frame_clip_die[i].y = 0;
        frame_clip_die[i].w = frame_width_die;
        frame_clip_die[i].h = frame_height_die;
    }
}
void MainObject::Action(SDL_Event &event)
{
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_a:status = walkLeft;left_ = true;right_ = false;break;

                case SDLK_RIGHT:
                case SDLK_d:status = walkRight;right_ = true;left_ = false;break;


                case SDLK_w:
                if (on_the_ground == true)
                {
                    up_ = true;
                }
                break;
                case SDLK_j:
                    if(shoot_ ==false && skill_ == false && timeSinceLastUseAttack.count() >= timeSetAttack)
                    {
                        attack_ = true;
                        lastUseAttack = currentTime;
                    }
                    break;
                case SDLK_k:
                    if(attack_ == false && skill_ == false && timeSinceLastUseShoot.count() >= timeSetShoot)
                    {
                        if (frame_shoot == -1)
                        {
                            BulletObject* newBullet = new BulletObject() ;
                            newBullet->setRect(rect.x + Width_main_object/2, rect.y + Height_main_Object/2 - 20);
                            newBullet->setmove(true);
                            newBullet->setStatus(status);
                            bullets.push_back(newBullet);
                            shoot_ = true;
                        }
                        lastUseShoot = currentTime;
                    }
                    break;
                case SDLK_l:
                    if (attack_ == false && shoot_ == false &&up_ == false  && timeSinceLastUseSkill.count() >= timeSetSkill)
                    {
                        skill_ = true;
                        lastUseSkill = currentTime;
                    }
                    break;
            }
        }else if(event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:

                case SDLK_LEFT:
                case SDLK_a:
                left_ = false;
                break;
                case SDLK_RIGHT:
                case SDLK_d:
                right_ = false;
                break;
            }
        }
}

void MainObject::walk(const MAP& mapdata, Graphics &graphics)
{
    SDL_Rect* currentclip;
    if (on_the_ground == true && shoot_ ==false && attack_ == false && skill_ == false)
    {
        if (timeSinceLastWalk.count() >= fps )
        {
            if(left_ || right_)
            {
                if (frame_walk < 5)
                {
                    frame_walk ++;
                }else if (frame_walk == 5)
                {
                    frame_walk = 0;
                }
            }else
            {
                frame_walk = -1;
            }
            //
            if(status == walkRight && right_ == true)
            {
                x_pos += character_speed;
                check_map_collision(mapdata);
                rect.x = x_pos - map_x;

            }else if(status == walkLeft && left_ == true)
            {
                x_pos -= character_speed;
                check_map_collision(mapdata);
                rect.x = x_pos - map_x;
            }

            lastWalk = currentTime;
        }
        //
        if(right_ == true && frame_walk != -1)
        {
            currentclip = &frame_clip[frame_walk];
            graphics.RenderFrame(runRight, currentclip, rect);

        }else if (left_ == true && frame_walk != -1)
        {
            currentclip = &frame_clip[5- frame_walk];
            graphics.RenderFrame(runLeft, currentclip, rect);
        }
    }
}
void MainObject::MoveInAir(const MAP& mapdata, Graphics &graphics)
{
    if (on_the_ground == false)
        {
            if(left_)
            {
                if (timeSinceLastWalk.count() >= fps)
                {
                    x_pos= x_pos - character_speed;
                    is_on_the_ground();
                    lastWalk = currentTime;
                }else{
                    is_on_the_ground();
                }
                if (shoot_ == false && attack_ == false && up_ == false && skill_ == false)
                {
                    graphics.RenderObject(character_in_air_left, rect);
                }
            }else if(right_)
            {
                if (timeSinceLastWalk.count() >= fps)
                {
                    x_pos=x_pos + character_speed;
                    is_on_the_ground();
                    lastWalk = currentTime;
                }else{
                    is_on_the_ground();
                }

                if (shoot_ == false && attack_ == false && up_ == false && skill_ == false)
                {
                    graphics.RenderObject(character_in_air_right, rect);
                }

        }else{
            is_on_the_ground();
        }
        check_map_collision(mapdata);
    }
}

void MainObject::Jump(Graphics &graphics)
{
    if (up_ && timeSinceLastJump.count() >= 30)
    {
        y_pos -= 40;
        rect.y = y_pos - map_y;
        on_the_ground = false;
        if (frame_jump < 6)
            {
                frame_jump++;
            }else if (frame_jump == 6)
            {
                frame_jump = -1;
                up_ = false;
            }
            lastJump = currentTime;
        if (frame_jump == 0)
        {
            graphics.playSound(gJump);
        }
    }
    if (up_ == true && attack_ == false && skill_ == false && shoot_ == false)
    {
        if (status == walkRight)
        {
            SDL_Rect *currentclip = &frame_clip_jump[frame_jump];
            graphics.RenderFrame(jumpRight, currentclip, rect);
        }
        else{
            SDL_Rect *currentclip = &frame_clip_jump[6 - frame_jump];
            graphics.RenderFrame(jumpLeft, currentclip, rect);
        }
    }

}

void MainObject::attack(Graphics &graphics)
{
    rectAttack.h =rect.h * 1.3;
    rectAttack.w = rect.w * 1.3;

    rectAttack.y = rect.y -(rectAttack.h - rect.h);
    SDL_Rect* currentclip;
    if (attack_ )
    {
        if (timeSinceLastAttack.count() >= fps )
        {
            if (frame_attack <= 3)
            {
                frame_attack ++;
                lastAttack = currentTime;
            }else if (frame_attack == 4)
            {
                frame_attack = -1;
                attack_ = false;
            }
            if (frame_attack == 0)
            {
                graphics.playSound(gAttack);
            }

        }
        if (status == walkRight && attack_ == true)
            {
                rectAttack.x = rect.x;
                currentclip = &frame_clip_attack[frame_attack];
                graphics.RenderFrame(attackRight, currentclip, rectAttack);
            }
        else if(status == walkLeft && attack_ == true)
            {
                rectAttack.x = rect.x - (rectAttack.w - rect.w);
                currentclip = &frame_clip_attack[4- frame_attack];
                graphics.RenderFrame(attackLeft, currentclip, rectAttack);
            }

    }
}
void MainObject::shoot(Graphics &graphics)
{
    SDL_Rect* currentclip;
    if(shoot_ == true)
    {
        if (timeSinceLastShoot.count() >= 80){

            if (frame_shoot  <= 1)
            {
                frame_shoot++;
                lastShoot = currentTime;
            }else if (frame_shoot == 2)
                {
                    frame_shoot = -1;
                    shoot_ = false;
                }
            if (frame_shoot == 0)
            {
                graphics.playSound(gShoot);
            }

        }
        if (status == walkRight && shoot_ == true)
        {
            currentclip = &frame_clip_shoot[frame_shoot];
            graphics.RenderFrame(shootRight, currentclip, rect);

        }else if (shoot_ == true){
            currentclip = &frame_clip_shoot[2 -frame_shoot];
            graphics.RenderFrame(shootLeft, currentclip, rect);
        }
    }

}
void MainObject::skill( Graphics &graphics, const MAP& mapdata)
{
    skillRect.x = rect.x;
    skillRect.y = rect.y;
    skillRect.w = Width_main_object * 3;
    skillRect.h = Height_main_Object;
    SDL_Rect* currentclip;
    if (skill_ == true )
    {
        if (timeSinceLastSkill.count() >= fps + 10)
        {
            if(frame_skill < 5)
                {
                    frame_skill ++;
                    lastSkill = currentTime;
                }else if (frame_skill == 5)
                    {
                        frame_skill = -1;
                        skill_ = false;
                    }
            if (status == walkRight)
            {
                x_pos += Width_main_object/2;
                rect.x = x_pos - map_x;
                skillRect.x = rect.x;

            }else{
                x_pos -= Width_main_object/2;
                rect.x = x_pos -map_x;
                skillRect.x = rect.x;
            }
            check_map_collision(mapdata);
            if (frame_skill ==0)
            {
                graphics.playSound(gSkill);
            }
        }
        if (status == walkRight && skill_ == true)
        {
            currentclip = &frame_clip_skill[frame_skill];
            graphics.RenderFrame(skillRight, currentclip, skillRect);
        }else if (skill_ == true) {
            currentclip = &frame_clip_skill[5 - frame_skill];
            graphics.RenderFrame(skillLeft, currentclip, skillRect);
        }
    }
}
void MainObject::renderPlayerNotMove(Graphics &graphics)
{
    if (left_ == false && right_ == false && shoot_ == false && attack_ == false && up_ == false && skill_ ==false)
        {
            if (on_the_ground == false)
            {
                if(status == walkRight)
                {
                    graphics.RenderObject(character_in_air_right, rect);
                }else
                {
                    graphics.RenderObject(character_in_air_left, rect);
                }
            }else{
                if(status == walkRight) // Walk_Right
                {
                    graphics.RenderObject(object, rect);
                }
                else{
                    graphics.RenderObject(character_left, rect);
                }
            }
        }
}
// x1, y1     x2, y1

// x1, y2     x2, y2
void MainObject::check_map_collision(const MAP &mapdata)
{
    int x1 = (x_pos) / TILE_SIZE;
    int x2 = (x_pos + Width_main_object -1)/ TILE_SIZE;

    int y1 = y_pos / TILE_SIZE;
    int y2 = (y_pos + TILE_SIZE -1)/ TILE_SIZE;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if ((mapdata.tile[y1][x2] >= 1 && mapdata.tile[y1][x2] <= 15) || (mapdata.tile[y2][x2] >= 1 && mapdata.tile[y2][x2] <= 15) )
        {
            x_pos = x2 * TILE_SIZE - Width_main_object ;
        }
        else if ((mapdata.tile[y1][x1] >= 1 && mapdata.tile[y1][x1] <= 15) || (mapdata.tile[y2][x1] >= 1 && mapdata.tile[y2][x1] <= 15))
        {
            x_pos = (x1 + 1) * TILE_SIZE ;
        }
    }

    x1 = x_pos / TILE_SIZE;
    x2 = (x_pos + TILE_SIZE )/ TILE_SIZE;
    y1 = y_pos / TILE_SIZE;
    y2 = (y_pos + Height_main_Object + 1)/ TILE_SIZE;

    if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
            if ((mapdata.tile[y2][x2] >= 1 && mapdata.tile[y2][x2] <= 15) || (mapdata.tile[y2][x1] >= 1 && mapdata.tile[y2][x1] <= 15))
            {
                y_pos = y2 * TILE_SIZE - Height_main_Object ;
                on_the_ground = true;
            }else if(mapdata.tile[y2][x2] == 0 && mapdata.tile[y2][x1] == 0)
            {
                on_the_ground = false;
            }
    }
    if (map_x == 0 || map_x == (mapdata.max_x)* TILE_SIZE - SCREEN_WIDTH)
    {
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;
    }
}
void MainObject::centre_on_map(MAP& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH /2);
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }else if (map_data.start_x + SCREEN_WIDTH >= (map_data.max_x + 1) *TILE_SIZE)
    {
        map_data.start_x = (map_data.max_x + 1) * TILE_SIZE - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }else if (map_data.start_y + SCREEN_HEIGHT >= (map_data.max_y + 1) * TILE_SIZE)
    {
        map_data.start_y = (map_data.max_y + 1) * TILE_SIZE- SCREEN_HEIGHT;
    }
}
void MainObject::loseHp(const int &damage)
{
    if (damage == BOSS_DAMAGE && timeSinceLastLoseHp.count() >= 1400)
    {
        hp-=damage;
        lastLoseHp = currentTime;


    }else if (damage == ENEMY_DAMGE && timeSinceLastLoseHp.count() >= 150 * 4)
    {
        hp -=damage;
        lastLoseHp = currentTime;
    }
}
void MainObject::die(Graphics &graphics)
{
    dieRect.x = rect.x;
    dieRect.y = rect.y;
    if (timeSinceLastDie.count() >= 150)
    {
        frame_die++;
        lastDie = currentTime;
    }
    if (status == walkRight && frame_die <= 4)
    {
        SDL_Rect* currentClip = &frame_clip_die[frame_die];
        graphics.RenderFrame(dieRight, currentClip, dieRect);
    }else if (frame_die <= 4){
        SDL_Rect* currentClip = &frame_clip_die[4 - frame_die];
        graphics.RenderFrame(dieLeft, currentClip, dieRect);
    }

}
void MainObject::reset()
{
    rect.x = 100;
    rect.y = 70;

    y_ =0;
    x_pos = 100;
    y_pos = 70;
    map_x = 0;
    map_y = 0;

    frame_walk = -1;
    frame_attack = -1;
    frame_shoot = -1;
    frame_jump = -1;
    frame_skill = -1;
    frame_die = -1;

    status = walkRight;

    hp = Main_Max_Hp;
    on_the_ground = false;
    up_ = false; down_ = false; left_ = false; right_ = false; attack_ = false; shoot_= false; skill_ = false;
}
void MainObject::loadSound(Graphics& graphics)
{
    gJump = graphics.loadSound("assets/jump.wav");
    gAttack = graphics.loadSound("assets/attack.wav");
    gSkill = graphics.loadSound("assets/skill.wav");
    gShoot = graphics.loadSound("assets/shoot.mp3");
    Mix_VolumeChunk(gSkill, MIX_MAX_VOLUME /3);
}
