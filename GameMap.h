#ifndef _GameMap_H
#define _GameMap_H

#include "Graphics.h"
#include "BaseObject.h"
#include "defs.h"
class TileMap : public BaseObject
{
private:

public:
    TileMap(){;}
    ~TileMap(){;}
};

class GameMap
{
private:
    MAP game_map;
    TileMap tile_map[MAX_TILE];
    string filename;
public:
    GameMap()
    {
        filename = "map.txt";
        game_map.start_x = 0;
        game_map.start_y = 0;
    }
    ~GameMap(){;}
    void loadMap();
    void loadMapTiles(Graphics &graphics);
    void renderMap(Graphics &graphics);
    void setMap(const MAP& mapdata)
    {
        game_map = mapdata;
    }
    MAP get_map_data()
    {
        return game_map;
    }
};
#endif // _GameMap_H
