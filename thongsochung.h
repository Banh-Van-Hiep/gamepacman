#ifndef THONGSOCHUNG_H //kt neu chua duoc dinh nghia
#define THONGSOCHUNG_H // dinh nghia de tranh trung lap

#include<vector>
#include<algorithm>
#include<cmath>
#include <string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <SDL_mixer.h>
#include"foods.h"
#include"ghost.h"
#include "sucmanh.h"

const int map_row = 20;
const int map_column = 20;
const int tile_size = 40;
const int numghost = 5;
extern  int mang;
const int Rbom = 50;

extern Mix_Chunk* amthanhan;
extern Mix_Chunk* amthanhansucmanh;
extern Mix_Chunk* amthanhdie;
extern int solanchet;
extern int tgconlai;
extern int pacmanFrameIndex;
extern int animationFrame;
extern SucManh sucmanhTangToc;
extern SucManh sucmanhTangMang;
extern SDL_Texture* textureTangToc;
extern SDL_Texture* textureTangMang;

const int Map[map_row][map_column]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,1,0,0,1,0,1,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,0,0,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1},
    {1,0,1,1,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,1,1,0,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,0,1,1,1,0,1,0,1,0,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

class Game
{
public:
    Game(); // khoi tao doi tuong
    ~Game(); //goi tu dong khi ct ket thuc, giai phong bo nho
    std::vector<Ghost> ghosts;
    Foods foods;
    SDL_Texture* foodtexture;

    SDL_Texture* ghosttexture;


    bool khoitao(const char* tieude, int rong, int cao);
    void xulysukien();
    void capnhat();
    void diemvamangvahoichieu(int score, int life,int cooldown);
    void enter();
    void velenmanhinh();
    bool kiemtravacham(int x, int y);
    void dondep();
    bool isRunning();
    bool ktkhoangcach(Ghost &ghost);
    void kichhoatbom();
    void hoichieu();
    void reset();

    Uint32 timebom;
    Uint32 moctg;
    Uint32 batdauno;

    SDL_Texture* loadtexture(const char* path);

    SDL_Rect pacman;//toa do pac man
    SDL_Renderer* renderer;
    int waitingtime1;

private: //cac bien trong nay chi co the thay doi ben trong class
    SDL_Window* window;
    SDL_Rect pacmanFrames[5];
    int pacmanFrameIndex;
    int animationFrame;

    Uint32 lastMoveTime = 0;
    enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
    Direction huongMoi;
    Direction huongHienTai;
    bool boolbom = true;
    bool checkno = false;
    bool running;

    TTF_Font *fontScore;
    TTF_Font *fontLife;
    TTF_Font *fontCooldown;

    Mix_Chunk* amThanhNo;
    Mix_Music* amthanhgame;
    Mix_Music* amthanhwin;
    Mix_Music* amthanhlost;
    Mix_Music* amthanhcho;

    SDL_Rect scorerect;
    SDL_Texture* scoretexture;

    SDL_Rect liferect;
    SDL_Texture* lifetexture;

    SDL_Rect cooldownRect;
    SDL_Texture* cooldowntexture;

    SDL_Rect bomrect;
    SDL_Texture* bomtexture;

    SDL_Texture* pacmantexture;

    SDL_Texture* wintexture;
    SDL_Rect winrect;

    SDL_Texture* losetexture;
    SDL_Rect loserect;

    SDL_Rect continuerect;
    SDL_Rect menurect;

    SDL_Rect enterrect;
    SDL_Texture* entertexture;

    SDL_Texture* tuongtexture;
    SDL_Texture* Ltexture;
    SDL_Texture* Stexture;
    SDL_Texture* Ttexture;

    int tocdo;

};

#endif //ket thuc bao ve file

