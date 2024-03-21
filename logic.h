#ifndef _LOGIC__H
#define _LOGIC__H
#include "BaseFunc.h"
#include "MainObject.h"
#include "GameMap.h"
#include "defs.h"
#include "BossObject.h"
#include "EnemyObject.h"
#include "Menu.h"
using namespace std::chrono;

struct Game
{
    MainObject character;
    SDL_Texture* background;
    SDL_Texture* bull;
    SDL_Rect attackRect;
    SDL_Rect mainRect;

    BulletObject bullet;
    GameMap game_map;
    MAP mapdata ;
    SDL_Event event;
    bool quitMenu;

    BossObject boss;
    SDL_Rect bossRect;
    bool is_init_boss = false;
    SDL_Rect bossAttackRect;

    vector <EnemyObject *> list_of_enemy;
    float enemy_x_pos = 23*TILE_SIZE;
    int enemy_num = 0;

    enum walkType{
        walkRight = 0,
        walkLeft = 1,
    };
    Game()
    {

    }
    void doMenu(bool &quit, Menu& menu, Graphics& graphics)
    {
        menu.RenderMenu(graphics);
        graphics.PresentScr();
        quitMenu = false;
        while(!quitMenu)
        {
            while(SDL_PollEvent(&event) != 0)
            {
                menu.handleOption(event, quitMenu, quit, graphics);
                graphics.PresentScr();
            }
        }
    }
    void doMenuAfterGame(bool &quit, Menu& menu, Graphics& graphics)
    {
        menu.menuAfterGame(graphics);
        graphics.PresentScr();
        quitMenu = false;
        restartGame(graphics);
        while(!quitMenu)
        {
            while(SDL_PollEvent(&event) != 0)
            {
                menu.handleOptionAfterGame(event, quitMenu, quit, graphics);
                graphics.PresentScr();
            }
        }
    }
    void InitEnemy(Graphics& graphics)
    {
        EnemyObject* enemy = new EnemyObject();
        enemy->setImg(graphics);
        enemy->set_clip_attack();
        enemy->set_clip_run();
        enemy->set_clip_hurt();
        enemy->set_clip_die();
        enemy->setPos(enemy_x_pos , 6 * TILE_SIZE -Height_enemy_object, mapdata.start_x, mapdata.start_y);
        list_of_enemy.push_back(enemy);
        enemy_x_pos += 8.5 *TILE_SIZE;
        enemy_num ++;
    }
    void InitBoss(Graphics &graphics)
    {
        boss.setImg(graphics);
        boss.set_clip_run();
        boss.set_clip_attack();
        boss.set_clip_die();
        //graphics.RenderObject(boss.get_texture_left)
    }
    void InitPlayer(Graphics &graphics){
    //MainObject character;
    character.setRect(70, 100);
    mainRect = character.getRect();
    character.setTexture("IMG/Character_Right.png", graphics);
    mainRect = character.getRect();
    character.setclip();
    character.set_clip_jump();
    character.set_clip_attack();
    character.set_clip_shoot();
    character.set_clip_skill();
    character.set_clip_die();

    bull = graphics.loadTexture("IMG/Phitieu.png");
    character.setImg(graphics);
    graphics.health_bar = graphics.loadTexture("IMG/Bar.png");
    graphics.bar_img = graphics.loadTexture("IMG/Bar_Img.png");
    graphics.skill_j = graphics.loadTexture("IMG/Attack.png");
    graphics.skill_k = graphics.loadTexture("IMG/Shoot.png");
    graphics.skill_l = graphics.loadTexture("IMG/Skill.png");

    graphics.hpRect.x = 75;
    graphics.hpRect.y = 24;
    graphics.hpRect.w = 190;
    graphics.hpRect.h = 17;
    attackRect = character.get_attack_rect();

    }
    void InitMap(Graphics& graphics)
    {
    background = graphics.loadTexture("IMG/background.jpg");
    graphics.RenderBackground(background);
    game_map.loadMap();
    game_map.loadMapTiles(graphics);
    }
    void Init(Graphics& graphics)
    {
        InitBoss(graphics);
        InitPlayer(graphics);
        InitMap(graphics);
        mapdata = game_map.get_map_data();
        mapdata.start_x = 0;
        mapdata.start_y = 0;
    }

    void handleBullet(Graphics &graphics)
    {
        vector <BulletObject*> list_of_bullets = character.get_list_bullet();
        vector <SDL_Rect> bulletRects;
        //ĐẠN
        for(vector <BulletObject*>::iterator it = list_of_bullets.begin(); it != list_of_bullets.end();)
        {
            BulletObject *p_bullet = *it;
            if(p_bullet!= NULL )
            {
            if (p_bullet->isMoving()){
                    p_bullet->MoveBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_Rect bulletRect = p_bullet->getRect();
                    bulletRects.push_back(bulletRect);
                    ++it;
            }else{
                it =list_of_bullets.erase(it);
            }
        }
        }
        for (long long unsigned i=0; i < bulletRects.size(); i++)
        {
            //vẽ đạn
            graphics.RenderObject(bull, bulletRects[i]);
        }
        checkColision3(graphics, list_of_bullets);
        checkColision4(graphics, list_of_bullets);
        bulletRects.clear();
    }

    void doPlayer(bool &quit, Graphics &graphics)
    {
        character.setTime();
        character.setMapXY(mapdata.start_x, mapdata.start_y);
        character.centre_on_map(mapdata);
        game_map.setMap(mapdata);
        if (character.getHp() <= 0){
            character.die(graphics);
        }
    else{
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }else
            {
                character.Action(event);
            }
        }
        character.Jump(graphics);
        character.walk(mapdata, graphics);
        character.MoveInAir(mapdata, graphics);
        handleBullet(graphics);
        character.shoot(graphics);
        character.attack(graphics);
        character.skill(graphics, mapdata);
        character.renderPlayerNotMove(graphics);

    }
    }
    void HandleBossRun(Graphics& graphics)
    {
        bossRect = boss.getRect();
        if (character.get_x_pos() - boss.get_x_pos() >Width_main_object + bossAttackRect.w - Width_boss_object && character.get_x_pos() - boss.get_x_pos() <= SCREEN_WIDTH )
        {
            boss.change_status_attack(false);
            boss.change_status_run(true);
            boss.Run(graphics);

        }else if (boss.get_x_pos() - character.get_x_pos() > bossAttackRect.w - Width_boss_object && boss.get_x_pos() - character.get_x_pos() <= SCREEN_WIDTH)
        {
            boss.change_status_attack(false);
            boss.change_status_run(true);
            boss.Run(graphics);
        }
    }
    void setBoss()
    {
        if (character.get_x_pos() > 82 * TILE_SIZE && is_init_boss == false)
        {
            is_init_boss = true;
            boss.setPos(100 * TILE_SIZE, 8 * TILE_SIZE - Height_boss_object, mapdata.start_x, mapdata.start_y);
        }
    }

    void doBoss(Graphics &graphics)
    {
        boss.setToMap(mapdata.start_x, mapdata.start_y);
        boss.setTime();
        if (boss.getHp() <= 0)
        {
            boss.Die(graphics);
        }else{
        if (character.get_x_pos() - boss.get_x_pos() > 0 && boss.get_frame_attack() == 6)
        {
            boss.setStatus(walkRight); //Right

        }else if (boss.get_frame_attack() == 6){
            boss.setStatus(walkLeft);
        }
        if (boss.get_frame_attack() == 6)
        {
            HandleBossRun(graphics);
        }
        if ((boss.get_x_pos() - character.get_x_pos() <= bossAttackRect.w - Width_boss_object && boss.get_x_pos() - character.get_x_pos() > 0) ||
            (-boss.get_x_pos() + character.get_x_pos() <=Width_main_object + bossAttackRect.w - Width_boss_object && -boss.get_x_pos() + character.get_x_pos() >0))
             {
                 boss.change_status_attack(true);
                 boss.change_status_run(false);
             }
        boss.Attack(graphics);
        }
    }

    void doEnemy(Graphics &graphics)
    {
        for (vector <EnemyObject*>::iterator it = list_of_enemy.begin(); it != list_of_enemy.end();)
        {
            EnemyObject* p_enemy = *it;
            if (p_enemy->getHp() <= 0){
                if (p_enemy->getFrameDie() <= 3)
                {
                    p_enemy->setToMap(mapdata.start_x, mapdata.start_y);
                    p_enemy->setTime();
                    p_enemy->Die(graphics);
                    it ++;
                }else{
                    list_of_enemy.erase(it);
                }
            }
            else
            {
                p_enemy->setTime();
                p_enemy->setToMap(mapdata.start_x, mapdata.start_y);
                p_enemy->check_to_map(mapdata);
                if (p_enemy->get_status_hurt()== false && p_enemy->get_x_pos() - character.get_x_pos() <= mainRect.w + p_enemy->getAttackRect().w - p_enemy->getRect().w && p_enemy->get_x_pos() - character.get_x_pos()>= 0)
                {
                        p_enemy->setStatus(walkLeft);
                        p_enemy->change_status_attack(true);

                }else if(p_enemy->get_status_hurt()== false && -p_enemy->get_x_pos() + character.get_x_pos() <= mainRect.w/2 + p_enemy->getAttackRect().w - p_enemy->getRect().w && -p_enemy->get_x_pos() + character.get_x_pos()>= 0)
                {
                    p_enemy->setStatus(walkRight);
                    p_enemy->change_status_attack(true);
                }
                p_enemy->Run(graphics);
                p_enemy->Hurt(graphics);
                p_enemy->Attack(graphics);
                it ++;
            }
        }
    }

    void checkColision1(Graphics &graphics)// boss attack player
    {
        bool col1 = false; // boss attack player
        mainRect = character.getRect();
        bossRect = boss.getRect();
        bossAttackRect = boss.getAttackRect();
        if (boss.get_status_attack() == true && boss.getStatus() == walkRight && boss.get_frame_attack() >= 4) //Right
        {
            if (character.get_y_pos() + mainRect.h < boss.get_y_pos())
            {
                col1 = false;
            }else if (mainRect.x > bossRect.x + bossAttackRect.w)
            {
                col1 = false;
            }else if (mainRect.x + mainRect.w < bossAttackRect.x  /*+ bossRect.w*/)
            {
                col1 = false;
            }else if (character.get_y_pos() > boss.get_y_pos() + bossRect.h)
            {
                col1 = false;
            }else {col1  = true;}
        }else if (boss.get_status_attack() == true && boss.getStatus() == walkLeft && boss.get_frame_attack() >= 4) // Left
        {
            if (character.get_y_pos() + mainRect.h < boss.get_y_pos())
            {
                col1 = false;
            }else if (mainRect.x + mainRect.w < bossAttackRect.x)
            {
                col1 = false;
            }else if (mainRect.x > bossRect.x)
            {
                col1 = false;
            }else if (character.get_y_pos() > boss.get_y_pos() + bossRect.h )
            {
                col1  = false;
            }else {col1 = true;}
        }
        if (col1 == true )
        {
                character.loseHp(BOSS_DAMAGE);
                graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
        }
    }
void checkColision2(Graphics &graphics) //Player Attack Boss
{
        bool col2 = false;
        mainRect = character.getRect();
        bossRect = boss.getRect();
        attackRect = character.get_attack_rect();
    if (character.get_status_attack() == true)
    {
        if ( character.getStatus() == walkRight && character.get_attack_frame() >= 1)
        {
            if (character.get_y_pos() + attackRect.h < boss.get_y_pos()){col2 = false;}
            else if (character.get_y_pos() > boss.get_y_pos() + bossRect.h){col2 = false;}
            else if (mainRect.x + attackRect.w < bossRect.x + bossRect.w /3){col2 = false;}
            else if (mainRect.x + mainRect.w > bossRect.x + bossRect.w){col2 = false;}
            else {col2 = true;}
        }else if (character.getStatus() == walkLeft && character.get_attack_frame() >= 1)
        {
            if (character.get_y_pos() + attackRect.h < boss.get_y_pos()){col2 = false;}
            else if (character.get_y_pos() > boss.get_y_pos() + bossRect.h){col2 = false;}
            else if (attackRect.x > bossRect.x + bossRect.w - bossRect.w /3){col2 = false;}
            else if (mainRect.x < bossRect.x){col2 = false;}
            else {col2 = true;}
        }
        if (col2 == true ){
            boss.loseHp(ATTACK_DAMGE);
            //cerr << boss.getHp() << endl;
        }
    }
    else if (character.get_status_skill() == true)
    {
            if (character.get_y_pos() + mainRect.h < boss.get_y_pos()){col2 = false;}
            else if (character.get_y_pos() > boss.get_y_pos() + bossRect.h){col2 = false;}
            else if (mainRect.x + mainRect.w < bossRect.x){col2 = false;}
            else if (mainRect.x > bossRect.x + bossRect.w - bossRect.w /3) {col2 = false;}
            else {col2 = true;}
            if (col2 == true ){
            boss.loseHp(SKILL_DAMGE);
            }
    }
}
    void checkColision3(Graphics &graphics, vector <BulletObject*> &list_of_bullets)// Player shoot boss
    {
        bossRect = boss.getRect();
        for (vector <BulletObject*>::iterator it = list_of_bullets.begin(); it != list_of_bullets.end(); it++)
        {
            bool col3 = false;
            BulletObject* p_bullet = *it;
            SDL_Rect bulletRect = p_bullet->getRect();
            if(bulletRect.y + bulletRect.h < bossRect.y)
            {
                col3 = false;
            }else if (bulletRect.y > bossRect.y + bossRect.h )
            {
                col3 = false;
            }else if (bulletRect.x +bulletRect.w < bossRect.x + bossRect.w /3)
            {
                col3 = false;
            }else if (bulletRect.x > bossRect.x + bossRect.w - bossRect.w /3)
            {
                col3 = false;
            }else {col3 = true;}
            if (col3 == true)
            {
                p_bullet ->setmove(false);
                boss.loseHp(SHOOT_DAMGE);
            }
        }
    }
    void checkColision4(Graphics &graphics, vector <BulletObject*> &list_of_bullets) // Player shoot enemy
    {
        for (vector <EnemyObject*>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            EnemyObject *p_enemy = *it_enemy;
            for (vector <BulletObject* >::iterator it_bullet= list_of_bullets.begin(); it_bullet != list_of_bullets.end(); it_bullet++)
            {
                bool col4 = false;
                BulletObject* p_bullet = *it_bullet;
                SDL_Rect bulletRect = p_bullet->getRect();

                if (bulletRect.y + bulletRect.h < p_enemy->getRect().y){col4 = false;}
                else if (bulletRect.y > p_enemy->getRect().y + p_enemy->getRect().h) {col4 = false;}
                else if (bulletRect.x +bulletRect.w < p_enemy->getRect().x) {col4 = false;}
                else if (bulletRect.x > p_enemy->getRect().x + p_enemy->getRect().w) {col4 = false;}
                else {col4  = true;}

                if (col4 == true)
                {
                    p_enemy->loseHp(SHOOT_DAMGE, graphics);
                    p_bullet->setmove(false);

                }
            }
        }
    }
    void checkColision5(Graphics& graphics)//Player attack enemy
    {
        attackRect = character.get_attack_rect();
        mainRect = character.getRect();
        for (vector <EnemyObject *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            EnemyObject *p_enemy = *it_enemy;
            if (character.get_status_attack() == true)
            {
                bool col5 = false;
                if ( character.getStatus() == walkRight && character.get_attack_frame() >= 1)
                {
                    if (character.get_y_pos() + attackRect.h < p_enemy->get_y_pos()){col5 = false;}
                    else if (character.get_y_pos() > p_enemy->get_y_pos() + p_enemy->getRect().h){col5 = false;}
                    else if (mainRect.x + attackRect.w < p_enemy->getRect().x ){col5 = false;}
                    else if (mainRect.x + mainRect.w > p_enemy->getRect().x + p_enemy->getRect().w){col5 = false;}
                    else {col5 = true;}
                }else if (character.getStatus() == walkLeft && character.get_attack_frame() >= 1)
                {
                    if (character.get_y_pos() + attackRect.h < p_enemy->get_y_pos()){col5 = false;}
                    else if (character.get_y_pos() > p_enemy->get_y_pos() + p_enemy->getRect().h){col5 = false;}
                    else if (attackRect.x > p_enemy->getRect().x + p_enemy->getRect().w){col5 = false;}
                    else if (mainRect.x < p_enemy->getRect().x){col5 = false;}
                    else {col5 = true;}
                }
                if (col5 == true){
                    p_enemy->loseHp(ATTACK_DAMGE, graphics);
                    //cerr << p_enemy->getHp() << endl;
                }
            }else if (character.get_status_skill() == true)
            {
                bool col5 = false;
                if (character.get_y_pos() + mainRect.h < p_enemy->get_y_pos()){col5 = false;}
                else if (character.get_y_pos() > p_enemy->get_y_pos() + p_enemy->getRect().h){col5 = false;}
                else if (mainRect.x + mainRect.w < p_enemy->getRect().x){col5 = false;}
                else if (mainRect.x > p_enemy->getRect().x + p_enemy->getRect().w) {col5 = false;}
                else {col5 = true;}
                if (col5 == true)
                {
                    p_enemy->loseHp(SKILL_DAMGE, graphics);
                    //cerr << p_enemy->getHp() << endl;
                }
            }
        }
    }
    void checkColision6(Graphics &graphics)//Enemy attack player
    {
    for (vector <EnemyObject *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
    {
        EnemyObject *p_enemy = *it_enemy;
        bool col6 = false; // Enemy attack player
        if (p_enemy->get_status_attack() == true && p_enemy->getStatus() == walkRight && p_enemy->getFrameAttack() >= 1) //Right
        {
            if (character.get_y_pos() + mainRect.h < p_enemy->get_y_pos())
            {
                col6 = false;
            }else if (mainRect.x > p_enemy->getRect().x + p_enemy->getAttackRect().w)
            {
                col6 = false;
            }else if (mainRect.x + mainRect.w < p_enemy->getAttackRect().x  /*+ bossRect.w*/)
            {
                col6 = false;
            }else if (character.get_y_pos() > p_enemy->get_y_pos() + p_enemy->getRect().h)
            {
                col6 = false;
            }else {col6  = true;}
        }else if (p_enemy->get_status_attack() == true && p_enemy->getStatus() == walkLeft && p_enemy->getFrameAttack() >= 1 ) // Left
        {
            if (character.get_y_pos() + mainRect.h < p_enemy->get_y_pos())
            {
                col6 = false;
            }else if (mainRect.x + mainRect.w < p_enemy->getAttackRect().x)
            {
                col6 = false;
            }else if (mainRect.x > p_enemy->getRect().x)
            {
                col6 = false;
            }else if (character.get_y_pos() > p_enemy->get_y_pos() + p_enemy->getRect().h )
            {
                col6  = false;
            }else {col6 = true;}
        }
        if (col6 == true && p_enemy->getFrameAttack() >= 1)
            {
                character.loseHp(ENEMY_DAMGE);
                graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
            }
        }
    }
    void restartGame(Graphics& graphics)
    {
        list_of_enemy.erase(list_of_enemy.begin(), list_of_enemy.end());
        enemy_num = 0;
        enemy_x_pos = 23*TILE_SIZE;

        is_init_boss = false;
        mapdata.tile[5][82] = 0;
        mapdata.tile[6][82] = 0;
        character.reset();
        boss.reset();
        game_map.setMap(mapdata);

        graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
    }
};

#endif // _LOGIC_H
