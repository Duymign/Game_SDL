#include "BaseFunc.h"

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_ERROR,
                   "%s: %s", msg, error);
    SDL_Quit();
}
SDL_Window* Graphics::initSDL()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    SDL_Window* WINDOW = SDL_CreateWindow("SDL_Test", SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);


    if (WINDOW == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return WINDOW;
}
SDL_Renderer* Graphics::createRenderer()
{

    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (Renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    return Renderer;
}
// ham bao loi

void Graphics::quitSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();

}
void Graphics::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
//Load anh
SDL_Texture* Graphics::loadTexture(const char *filename)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
      }
	return texture;
}

void Graphics::RenderObject(SDL_Texture* texture, SDL_Rect rect)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

void Graphics::RenderFrame(SDL_Texture* texture, SDL_Rect* currentFrame,const SDL_Rect &rect)
    {
        SDL_RenderCopy(renderer, texture, currentFrame, &rect);
    }
void Graphics::RenderBackground(SDL_Texture* background)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
    }
void Graphics::PresentScr()
    {
        SDL_RenderPresent(renderer);
    }
void Graphics::Init()
{
    window = initSDL();
    renderer = createRenderer();
    if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
    }

}
void Graphics::ClearScr()
{
    SDL_RenderClear(renderer);
}
void Graphics::RenderHealthBar()
{
    SDL_Rect barRect;
    barRect.x = 70;
    barRect.y= 20;
    barRect.w = 200;
    barRect.h = 25;
    SDL_Rect imgRect = {40, 0, 45, 45};
    RenderObject(health_bar, barRect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer,  &hpRect);
    RenderObject(bar_img, imgRect);
}
void Graphics::RenderBossHealthBar(const SDL_Rect& bossRect, const int &bossHp, const int &MAX_HP)
{
    SDL_Rect barRect;
    barRect.x = bossRect.x;
    barRect.y= bossRect.y - 60;
    barRect.w = bossRect.w;
    barRect.h = bossRect.h / 13;
    SDL_Rect bossHpRect;
    bossHpRect.x = barRect.x +5;
    bossHpRect.y = barRect.y +2;
    bossHpRect.h = barRect.h - 4;
    bossHpRect.w = (bossRect.w - 10) * (float) bossHp/ MAX_HP;

    RenderObject(health_bar, barRect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer,  &bossHpRect);
}
void Graphics::RenderSkill(const float& coolDownTimeSkill, const float &coolDownTimeAttack, const float &coolDownTimeShoot)
{
    SDL_Rect skill_L_Rect;
    SDL_Rect skill_J_Rect;
    SDL_Rect skill_K_Rect;
    SDL_SetRenderDrawColor(renderer, 0, 199, 255, 255);

    skillRect.x = TILE_SIZE;
    skillRect.y = TILE_SIZE * 10 + 10;
    skillRect.w =50;
    skillRect.h = 50;

    skill_J_Rect.x = skillRect.x;
    skill_J_Rect.w = skillRect.w;
    skill_J_Rect.h = skillRect.h -skillRect.h * coolDownTimeAttack/ timeSetAttack;
    skill_J_Rect.y = skillRect.y + skillRect.h * coolDownTimeAttack/ timeSetAttack;
    if (skill_J_Rect.h <= 0) skill_J_Rect.h =0;
    RenderObject(skill_j, skillRect);
    SDL_RenderFillRect(renderer,  &skill_J_Rect);

    skillRect.x += 100;
    skill_K_Rect.x = skillRect.x;
    skill_K_Rect.w = skillRect.w;
    skill_K_Rect.h = skillRect.h -skillRect.h * coolDownTimeShoot/ timeSetShoot;
    skill_K_Rect.y = skillRect.y + skillRect.h * coolDownTimeShoot/ timeSetShoot;
    if (skill_K_Rect.h <= 0) skill_K_Rect.h =0;
    RenderObject(skill_k, skillRect);
    SDL_RenderFillRect(renderer,  &skill_K_Rect);

    skillRect.x += 100;
    skill_L_Rect.x = skillRect.x;
    skill_L_Rect.w = skillRect.w;
    skill_L_Rect.h = skillRect.h - skillRect.h * coolDownTimeSkill/ timeSetSkill;
    skill_L_Rect.y = skillRect.y + skillRect.h * coolDownTimeSkill/ timeSetSkill;
    if (skill_L_Rect.h <= 0) skill_L_Rect.h =0;
    RenderObject(skill_l, skillRect);
    SDL_RenderFillRect(renderer,  &skill_L_Rect);
}
TTF_Font* Graphics::loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
        return gFont;
    }

    SDL_Texture* Graphics::createText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

    Mix_Music *Graphics::loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void Graphics:: playMusic(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

     Mix_Chunk* Graphics::loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
               "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
        return gChunk;
    }

    void Graphics::playSound(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }
    void Graphics::setColor(const SDL_Color &color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
