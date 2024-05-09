#ifndef MENU_H
#define MENU_H

#include "Graphics.h"

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
    SDL_Texture* continueGame;
    SDL_Texture* playAgain;
    SDL_Texture* instruction;
    SDL_Texture* guideMenu;
    SDL_Texture* Back;

    SDL_Rect newGameRect;
    SDL_Rect exitRect;
    SDL_Rect textRect;
    SDL_Rect resultRect;
    SDL_Rect continueRect;
    SDL_Rect guideRect = {SCREEN_WIDTH/2 - 250/2, 650, 250, 50};
    SDL_Rect backButton = {20, 20, 100, 25};

    int result;
    int optionResult;

public:
    Menu(Graphics &graphics)
    {
        font = graphics.loadFont("assets/ArchivoNarrow-VariableFont_wght.ttf", 100);
        color = {0, 0, 0, 255};
        newGame = graphics.createText("New Game", font, color);
        exit = graphics.createText("Exit", font, color);
        playAgain = graphics.createText("Play Again !", font, color);
        continueGame = graphics.createText("Continue", font, color);
        instruction = graphics.createText("Guide", font , color);

        menuBackGround = graphics.loadTexture("IMG/Menu.png");
        option = graphics.loadTexture("IMG/Option.png");

        newGameRect.x = SCREEN_WIDTH/2 - 150;
        newGameRect.y = SCREEN_HEIGHT/2 ;
        newGameRect.w = 300;
        newGameRect.h = 50;

        continueRect.x = newGameRect.x;
        continueRect.y = newGameRect.y - 100;
        continueRect.w = newGameRect.w;
        continueRect.h = newGameRect.h;

        exitRect.x = newGameRect.x;
        exitRect.y = newGameRect.y + 100;
        exitRect.w = newGameRect.w ;
        exitRect.h = newGameRect.h;

        resultRect.x = SCREEN_WIDTH/2 - 130;
        resultRect.y = SCREEN_HEIGHT/2 - 120;
        resultRect.w = 260;
        resultRect.h = 100;

        color = {255, 0, 0, 255};
        loseGame = graphics.createText("You Loose!", font, color);
        winGame = graphics.createText("You Win!", font, color);

        result = pause;
        optionResult =Continue;
        guideMenu = graphics.loadTexture("IMG/Guide.png");

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
            }else if (x >= guideRect.x && x <= guideRect.x + guideRect.w && y >= guideRect.y && y <= guideRect.y + guideRect.h)
            {
                quitGame = false;
                quitMenu = false;
                optionResult = guide;
            }else if (x >= backButton.x && x <= backButton.x + backButton.w && y >= backButton.y && y <= backButton.y + backButton.h)
            {
                optionResult = go_back;
            }
        }
        RenderMenu(graphics);
        renderInstruction(graphics, x, y);
        SDL_Delay(20);
    }
    enum resultType{
        pause = 2,
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
            graphics.RenderObject(loseGame, resultRect);
        }
        else if (result == win)
        {
            graphics.RenderObject(winGame, resultRect);
        }else if (result == pause)
        {
                graphics.RenderObject(option, continueRect);
                textRect.x = SCREEN_WIDTH/2 - 80;
                textRect.y = continueRect.y + 10;
                textRect.w = 160;
                graphics.RenderObject(continueGame, textRect);
        }

    }
    void handleOptionAfterGame(SDL_Event &event, bool &quitMenu, bool &quitGame, Graphics &graphics)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (result == pause)
        {
            if (x >= continueRect.x && x <= continueRect.x + continueRect.w && y >= continueRect.y && y <= continueRect.y + continueRect.h)
            {
                color = {255, 0, 0, 255};
                continueGame = graphics.createText("Continue", font, color);

            }else{
                color = {0, 0, 0, 255};
                continueGame = graphics.createText("Continue", font, color);
            }
        }
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

        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            if (x >= continueRect.x && x <= continueRect.x + continueRect.w && y >= continueRect.y && y <= continueRect.y + continueRect.h && result == pause)
            {
                optionResult = Continue;
                quitGame = false;
                quitMenu = true;
            }
            else if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
            {
                optionResult = restart;
                quitGame = false;
                quitMenu = true;
            }
            else if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
            {
                quitGame = true;
                quitMenu = true;
            }
            else if (x >= guideRect.x && x <= guideRect.x + guideRect.w && y >= guideRect.y && y <= guideRect.y + guideRect.h)
            {
                quitGame = false;
                quitMenu = false;
                optionResult = guide;
            }else if (x >= backButton.x && x <= backButton.x + backButton.w && y >= backButton.y && y <= backButton.y + backButton.h)
            {
                optionResult = go_back;
            }
        }
        menuAfterGame(graphics);
        renderInstruction(graphics, x, y);
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
    enum option_result
    {
        Continue = 0,
        restart = 1,
        guide = 2,
        go_back = 3,
    };

    int getOption()
    {
        return optionResult;
    }
    void renderInstruction(Graphics& graphics, const int& x, const int& y)
    {
        if (optionResult == guide)
        {
            if (x >= backButton.x && x <= backButton.x + backButton.w && y >= backButton.y && y <= backButton.y + backButton.h)
            {
                color = {255, 0, 0, 255};
                Back= graphics.createText("BACK", font, color);
            }else{
                color = {255, 255, 0, 255};
                Back= graphics.createText("BACK", font, color);
            }
            graphics.RenderBackground(guideMenu);
            graphics.RenderObject(Back, backButton);
            return;
        }
        if (x >= guideRect.x && x <= guideRect.x + guideRect.w && y >= guideRect.y && y <= guideRect.y + guideRect.h)
        {
            color = {255, 0, 0, 255};
            instruction= graphics.createText("GUIDE", font, color);

        }else{
            color = {255, 255, 0, 255};
            instruction = graphics.createText("GUIDE", font, color);
        }
        graphics.RenderObject(instruction,guideRect );
    }
};
#endif // MENU_H
