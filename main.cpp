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

    game.continueGame(quit, menu, graphics);
    while(!quit)
    {

        while (game.enemy_num < game.enemy_max_num)
            {
                game.InitEnemy(graphics);
            }
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
                graphics.RenderBossHealthBar(game.bossRect, game.boss.getHp(), BOSS_MAX_HP);
                game.checkColision1(graphics);//BossAttackPlayer
                game.checkColision2(graphics);//PlayerAttackBoss
            }
            graphics.RenderHealthBar();
            game.doPlayer(quit, graphics, menu);
            miniMap.RenderMiniMap(game.mapdata, game.character.get_x_pos(), game.character.get_y_pos(), graphics);
            graphics.PresentScr();
            if (game.character.getFrameDie() == 4 || game.character.getRect().y > SCREEN_HEIGHT)
            {
                //MessageBox(NULL, "Game Over!", "Infor", MB_OK);
                game.restartGame(graphics);
                menu.setResult(0);//Lose
                game.saveGame(menu);
                game.doMenuAfterGame(quit, menu, graphics);
                graphics.PresentScr();
            }
            if (game.boss.get_frame_die() == 5)
            {
                game.restartGame(graphics);
                menu.setResult(1);//Win
                game.saveGame(menu);
                game.doMenuAfterGame(quit, menu, graphics);
                graphics.PresentScr();
            }
        SDL_Delay(1000.0/60);
    }

    graphics.quitSDL();
    return 0;
}
