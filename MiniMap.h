#ifndef _MINIMAP_H
#define _MINIMAP_H

#include "Graphics.h"
#include "defs.h"
#include "GameMap.h"
class MiniMap
{
private:
    SDL_Color color;
    int x;
    int y;
    SDL_Rect mainRect;
    SDL_Rect tileRect;
    SDL_Rect miniMapRect;
    SDL_Texture* miniMap;
public:
    MiniMap(Graphics &graphics)
    {
        x = 1000;
        y = 100;
        mainRect.w = 5;
        mainRect.h = 5;
        tileRect.w = 1.0/( MAX_MAP_X) * (2 * MINI_MAP_RADIUS) + 1;
        tileRect.h = 1.0/( MAX_MAP_Y) * (2 * MINI_MAP_RADIUS);
        miniMap = graphics.loadTexture("MAP/mini_map.png");
        miniMapRect.w = MINI_MAP_RADIUS * 2 + 10;
        miniMapRect.h = MINI_MAP_RADIUS * 2 + 10;
        miniMapRect.x = x - MINI_MAP_RADIUS -5;
        miniMapRect.y = y - MINI_MAP_RADIUS -5;
    }
    ~MiniMap(){;}
    void RenderCharacter(const float& x_pos, const float& y_pos, Graphics &graphics)
    {
        color = {255, 0, 0, 255};
        graphics.setColor(color);
        mainRect.x = x_pos / (TILE_SIZE * MAX_MAP_X) * (2 * MINI_MAP_RADIUS) + x - MINI_MAP_RADIUS;
        mainRect.y = y_pos / (TILE_SIZE * MAX_MAP_Y) * (2 * MINI_MAP_RADIUS) + y - MINI_MAP_RADIUS;
        int i = mainRect.x - x;
        int j = mainRect.y - y;
        if (i*i + j*j <= MINI_MAP_RADIUS* MINI_MAP_RADIUS + 100)
        {
            graphics.drawRectangle(mainRect);
        }
    }
    void RenderMap(MAP& mapdata, Graphics &graphics)
    {
        //float x1, y1;

        color = {255, 255, 128, 255};
        graphics.setColor(color);
        for (int i=6; i<= 8; i++)
        {
            for (int j = 0; j < MAX_MAP_X; j++)
            {
                switch (mapdata.tile[i][j])
                {
                case 1:
                case 9:
                case 14:
                case 6:
                case 7:
                case 2:
                case 3:
                    tileRect.x = (float)j/( MAX_MAP_X) * (2 * MINI_MAP_RADIUS) + x - MINI_MAP_RADIUS;
                    tileRect.y= (float)i/(MAX_MAP_Y) * (2 * MINI_MAP_RADIUS) + y - MINI_MAP_RADIUS - 15;
                    graphics.drawRectangle(tileRect);
                    break;
                }
            }
        }
    }
    void RenderMiniMap(MAP &mapdata, const float& x_pos, const float& y_pos,Graphics &graphics)
    {
        graphics.RenderObject(miniMap,miniMapRect );
        RenderMap(mapdata, graphics);
        RenderCharacter(x_pos, y_pos, graphics);
    }

};
#endif // _MINIMAP_H
