#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"

class TileMap : public Component
{
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);

        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int camexaY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void Update(float dt);
        bool Is(string type);
};

#endif