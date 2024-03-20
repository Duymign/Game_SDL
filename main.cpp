#include "logic.h"
#include "BaseFunc.h"
#include "Menu.h"
int main(int argc, char* argv[])
{
    high_resolution_clock::time_point lastFrame = high_resolution_clock::now();
    high_resolution_clock::time_point currentTime;
    duration<int, milli> timeSinceLastFrame ;

    bool quit = false;

    Graphics graphics;
    graphics.Init();
    Menu menu(graphics);
    Game game;
    game.Init(graphics);
    while (game.enemy_num < 6)
        {
            game.InitEnemy(graphics);
        }
    game.doMenu(quit, menu, graphics);

    while(!quit)
    {
        currentTime = high_resolution_clock::now();
        timeSinceLastFrame = duration_cast<milliseconds> (currentTime - lastFrame);

        if (timeSinceLastFrame.count() >= 1000.0 / 60)
        {
            graphics.ClearScr();
            graphics.RenderBackground(game.background);
            game.game_map.renderMap(graphics);
            graphics.RenderSkill(game.character.get_time_set_skill(), game.character.get_time_set_attack(), game.character.get_time_set_shoot());
            if (game.list_of_enemy.size() == 0)
            {
                if (game.character.get_x_pos() > 83 * TILE_SIZE && game.mapdata.tile[5][53] != 12)
                {
                    game.mapdata.tile[5][82] = 12;
                    game.mapdata.tile[6][82] = 11;
                }
                game.setBoss();
            }
            if (game.list_of_enemy.size() != 0)
            {
                game.doEnemy(graphics);
                game.checkColision5(graphics);//Player attack enemy
                game.checkColision6(graphics);//Enemy attack player
            }
        if (game.is_init_boss == true)
            {
                game.doBoss(graphics);
                graphics.RenderBossHealthBar(game.bossRect, game.boss.getHp());
                game.checkColision1(graphics);//BossAttackPlayer
                game.checkColision2(graphics);//PlayerAttackBoss
            }
            graphics.RenderHealthBar();
            game.doPlayer(quit, graphics);
            graphics.PresentScr();
            lastFrame = currentTime;
            if (game.character.getFrameDie() == 4){
                MessageBox(NULL, "Game Over!", "Infor", MB_OK);
                quit = true;
            }
            if (game.boss.get_frame_die() == 5)
            {
                MessageBox(NULL, "You Win!", "Infor", MB_OK);
                quit = true;
            }
        }
    }
    graphics.quitSDL();
    return 0;
}
