#ifndef _Graphics_H
#define _Graphics_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <SDL_keyboard.h>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <string>
#include "defs.h"
using namespace std;

struct Graphics
{
    SDL_Texture* health_bar;
    SDL_Texture* bar_img;
    SDL_Texture* skill_j;
    SDL_Texture* skill_k;
    SDL_Texture* skill_l;

    SDL_Renderer * renderer;
    SDL_Window *window;

    SDL_Rect hpRect;
    SDL_Rect skillRect;

    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* initSDL();
    SDL_Renderer* createRenderer();
    void quitSDL();
    void waitUntilKeyPressed();

    SDL_Texture *loadTexture(const char *filename);
    void RenderObject(SDL_Texture* texture, SDL_Rect rect);
    void RenderFrame(SDL_Texture* texture, SDL_Rect* currentFrame,const SDL_Rect &rect);
    void RenderBackground(SDL_Texture* background);
    void PresentScr();
    void RenderHealthBar();
    void RenderBossHealthBar(const SDL_Rect &bossRect, const int &bossHp, const int &MAX_HP);
    void Init();
    void ClearScr();
    void RenderSkill(const float &coolDownTimeSkill, const float &coolDownTimeAttack, const float &coolDownTimeShoot);
    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* createText(const char* text, TTF_Font* font, SDL_Color textColor);
    Mix_Music *loadMusic(const char* path);
    void playMusic(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void playSound(Mix_Chunk* gChunk);
    void setColor(const SDL_Color &color);
    void drawPoint(const int&x, const int& y){SDL_RenderDrawPoint(renderer, x, y); }
    void drawRectangle(const SDL_Rect& rect){SDL_RenderFillRect(renderer, &rect);}
    void drawLine(const float&x1, const float &y1, const float& x2, const float &y2){SDL_RenderDrawLine(renderer,x1,y1, x2, y2 );}
};

    struct MAP
    {
        float start_x;
        float start_y;

        int max_x;
        int max_y;

        int tile[MAX_MAP_Y][MAX_MAP_X];

        string name;

    };
#endif // _BaseFunc_H
