#include "TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file)
{
    tileSet = new Sprite(associated, file);
    
    rows = tileSet->GetHeight() / tileHeight;
    columns = tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    if(index == (rows*columns)-1)
    {
        tileSet->SetClip(x, y, tileWidth, tileHeight);
        tileSet->Render(x, y);
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}