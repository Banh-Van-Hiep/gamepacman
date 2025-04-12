#include "thongsochung.h"
#include<iostream>
#include "ghost.h"
#include "foods.h"
int waitingtime2 = 18;
Mix_Chunk* amthanhdie = nullptr;

Ghost::Ghost()
{
}

void Ghost::khoitaoghost(int id)
{
    int loaighost = id%4;
    if(id == 0)
    {
        rectghost.x = 60;
        rectghost.y = 60;
        std::cout<<rectghost.x<<' '<<rectghost.y<<std::endl;
    }
    if(id == 1)
    {
        rectghost.x = 60;
        rectghost.y = 740;
        std::cout<<rectghost.x<<' '<<rectghost.y<<std::endl;
    }
    if(id == 2)
    {
        rectghost.x = 740;
        rectghost.y = 60;
        std::cout<<rectghost.x<<' '<<rectghost.y<<std::endl;
    }
    if(id == 3)
    {
        rectghost.x = 740;
        rectghost.y = 740;
        std::cout<<rectghost.x<<' '<<rectghost.y<<std::endl;
    }
    if(id == 4)
    {
        rectghost.x = 300;
        rectghost.y = 300;
        std::cout<<rectghost.x<<' '<<rectghost.y<<std::endl;
    }
    rectghost.w = 20;
    rectghost.h = 20;
    for (int i = 0; i < 5; i++)
    {
        numframe[i] = { i * 17, loaighost * 17, 17, 17 };
    }
}

bool Ghost::kiemtravacham(int x, int y)
{
    int row1 = y / tile_size;
    int col1 = x / tile_size;
    int row2 = (y + rectghost.h - 1) / tile_size;
    int col2 = (x + rectghost.w - 1) / tile_size;
    for(int i = row1; i <= row2; i++)
    {
        for(int j = col1; j <= col2; j++)
        {
            if (i < 0 || i >= map_row || j < 0 || j >= map_column) {
            continue;
            }
            if(Map[i][j] == 1) return false;
        }
    }
    return true;
}

void Ghost::ve(SDL_Renderer* renderer, SDL_Texture* ghosttexture)
{
     Uint32 time = SDL_GetTicks();
     if (time - tghientai > 150)
    {
        framehientai = (framehientai + 1) % 4;
        tghientai = time;
    }
    SDL_RenderCopy(renderer, ghosttexture, &numframe[framehientai], &rectghost);
}

int Ghost::winORlost(SDL_Rect pacman, int &mang)
{
        if(SDL_HasIntersection(&rectghost,&pacman))
        {
            Mix_PlayChannel(2, amthanhdie, 0);
            mang--;
        }
        return mang;
}

void Ghost::capnhatvitri(SDL_Rect pacman)
{
    Uint32 now = SDL_GetTicks();
    if (now - lastUpdateTime < waitingtime2)
    {
        return;
    }
    lastUpdateTime = now;

    int dx = pacman.x - rectghost.x;
    int dy = pacman.y - rectghost.y;
    int huong;
    int newx = rectghost.x;
    int newy = rectghost.y;
    if(abs(dx) >= abs(dy))
    {
        if(dx>0) newx+=2;
        else newx-=2;
    }
    else
    {
        if(dy>0) newy+=2;
        else newy-=2;
    }
    if (kiemtravacham(newx, newy))
    {
        rectghost.x = newx;
        rectghost.y = newy;
    }
}
void Ghost::vt(int X, int Y)
{
    rectghost.x = X;
    rectghost.y = Y;
}
void Ghost::changewaitingtime(int &waitingtime1, const Foods &food)
{
    if (food.food.size() <= 20)
    {
        waitingtime2 = 15;
        waitingtime1 = 10;
    }
}
