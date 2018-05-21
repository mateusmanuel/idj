#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music> > Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk> > Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font> > Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
    auto search = imageTable.find(file);
    if(search != imageTable.end())
    {
        return search->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr)
    {
        printf("[ERROR] IMG_LoadTexture: %s\n", SDL_GetError());
        return std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    }

    imageTable.insert({file, std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* texture) { SDL_DestroyTexture(texture); })});
    return imageTable[file];
}

void Resources::ClearImages()
{
    for(auto image: imageTable)
    {
        if(image.second.unique())
        {
            imageTable.erase(image.first);
        }
    }

    imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file)
{
    auto search = musicTable.find(file);
    if(search != musicTable.end())
    {
        return search->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if(music == nullptr)
    {
        printf("[ERROR] Mix_LoadMUS: %s\n", SDL_GetError());
        return std::shared_ptr<Mix_Music>(music, [](Mix_Music* music) { Mix_FreeMusic(music); });
    }

    musicTable.insert({file, std::shared_ptr<Mix_Music>(music, [](Mix_Music* music) { Mix_FreeMusic(music); }) });
    return musicTable[file];
}

void Resources::ClearMusics()
{
    for(auto music: musicTable)
    {
        if(music.second.unique())
        {
            musicTable.erase(music.first);
        }
    }

    musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file)
{
    auto search = soundTable.find(file);
    if(search != soundTable.end())
    {
        return search->second;
    }

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if(sound == nullptr)
    {
        printf("[ERROR] Mix_LoadWAV: %s\n", SDL_GetError());
        return std::shared_ptr<Mix_Chunk>(sound, [](Mix_Chunk* sound) {Mix_FreeChunk(sound);});
    }

    soundTable.insert({file, std::shared_ptr<Mix_Chunk>(sound, [](Mix_Chunk* sound) {Mix_FreeChunk(sound);}) });
    return soundTable[file];
}

void Resources::ClearSounds()
{
    for(auto sound: soundTable)
    {
        if(sound.second.unique())
        {
            soundTable.erase(sound.first);
        }
    }

    soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize)
{
    std::string key = std::to_string(ptsize) + file;

    auto search = fontTable.find(key);
    if(search != fontTable.end())
    {
        return search->second;
    }

    TTF_Font* texture = TTF_OpenFont(file.c_str(), ptsize);
    if(texture == nullptr)
    {
        printf("[ERROR] IMG_LoadTexture: %s\n", SDL_GetError());
        return std::shared_ptr<TTF_Font>(texture, [](TTF_Font* font) { TTF_CloseFont(font); });
    }

    fontTable.insert({key, std::shared_ptr<TTF_Font>(texture, [](TTF_Font* font) { TTF_CloseFont(font); })});
    return fontTable[key];
}

void Resources::ClearFonts()
{
    for(auto font: fontTable)
    {
        if(font.second.unique())
        {
            fontTable.erase(font.first);
        }
    }

    fontTable.clear();
}
