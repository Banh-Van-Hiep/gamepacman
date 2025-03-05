#include "thongsochung.h"
#include<iostream>

Game::Game() : window(nullptr), renderer(nullptr), running(false){}
Game::~Game() {dondep();}

//khoi tao cua so but ve
bool Game::khoitao(const char* tieude, int rong, int cao)
{
    if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
    {
        std::cout<<"Loi khoi tao std_image: "<<IMG_GetError()<<std::endl;
        return false;
    }
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cout<<"loi khoi tao SDL: "<<SDL_GetError()<<std::endl;
    }

    window = SDL_CreateWindow(tieude, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, rong, cao, SDL_WINDOW_SHOWN);
    if(!window)
    {
        std::cout<<"Khong the tao cua so: "<<SDL_GetError()<<std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        std::cout<<"khong the tao renderer: "<< SDL_GetError()<<std::endl;
        return false;
    }

    //khoi tao pacman
    pacmantexture = loadtexture("pacman.png");
    if(!pacmantexture)
    {
        std::cout<<"loi tai pacman.png: "<<IMG_GetError()<<std::endl;
        return false;
    }
    pacman.x = rong/2;
    pacman.y = cao/2;
    pacman.w = 50;
    pacman.h = 50;
    tocdo = 5;

    running = true;
    return true;
}

//ham tai anh
SDL_Texture* Game::loadtexture(const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if(!surface)
    {
        std::cout<<"Loi anh: "<<IMG_GetError()<<std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);//giai phong surface
    return texture;
}

//xu ly su kien
void Game::xulysukien()
{
    SDL_Event sukien;
    while(SDL_PollEvent(&sukien))
    {
        if(sukien.type == SDL_QUIT)
        {
            running = false;
        }
        else if(sukien.type==SDL_KEYDOWN)
        {
            switch (sukien.key.keysym.sym)
            {
                case SDLK_UP:
                    if(pacman.y-tocdo>=0) pacman.y -= tocdo;
                    break;
                case SDLK_DOWN:
                    if(pacman.y+tocdo+pacman.h<=600) pacman.y+= tocdo;
                    break;
                case SDLK_LEFT:
                    if(pacman.x-tocdo>=0) pacman.x-=tocdo;
                    break;
                case SDLK_RIGHT:
                    if(pacman.x+tocdo+pacman.w<=800) pacman.x+=tocdo;
                    break;
            }
        }

    }

}

//cap nhat trang thai
void Game::capnhat(){}

//ve len man hinh
void Game::velenmanhinh()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //ve pacman
    //SDL_SetRenderDrawColor(renderer,255,255,0,255);
    //SDL_RenderFillRect(renderer,&pacman);
    if(pacmantexture)
    {
        SDL_RenderCopy(renderer, pacmantexture, NULL, &pacman);
    } else
    {
        std::cout<<"anh khong ton tai"<<std::endl;
    }
    SDL_RenderPresent(renderer); // cap nhat ban ve len man hinh

}

// kt co dang chay khong
bool Game::isRunning()
{
    return running;
}

//dondep
void Game::dondep()
{
    if(pacmantexture)
    {
        SDL_DestroyTexture(pacmantexture);
        pacmantexture = nullptr;
    }
    if(renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    IMG_Quit(); // Dọn dẹp SDL_image
    SDL_Quit();
}






















