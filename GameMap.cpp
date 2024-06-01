#include "GameMap.h"

void GameMap:: loadMap(const char* filename)
{

    ifstream file(filename);
    if (file.is_open())
    {
        game_map.max_x = game_map.max_y =0;
    for (int i=0; i < MAX_MAP_Y; i++)
    {
        for (int j=0 ; j < MAX_MAP_X; j++)
        {
            file >> game_map.tile[i][j];
            //file.seekg(1 ,ios_base::cur);
            int val = game_map.tile[i][j];

            if (val > 0)
            {
                if (i > game_map.max_y)
                {
                    game_map.max_y = i;
                }
                if (j > game_map.max_x)
                {
                    game_map.max_x = j;
                }
            }
        }

    }
    //cout << filename + " is open!";
    }else{
        cout << "Can not open file ";
    }

    file.close();
}
void GameMap::loadMapTiles(Graphics &graphics)
{
    for (int i=1; i < MAX_TILE ; i++)
    {
        string num = "MAP/" + to_string(i);
        num += ".png";
        cout << num;
        char Name[num.size()];
        for (unsigned long long j =0; j < num.size(); j++)
        {
            Name[j] = num[j];
        }
        tile_map[i].setTexture(Name, graphics);
    }
}
void GameMap::renderMap(Graphics &graphics)
{
    int x1 = ((int)game_map.start_x % TILE_SIZE) * (-1);
    int y1 = ((int)game_map.start_y % TILE_SIZE) * (-1);
    int map_x = 0;

    int x2 =(x1 + SCREEN_WIDTH) + (x1 == 0 ? 0 : TILE_SIZE);
    int y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
    int map_y = 0;

    //map_y = game_map.start_y/TILE_SIZE;
    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE;
        //map_x =0;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map.tile[map_y][map_x];
            if (val != 0)
            {
                tile_map[val].setRect(j, i, TILE_SIZE, TILE_SIZE);
                graphics.RenderObject(tile_map[val].getTexture(), tile_map[val].getRect());
            }
            map_x ++;
        }
        map_y ++;
    }
}
