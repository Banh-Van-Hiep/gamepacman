#include "loadimage.h"
#include <SDL_image.h>
#include <SDL.h>
#include<iostream>

SDL_Texture * loadtexture(SDL_Renderer* renderer,const char* path)
{

    SDL_Surface* surface = IMG_Load(path);
    if(!surface)
    {
        std::cout<<"loi anh: "<<IMG_GetError()<<std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}
