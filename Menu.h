#ifndef MENU_H
#define MENU_H

#include "BaseFunc.h"

class Menu{
private:
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* newGame;
    SDL_Texture* exit;
    SDL_Texture* menuBackGround;
    SDL_Texture* option;
    SDL_Texture* loseGame;
    SDL_Texture* winGame;
    SDL_Texture* playAgain;

    SDL_Rect newGameRect;
    SDL_Rect exitRect;
    SDL_Rect textRect;
    SDL_Rect winGameRect;
    int result;

public:
    Menu(Graphics &graphics)
    {
        font = graphics.loadFont("assets/ArchivoNarrow-VariableFont_wght.ttf", 100);
        color = {0, 0, 0, 255};
        newGame = graphics.createText("New Game", font, color);
        exit = graphics.createText("Exit", font, color);
        playAgain = graphics.createText("Play Again !", font, color);
        menuBackGround = graphics.loadTexture("IMG/Menu.png");
        option = graphics.loadTexture("IMG/Option.png");
        newGameRect.x = SCREEN_WIDTH/2 - 150;
        newGameRect.y = SCREEN_HEIGHT/2 ;
        newGameRect.w = 300;
        newGameRect.h = 50;

        exitRect.x = newGameRect.x;
        exitRect.y = newGameRect.y + 100;
        exitRect.w = newGameRect.w ;
        exitRect.h = newGameRect.h;

        winGameRect.x = SCREEN_WIDTH/2 - 130;
        winGameRect.y = SCREEN_HEIGHT/2 - 120;
        winGameRect.w = 260;
        winGameRect.h = 100;

        color = {255, 0, 0, 255};
        loseGame = graphics.createText("Looser!", font, color);
        winGame = graphics.createText("You Win!", font, color);
        result = lose;
    }
    ~Menu(){;}
    void RenderMenu(Graphics &graphics)
    {
        graphics.ClearScr();
        textRect.x = SCREEN_WIDTH/2 - 80;
        textRect.y = newGameRect.y + 10;
        textRect.w = 160;
        textRect.h = 30;
        graphics.RenderBackground(menuBackGround);
        graphics.RenderObject(option, newGameRect);
        graphics.RenderObject(newGame, textRect);

        textRect.x = SCREEN_WIDTH/2 - 30;

        textRect.y += 100;
        textRect.w = 60;

        graphics.RenderObject(option, exitRect);
        graphics.RenderObject(exit, textRect);
    }
    void handleOption(SDL_Event &event, bool &quitMenu, bool &quitGame, Graphics &graphics)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
        {
            color = {255, 0, 0, 255};
            newGame = graphics.createText("New Game", font, color);

        }else{
            color = {0, 0, 0, 255};
            newGame = graphics.createText("New Game", font, color);

        }

        if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
        {
            color = {255, 0, 0, 255};
            exit = graphics.createText("Exit", font, color);

        }else
        {
            color = {0, 0, 0, 255};
            exit = graphics.createText("Exit", font, color);
        }
        RenderMenu(graphics);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
            {
                quitGame = false;
                quitMenu = true;
            }
            else if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
            {
                quitGame = true;
                quitMenu = true;
            }
        }
        SDL_Delay(20);
    }
    enum resultType{
        win = 1,
        lose = 0,
    };
    void menuAfterGame(Graphics &graphics)
    {
        graphics.ClearScr();
        textRect.x = SCREEN_WIDTH/2 - 80;
        textRect.y = newGameRect.y + 10;
        textRect.w = 160;
        textRect.h = 30;
        graphics.RenderBackground(menuBackGround);
        graphics.RenderObject(option, newGameRect);
        graphics.RenderObject(playAgain, textRect);

        textRect.x = SCREEN_WIDTH/2 - 30;

        textRect.y += 100;
        textRect.w = 60;

        graphics.RenderObject(option, exitRect);
        graphics.RenderObject(exit, textRect);
        if (result == lose)
        {
            graphics.RenderObject(loseGame, winGameRect);
        }
        else if (result == win)
        {
            graphics.RenderObject(winGame, winGameRect);
        }
    }
    void handleOptionAfterGame(SDL_Event &event, bool &quitMenu, bool &quitGame, Graphics &graphics)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
        {
            color = {255, 0, 0, 255};
            playAgain = graphics.createText("Play Again !", font, color);

        }else{
            color = {0, 0, 0, 255};
            playAgain = graphics.createText("Play Again !", font, color);
        }

        if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
        {
            color = {255, 0, 0, 255};
            exit = graphics.createText("Exit", font, color);

        }else
        {
            color = {0, 0, 0, 255};
            exit = graphics.createText("Exit", font, color);
        }
        menuAfterGame(graphics);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
            {
                quitGame = false;
                quitMenu = true;
            }
            else if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
            {
                quitGame = true;
                quitMenu = true;
            }
        }
        SDL_Delay(20);
    }
    int getResult()
    {
       return result;
    }
    void setResult(int result)
    {
        this->result = result;
    }

};
#endif // MENU_H
