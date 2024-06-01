#include "logic.h"
#include "Graphics.h"
#include "Menu.h"

int main(int argc, char* argv[])
{

    bool quit = false;

    Graphics graphics;
    graphics.Init();
    Menu menu(graphics);
    Game game;
    game.Init(graphics);
    MiniMap miniMap(graphics);

    Uint64 frameStart;
    const int frameDelay = 1000 / 60;

    game.continueGame(quit, menu, graphics);

    while(!quit)
    {
        frameStart = SDL_GetPerformanceCounter();

        while (game.enemy_num < game.enemy_max_num)
            {
                game.InitEnemy(graphics);
            }
            graphics.ClearScr();
            graphics.RenderBackground(game.background);
            game.game_map.renderMap(graphics);
            graphics.RenderSkill(game.character.get_time_set_skill(), game.character.get_time_set_attack(), game.character.get_time_set_shoot());

            if (game.list_of_enemy.size() != 0)
            {
                game.doEnemy(graphics);
                game.checkColision5(graphics);//Player attack enemy
                game.checkColision6(graphics);//Enemy attack player
            }
            if (game.is_init_boss == true)
            {
                game.doBoss(graphics);
                graphics.RenderBossHealthBar(game.bossRect, game.boss.getHp(), BOSS_MAX_HP);
                game.checkColision1(graphics);//BossAttackPlayer
                game.checkColision2(graphics);//PlayerAttackBoss
                game.checkColision7(graphics);//BossUseSkillAttack

            }
            if (game.list_of_enemy.size() == 0)
            {
                if (game.character.get_x_pos() > 83 * TILE_SIZE && game.mapdata.tile[5][53] != 12 && game.level == 1)
                {
                    game.mapdata.tile[5][82] = 12;
                    game.mapdata.tile[6][82] = 11;
                }
                game.setBoss();
            }
            graphics.RenderHealthBar();

            miniMap.RenderMiniMap(game.mapdata, game.character.get_x_pos(), game.character.get_y_pos(), graphics);
            game.doPlayer(quit, graphics, menu);
            graphics.PresentScr();
            if (game.character.getFrameDie() == 4 || game.character.getRect().y > SCREEN_HEIGHT)
            {
                if (game.level == 2.5) game.level =2;
                //MessageBox(NULL, "Game Over!", "Infor", MB_OK);
                game.restartGame(graphics);
                menu.setResult(0);//Lose
                game.saveGame(menu);
                game.doMenuAfterGame(quit, menu, graphics);
                graphics.PresentScr();
            }
            if (game.boss.get_frame_die() == 5)
            {
                if (game.level == 2.5) game.level = 2;
                game.restartGame(graphics);
                menu.setResult(1);//Win
                game.saveGame(menu);
                game.doMenuAfterGame(quit, menu, graphics);
                graphics.PresentScr();
            }

        int frameTime = SDL_GetPerformanceCounter() - frameStart;
        if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
    }

    graphics.quitSDL();
    return 0;
}
