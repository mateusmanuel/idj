#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

class Resources
{
    public:
        SDL_Texture* GetImage(std::string file);
        void ClearImages();

        Mix_Music* GetMusic(std::string file);
        void ClearMusics();

        Mix_Chunk* GetSound(std::string file);
        void ClearSounds();

    private:
        std::unordered_map<std::string, SDL_Texture*> imageTable;
        std::unordered_map<std::string, Mix_Music*> musicTable;
        std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif