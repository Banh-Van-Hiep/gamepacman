#include "thongsochung.h"
#include "foods.h"
#include<iostream>
Mix_Chunk* amthanhan = nullptr;
int score = 0;

Foods::Foods()
{

}

void Foods::khoitaofoods()
{
    food.clear();
    for(int i = 0; i < map_row; i++)
    {
        for(int j = 0; j < map_column; j++)
        {
            if(Map[i][j]==0)
            {
                SDL_Rect Food = {j*tile_size + tile_size/2-3, i*tile_size+tile_size/2-3, 6, 6};
                food.push_back(Food);
            }
        }
    }
}

void Foods::draw(SDL_Renderer* renderer,SDL_Texture* foodtexture)
{
    if (!foodtexture) return;

    for (auto &f : food)
    {
        SDL_RenderCopy(renderer, foodtexture, NULL, &f);
    }
}

void Foods::checkeating(SDL_Rect pacman)
{
    for(auto f = food.begin(); f != food.end(); )
    {
        if(SDL_HasIntersection(&pacman,&(*f)))
        {
            food.erase(f);
            Mix_PlayChannel(0, amthanhan, 0);
            score++;
        }
        else f++;
    }
}
bool Foods::winORlost()
{
    if(food.size()<=100) return true;
    return false;
}

