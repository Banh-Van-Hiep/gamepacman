#include "thongsochung.h"

const int chieu_rong = 800;
const int chieu_cao = 600;

int main(int argc, char* argv[])
{
    Game game;
    if(!game.khoitao("Pac-Man Clone", chieu_rong, chieu_cao))
    {
        return -1;
    }
    while(game.isRunning())
    {
        game.xulysukien();
        game.capnhat();
        game.velenmanhinh();
    }
    return 0;
}
