#include "thongsochung.h"
#include "foods.h"
#include "ghost.h"

#include<iostream>

const int chieu_rong = 800;
const int chieu_cao = 800;
extern bool choitiep;

int main(int argc, char* argv[])
{
    Game game;
    while (choitiep) {
        game.khoitao("Pac-Man Clone", chieu_rong, chieu_cao);
        game.reset();
        game.enter();
        while (game.isRunning())
        {
            game.xulysukien();
            game.capnhat();
            game.velenmanhinh();

            game.foods.draw(game.renderer, game.foodtexture);
            for (auto& ghost : game.ghosts)
            {
                ghost.capnhatvitri(game.pacman);
                ghost.ve(game.renderer, game.ghosttexture);
            }
            game.foods.checkeating(game.pacman);
        }
        game.dondep();
    }

    return 0;
}
