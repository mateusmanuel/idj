#include "TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) :
tileWidth(tileWidth), tileHeight(tileHeight)
{
    tileSet = new Sprite(associated, file);
    
    rows = tileSet->GetHeight() / tileHeight;
    columns = tileSet->GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    if((int)index < (rows*columns)-1 and (int)index >= 0)
    {
        int i = (index%columns)*tileWidth;
        int j = (index/columns)*tileHeight;

        tileSet->SetClip(i, j, tileWidth, tileHeight);
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