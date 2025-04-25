#ifndef GHOST_H
#define GHOST_H

#include<SDL.h>
extern int waitingtime2;

class Ghost
{
public:
    Ghost();
    SDL_Rect rectghost;
    SDL_Rect numframe[4];
    int framehientai;
    Uint32 tghientai = 0;

    void vt(int X, int Y);
    void khoitaoghost(int id);
    void capnhatvitri(SDL_Rect pacman);
    bool kiemtravacham(int x, int y);
    void ve(SDL_Renderer* renderer, SDL_Texture* ghosttexture);
    int winORlost(SDL_Rect &pacman,int &mang, int &slc,Uint32 &lastCollisionTime, int &wf2);
    void changewaitingtime(int &waitingtime1, const Foods &food);
private:
    Uint32 lastUpdateTime;
};
#endif
