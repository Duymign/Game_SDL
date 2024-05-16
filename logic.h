#ifndef _LOGIC__H
#define _LOGIC__H

#include "Graphics.h"
#include "Player.h"
#include "GameMap.h"
#include "defs.h"
#include "Boss.h"
#include "Enemy.h"
#include "Menu.h"
#include "MiniMap.h"
using namespace std::chrono;

struct Game
{
    Player character;
    SDL_Texture* background;
    SDL_Texture* bull;
    SDL_Rect attackRect;
    SDL_Rect mainRect;

    Dart dart;
    GameMap game_map;
    MAP mapdata ;
    SDL_Event event;
    bool quitMenu;

    Boss boss;
    SDL_Rect bossRect;
    bool is_init_boss = false;
    SDL_Rect bossAttackRect;

    vector <Enemy *> list_of_enemy;
    float enemy_x_pos;
    int enemy_max_num =6;
    int enemy_num =0;

    enum walkType{
        walkRight = 0,
        walkLeft = 1,
    };
    Game()
    {
        enemy_num =0;
        enemy_max_num = 6;
        enemy_x_pos = 23*TILE_SIZE;
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

        while(!quitMenu)
        {
            while(SDL_PollEvent(&event) != 0)
            {
                menu.handleOptionAfterGame(event, quitMenu, quit, graphics);
                graphics.PresentScr();
            }
        }
        if (menu.getOption() == Menu::restart) // Restart
            {
                enemy_max_num =6;
                enemy_num =0;
                restartGame(graphics);
            }
    }
    void InitEnemy(Graphics& graphics)
    {
        Enemy* enemy = new Enemy();
        enemy->setImg(graphics);
        enemy->set_clip_attack();
        enemy->set_clip_run();
        enemy->set_clip_hurt();
        enemy->set_clip_die();
        enemy->loadSound(graphics);
        enemy->setPos(enemy_x_pos , 6 * TILE_SIZE -Height_enemy_object, mapdata.start_x, mapdata.start_y);
        list_of_enemy.push_back(enemy);
        enemy_x_pos += 8.5 *TILE_SIZE;
        enemy_num++;
    }
    void InitBoss(Graphics &graphics)
    {
        boss.setImg(graphics);
        boss.set_clip_run();
        boss.set_clip_attack();
        boss.set_clip_die();
        boss.set_clip_skill();
        boss.loadSound(graphics);
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
    character.loadSound(graphics);

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

    void handleDart(Graphics &graphics)
    {
        vector <Dart*> list_of_darts = character.get_list_bullet();
        vector <SDL_Rect> dartRects;
        //ĐẠN
        for(vector <Dart*>::iterator it = list_of_darts.begin(); it != list_of_darts.end();)
        {
            Dart *p_dart = *it;
            if(p_dart!= NULL )
            {
            if (p_dart->isMoving()){
                    p_dart->MoveDart(SCREEN_WIDTH, SCREEN_HEIGHT);
                    SDL_Rect dartRect = p_dart->getRect();
                    dartRects.push_back(dartRect);
                    ++it;
            }else{
                it =list_of_darts.erase(it);
            }
        }
        }
        for (long long unsigned i=0; i < dartRects.size(); i++)
        {
            //vẽ đạn
            graphics.RenderObject(bull, dartRects[i]);
        }
        checkColision3(graphics, list_of_darts);
        checkColision4(graphics, list_of_darts);
        dartRects.clear();
    }

    void doPlayer(bool &quit, Graphics &graphics, Menu& menu)
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
                saveGame(menu);
            }else
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_p)
                    {
                        menu.setResult(2);
                        saveGame(menu);
                        doMenuAfterGame(quit, menu, graphics);
                    }
                }
                character.Action(event);
            }
        }
        character.Jump(graphics);
        character.walk(mapdata, graphics);
        character.MoveInAir(mapdata, graphics);
        handleDart(graphics);
        character.shoot(graphics);
        character.attack(graphics);
        character.skill(graphics, mapdata);
        character.renderPlayerNotMove(graphics);

    }
    }
    void HandleBossRun(Graphics& graphics)
    {
        bossRect = boss.getRect();
        if (character.get_x_pos() - boss.get_x_pos() > 0 && boss.get_frame_attack() == 6)
            {
                boss.setStatus(walkRight); //Right
            }else if (boss.get_frame_attack() == 6){
                boss.setStatus(walkLeft);
            }
        if (character.get_x_pos() - boss.get_x_pos() >Width_main_object + bossAttackRect.w - Width_boss_object &&
            character.get_x_pos() - boss.get_x_pos() <= SCREEN_WIDTH )
        {
            boss.change_status_attack(false);
            boss.change_status_run(true);
            boss.Run(graphics);

        }else if (boss.get_x_pos() - character.get_x_pos() > bossAttackRect.w - Width_boss_object &&
                  boss.get_x_pos() - character.get_x_pos() <= SCREEN_WIDTH)
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
    bool checkNearCharacter()
    {
        if (boss.get_x_pos() - character.get_x_pos() <= bossAttackRect.w - Width_boss_object && boss.get_x_pos() - character.get_x_pos() > 0)
        {
            //character ở bên trái boss
            return true;
        }else if (-boss.get_x_pos() + character.get_x_pos() <= Width_main_object + bossAttackRect.w - Width_boss_object &&
             -boss.get_x_pos() + character.get_x_pos() >0)
             {
                 //character ở bên phải boss
                 return true;
             }
        return false;
    }
    void doBoss(Graphics &graphics)
    {
        boss.setToMap(mapdata.start_x, mapdata.start_y);
        boss.setTime();
        if (boss.getHp() <= 0)
        {
            boss.Die(graphics);
        }else{

            if (boss.get_frame_attack() == 6)
            {
                HandleBossRun(graphics);
            }
            if(checkNearCharacter() == true)
            {
                boss.change_status_attack(true);
                boss.change_status_run(false);
            }
            boss.UseSkill(graphics);
            boss.moveSkill(graphics);

            boss.Attack(graphics);
        }
    }
    void HandleEnemyStatus(Enemy* p_enemy)
    {
        if (p_enemy->get_status_hurt()== false)
        {
                if (p_enemy->get_x_pos() - character.get_x_pos() <= mainRect.w + p_enemy->getAttackRect().w - p_enemy->getRect().w &&
                    p_enemy->get_x_pos() - character.get_x_pos()>= 0)
                    {
                        p_enemy->setStatus(walkLeft);
                        p_enemy->change_status_attack(true);

                }else if(-p_enemy->get_x_pos() + character.get_x_pos() <= mainRect.w/2 + p_enemy->getAttackRect().w - p_enemy->getRect().w &&
                        -p_enemy->get_x_pos() + character.get_x_pos()>= 0)
                {
                    p_enemy->setStatus(walkRight);
                    p_enemy->change_status_attack(true);
                }
        }
    }
    void doEnemy(Graphics &graphics)
    {
        for (vector <Enemy*>::iterator it = list_of_enemy.begin(); it != list_of_enemy.end();)
        {
            Enemy* p_enemy = *it;
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
                p_enemy->check_map_collision(mapdata);
                HandleEnemyStatus(p_enemy);
                p_enemy->Run(graphics);
                p_enemy->Hurt(graphics);
                p_enemy->Attack(graphics);
                graphics.RenderBossHealthBar(p_enemy->getRect(), p_enemy->getHp(), ENEMY_MAX_HP);
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
    void checkColision3(Graphics &graphics, vector <Dart*> &list_of_darts)// Player shoot boss
    {
        bossRect = boss.getRect();
        for (vector <Dart*>::iterator it = list_of_darts.begin(); it != list_of_darts.end(); it++)
        {
            bool col3 = false;
            Dart* p_dart = *it;
            SDL_Rect dartRect = p_dart->getRect();
            if(dartRect.y + dartRect.h < bossRect.y)
            {
                col3 = false;
            }else if (dartRect.y > bossRect.y + bossRect.h )
            {
                col3 = false;
            }else if (dartRect.x +dartRect.w < bossRect.x + bossRect.w /3)
            {
                col3 = false;
            }else if (dartRect.x > bossRect.x + bossRect.w - bossRect.w /3)
            {
                col3 = false;
            }else {col3 = true;}
            if (col3 == true)
            {
                p_dart ->setmove(false);
                boss.loseHp(SHOOT_DAMGE);
            }
        }
    }
    void checkColision4(Graphics &graphics, vector <Dart*> &list_of_darts) // Player shoot enemy
    {
        for (vector <Enemy*>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            Enemy *p_enemy = *it_enemy;
            for (vector <Dart* >::iterator it_dart= list_of_darts.begin(); it_dart != list_of_darts.end(); it_dart++)
            {
                bool col4 = false;
                Dart* p_dart = *it_dart;
                SDL_Rect bulletRect = p_dart->getRect();

                if (bulletRect.y + bulletRect.h < p_enemy->getRect().y){col4 = false;}
                else if (bulletRect.y > p_enemy->getRect().y + p_enemy->getRect().h) {col4 = false;}
                else if (bulletRect.x +bulletRect.w < p_enemy->getRect().x) {col4 = false;}
                else if (bulletRect.x > p_enemy->getRect().x + p_enemy->getRect().w) {col4 = false;}
                else {col4  = true;}

                if (col4 == true)
                {
                    p_enemy->loseHp(SHOOT_DAMGE, graphics);
                    p_dart->setmove(false);
                }
            }
        }
    }
    void checkColision5(Graphics& graphics)//Player attack enemy
    {
        attackRect = character.get_attack_rect();
        mainRect = character.getRect();
        for (vector <Enemy *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            Enemy *p_enemy = *it_enemy;
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
    for (vector <Enemy *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
    {
        Enemy *p_enemy = *it_enemy;
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
    void checkColision7(Graphics &graphics)//Boss Use Skill Attack Player
    {
        float x = boss.get_x_skill_pos();
        float y = boss.get_y_skill_pos();
        bool col7 = false;
        if (y + boss_heigh_skill < character.get_y_pos()){col7 = false;}
        else if (y + 20> character.get_y_pos() + Height_main_Object) {col7 = false;}
        else if (x + boss_width_skill -10 < character.get_x_pos()) {col7 = false;}
        else if (x + 10> character.get_x_pos() + Width_main_object) {col7 = false;}
        else {
            col7  = true;
        }
        if (col7 == true && boss.isUseSkill())
        {
            character.loseHp(BOSS_SKILL_DAMAGE);
            graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
        }

    }
    void restartGame(Graphics& graphics)
    {
        list_of_enemy.erase(list_of_enemy.begin(), list_of_enemy.end());
        enemy_max_num = 6;
        enemy_num =0;
        enemy_x_pos = 23*TILE_SIZE;

        is_init_boss = false;
        mapdata.tile[5][82] = 0;
        mapdata.tile[6][82] = 0;
        character.reset();
        boss.reset();
        game_map.setMap(mapdata);

        graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
    }
    void saveGame(Menu& menu)
    {
        ofstream fileMain("main.txt");
        fileMain << menu.getResult() << " ";
        fileMain << character.get_x_pos() << " " << character.get_y_pos() << " ";
        fileMain << mapdata.start_x <<" " << mapdata.start_y << " ";
        fileMain << character.getHp() << " ";
        fileMain.close();

        ofstream fileEnemy("enemy.txt");

        fileEnemy << (int)list_of_enemy.size() << " ";
        for (vector <Enemy *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            Enemy* p_enemy = *it_enemy;
            fileEnemy << p_enemy->get_x_pos() << " " << p_enemy->get_y_pos() << " "
            << p_enemy->getHp() << " ";
        }
        fileEnemy.close();

        ofstream fileBoss("boss.txt");
        fileBoss << boss.get_x_pos() << " " << boss.get_y_pos() << " " << boss.getHp() << " ";

        fileBoss.close();

    }
    void resumeEnemy(Graphics &graphics)
    {
        ifstream fileEnemy("enemy.txt");

        fileEnemy >> enemy_max_num;

        for (int i=0; i < enemy_max_num; i++)
        {
            InitEnemy(graphics);
        }
        for (vector <Enemy *>::iterator it_enemy = list_of_enemy.begin(); it_enemy != list_of_enemy.end(); it_enemy ++)
        {
            Enemy* p_enemy = *it_enemy;
            float x_pos, y_pos;
            int hp;
            fileEnemy >> x_pos >> y_pos >> hp;
            p_enemy->setPos(x_pos, y_pos, mapdata.start_x, mapdata.start_y);
            p_enemy->setHp(hp);
        }
        fileEnemy.close();
    }
    void resumeBoss()
    {
        ifstream fileBoss("boss.txt");
        float x_pos, y_pos;
        int hp;
        fileBoss >> x_pos >> y_pos >> hp;
        boss.setPos(x_pos, y_pos, mapdata.start_x, mapdata.start_y);
        boss.setHp(hp);
        fileBoss.close();
    }
    void continueGame(bool &quit, Menu &menu, Graphics &graphics)
    {
        float x_pos, y_pos;
        int result, hp;
        ifstream fileMain("main.txt");
        fileMain >> result;
        cout << result << " ";

        //fileMain.seekg(1, ios_base::cur);
        if (result == Menu::pause)
        {
            menu.setResult(Menu::pause);
            fileMain >> x_pos >> y_pos;
            character.setPos(x_pos, y_pos);
            fileMain>>mapdata.start_x >> mapdata.start_y >> hp ;
            character.setMapXY(mapdata.start_x, mapdata.start_y);
            character.setRect(x_pos - mapdata.start_x, y_pos);
            character.setHp(hp);
            graphics.hpRect.w = 190.0 *(float)character.getHp()/Main_Max_Hp;
            character.centre_on_map(mapdata);

            doMenuAfterGame(quit, menu, graphics);
            if (menu.getOption() == Menu::Continue)
            {
                resumeEnemy(graphics);
                resumeBoss();
            }
        }else
        {
            doMenu(quit, menu, graphics);
        }
        fileMain.close();
    }
};

#endif // _LOGIC_H
