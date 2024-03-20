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
    SDL_Rect newGameRect;
    SDL_Rect exitRect;
    SDL_Rect textRect;

public:
    Menu(Graphics &graphics)
    {
        font = graphics.loadFont("assets/ArchivoNarrow-VariableFont_wght.ttf", 100);
        color = {0, 0, 0, 255};
        newGame = graphics.createText("New Game", font, color);
        exit = graphics.createText("Exit", font, color);
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
    }
    ~Menu(){;}
    void RenderMenu(Graphics &graphics)
    {
        textRect.x = SCREEN_WIDTH/2 - 70;
        textRect.y = newGameRect.y + 10;
        textRect.w = 140;
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
};
#endif // MENU_H
