#ifndef FOODS_H
#define FOODS_H

#include <SDL.h>
#include<vector>

class Foods
{
public:
    Foods();
    int score = 0;
    void khoitaofoods();
    void draw(SDL_Renderer* renderer,SDL_Texture* foodtexture);
    bool winORlost();
    void checkeating(SDL_Rect pacman);
    std::vector<SDL_Rect> food;
private:
};

#endif
