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
    SDL_Texture* level;
    SDL_Texture* level1;
    SDL_Texture* level2;

    SDL_Rect levelRect;
    SDL_Rect newGameRect;
    SDL_Rect exitRect;
    SDL_Rect textRect;
    SDL_Rect resultRect;
    SDL_Rect continueRect;
    SDL_Rect guideRect = {SCREEN_WIDTH/2 - 250/2, 650, 250, 50};
    SDL_Rect backButton = {20, 20, 100, 25};

    int Level =0;
    int result;
    int optionResult;
    bool chooseLevel;

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
        level = graphics.createText("Level", font, color);
        level1 = graphics.createText("Level 1", font, color);
        level2 = graphics.createText("level 2", font, color);

        menuBackGround = graphics.loadTexture("IMG/Menu.png");
        option = graphics.loadTexture("IMG/Option.png");
        chooseLevel = false;

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

        levelRect.x = newGameRect.x;
        levelRect.y = exitRect.y + 100;
        levelRect.w = newGameRect.w;
        levelRect.h = newGameRect.h;

        color = {255, 0, 0, 255};
        loseGame = graphics.createText("You Lose!", font, color);
        winGame = graphics.createText("You Win!", font, color);

        result = pause;
        optionResult =Continue;
        guideMenu = graphics.loadTexture("IMG/Guide.png");
        Level = 0;
    }
    ~Menu(){;}
    void renderLevel(Graphics& graphics, SDL_Event &event, bool &quitMenu)
    {
        if (chooseLevel == true)
        {
        graphics.ClearScr();

        textRect.x = SCREEN_WIDTH/2 - 50;
        textRect.y = newGameRect.y + 10;
        textRect.w = 100;
        textRect.h = 30;
        graphics.RenderBackground(menuBackGround);
        graphics.RenderObject(option, newGameRect);
        graphics.RenderObject(level1, textRect);

        textRect.x = SCREEN_WIDTH/2 - 50;

        textRect.y += 100;
        textRect.w = 100;

        graphics.RenderObject(option, exitRect);
        graphics.RenderObject(level2, textRect);
        graphics.RenderObject(Back, backButton);
        handleOptionLevel(event, graphics, quitMenu);
        }
    }
    void handleOptionLevel(SDL_Event &event, Graphics &graphics, bool& quitMenu)
    {
        SDL_DestroyTexture(Back);
        SDL_DestroyTexture(level1);
        SDL_DestroyTexture(level2);

        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x >= backButton.x && x <= backButton.x + backButton.w && y >= backButton.y && y <= backButton.y + backButton.h)
            {
                color = {255, 0, 0, 255};
                Back= graphics.createText("BACK", font, color);
            }else{
                color = {255, 255, 0, 255};
                Back= graphics.createText("BACK", font, color);
            }
        if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
        {
            color = {255, 0, 0, 255};
            level1 = graphics.createText("Level 1", font, color);

        }else{
            color = {0, 0, 0, 255};
            level1 = graphics.createText("Level 1", font, color);

        }

        if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
        {
            color = {255, 0, 0, 255};
            level2 = graphics.createText("Level 2", font, color);

        }else
        {
            color = {0, 0, 0, 255};
            level2 = graphics.createText("Level 2", font, color);
        }
        //while (quitMenu == false || chooseLevel == true)
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (x >= backButton.x && x <= backButton.x + backButton.w && y >= backButton.y && y <= backButton.y + backButton.h)
            {
                chooseLevel = false;
                Level = 0;
            }else if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w && y >= newGameRect.y && y <= newGameRect.y + newGameRect.h)
            {
                Level = 1;
                optionResult = changelevel;
                chooseLevel = false;
                quitMenu = true;
            }else if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
            {
                Level = 2;
                optionResult = changelevel;
                chooseLevel = false;
                quitMenu = true;
            }
        }

    }
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

        textRect.y += 100;
        textRect.w = 100;
        textRect.x = SCREEN_WIDTH/2 - 50;
        graphics.RenderObject(option, levelRect);
        graphics.RenderObject(level, textRect);

    }
    void handleOption(SDL_Event &event, bool &quitMenu, bool &quitGame, Graphics &graphics)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_DestroyTexture(newGame);
        SDL_DestroyTexture(exit);
        SDL_DestroyTexture(level);

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

        if (x >= levelRect.x && x <= levelRect.x + levelRect.w && y >= levelRect.y && y <= levelRect.y + levelRect.h)
        {
            color = {255, 0, 0, 255};
            level = graphics.createText("Level", font, color);

        }else
        {
            color = {0, 0, 0, 255};
            level = graphics.createText("Level", font, color);
        }
        if (chooseLevel == false)
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
            }else if (x >= levelRect.x && x <= levelRect.x + levelRect.w && y >= levelRect.y && y <= levelRect.y + levelRect.h)
            {
                chooseLevel = true;
            }
        }
        RenderMenu(graphics);
        renderInstruction(graphics, x, y);
        renderLevel(graphics, event, quitMenu);
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
        textRect.y += 100;
        textRect.w = 100;
        textRect.x = SCREEN_WIDTH/2 - 50;
        graphics.RenderObject(option, levelRect);
        graphics.RenderObject(level, textRect);
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
        SDL_DestroyTexture(continueGame);
        SDL_DestroyTexture(playAgain);
        SDL_DestroyTexture(exit);
        SDL_DestroyTexture(level);
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
        if (x >= levelRect.x && x <= levelRect.x + levelRect.w && y >= levelRect.y && y <= levelRect.y + levelRect.h)
        {
            color = {255, 0, 0, 255};
            level = graphics.createText("Level", font, color);

        }else
        {
            color = {0, 0, 0, 255};
            level = graphics.createText("Level", font, color);
        }
        if (chooseLevel == false)
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
            }else if (x >= levelRect.x && x <= levelRect.x + levelRect.w && y >= levelRect.y && y <= levelRect.y + levelRect.h)
            {
                chooseLevel = true;
            }
        }

        menuAfterGame(graphics);
        renderInstruction(graphics, x, y);
        renderLevel(graphics, event, quitMenu);
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
        changelevel = 4,
    };

    int getOption()
    {
        return optionResult;
    }
    void renderInstruction(Graphics& graphics, const int& x, const int& y)
    {
        if (optionResult == guide)
        {
            SDL_DestroyTexture(Back);
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
        SDL_DestroyTexture(instruction);
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
    int getLevel(){return Level;}
    void setLevel(const int& Level){this->Level = Level;}
};
#endif // MENU_H
