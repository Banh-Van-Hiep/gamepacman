#ifndef THONGSOCHUNG_H //kt neu chua duoc dinh nghia
#define THONGSOCHUNG_H // dinh nghia de tranh trung lap
#include<SDL2/SDL.h> // thu vien sdl2
#include<SDL2/SDL_image.h>

class Game
{
public:
    Game(); // khoi tao doi tuong
    ~Game(); //goi tu dong khi ct ket thuc, giai phong bo nho

    bool khoitao(const char* tieude, int rong, int cao);
    void xulysukien();
    void capnhat();
    void velenmanhinh();
    void dondep();

    bool isRunning(); //kt game co dang chay khong
    SDL_Texture* loadtexture(const char* path);//texture phai la con tro vi de truy xuat du lieu phuc tap

private: //cac bien trong nay chi co the thay doi ben trong class
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running; //trang thai game(chay hay k)
    SDL_Texture* pacmantexture;
    SDL_Rect pacman;
    int tocdo;

};
#endif //ket thuc bao ve file
