#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture> > Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

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
        return std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); });
    }

    imageTable.insert({file, std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); })});
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

Mix_Music* Resources::GetMusic(std::string file)
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
        return music;
    }

    musicTable.insert({file, music});
    return music;
}

void Resources::ClearMusics()
{
    for(auto music: musicTable)
    {
        Mix_FreeMusic(music.second);
    }

    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file)
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
        return sound;
    }

    soundTable.insert({file, sound});
    return sound;
}

void Resources::ClearSounds()
{
    for(auto sound: soundTable)
    {
        Mix_FreeChunk(sound.second);
    }

    soundTable.clear();
}