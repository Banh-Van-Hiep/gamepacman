#include "thongsochung.h"

#include<iostream>
bool choitiep = true;
int tgconlai = 0;
int solanchet = 0;
int pacmanFrameIndex = 0;
int animationFrame = 0;
int mang = 3;

Game::Game()
{
    window = nullptr;
    renderer = nullptr;

    pacmantexture = nullptr;
    tuongtexture = nullptr;
    foodtexture = nullptr;
    ghosttexture = nullptr;

    entertexture = nullptr;
    scoretexture = nullptr;
    lifetexture = nullptr;
    bomtexture = nullptr;
    cooldowntexture = nullptr;
    wintexture = nullptr;
    losetexture = nullptr;
    Ltexture = nullptr;
    Stexture = nullptr;
    Ttexture = nullptr;

    amThanhNo = nullptr;
    amthanhgame = nullptr;
    amthanhwin = nullptr;
    amthanhlost = nullptr;
    amthanhcho = nullptr;

    running = false;
    tocdo = 2;
    timebom = 10000;
    waitingtime1 = 15;
}
Game::~Game()
{
    dondep();
}

//khoi tao cua so but ve
bool Game::khoitao(const char* tieude, int rong, int cao)
{
    if(TTF_Init()==-1)
    {
        std::cout<<"loi khoi tao TTF: "<<TTF_GetError()<<std::endl;
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG))
    {
        std::cout<<"Loi khoi tao std_image: "<<IMG_GetError()<<std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer không thể khởi động! Lỗi: " << Mix_GetError() << std::endl;
        return false;
    }
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cout<<"loi khoi tao SDL: "<<SDL_GetError()<<std::endl;
        return false;
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

    foods.khoitaofoods();

    // khoi tao nhieu ghost

    //khoi tao pacman
    pacmantexture = loadtexture("pacman.png");
    if(!pacmantexture)
    {
        std::cout<<"loi tai pacman.png: "<<IMG_GetError()<<std::endl;
        return false;
    }
    //tuong
    tuongtexture = loadtexture("tuong.png");
    if(!tuongtexture)
    {
        std::cout<<"loi tai pacman.png: "<<IMG_GetError()<<std::endl;
        return false;
    }
    //khoi tao thuc an
    foodtexture = loadtexture("food.png");
    if(!foodtexture)
    {
        std::cout<<"loi tai food.png: "<<IMG_GetError()<<std::endl;
        return false;
    }

    ghosttexture = loadtexture("ghosts.png");
    if(!ghosttexture)
    {
        std::cout<<"loi tai ghost.png"<<IMG_GetError()<<std::endl;
        return false;
    }

    bomtexture = loadtexture("bom.png");
    if(!bomtexture)
    {
        std::cout<<"loi tai anh bom.png"<<IMG_GetError()<<std::endl;
        return false;
    }
    wintexture = loadtexture("win.png");
    if(!wintexture)
    {
        std::cout<<"loi tai anh win.png"<<IMG_GetError()<<std::endl;
        return false;
    }
    losetexture = loadtexture("lose.png");
    if(!losetexture)
    {
        std::cout<<"loi tai anh lose.png"<<IMG_GetError()<<std::endl;
        return false;
    }
    entertexture = loadtexture("enter.png");
    if(!entertexture)
    {
        std::cout<<"loi tai anh lose.png"<<IMG_GetError()<<std::endl;
        return false;
    }

    Ltexture = loadtexture("L.png");
    Stexture = loadtexture("S.png");
    Ttexture = loadtexture("T.png");

    amThanhNo = Mix_LoadWAV("bom.mp3");
    amthanhan = Mix_LoadWAV("eat.mp3");
    amthanhgame = Mix_LoadMUS("game.mp3");
    amthanhdie = Mix_LoadWAV("die.mp3");
    amthanhwin = Mix_LoadMUS("win.mp3");
    amthanhlost = Mix_LoadMUS("lost.mp3");
    amthanhcho = Mix_LoadMUS("cho.mp3");
    //
    fontScore = TTF_OpenFont("arial.ttf", 24);
    fontLife = TTF_OpenFont("arial.ttf",24);
    fontCooldown = TTF_OpenFont("arial.ttf", 24);
    if (!fontScore||!fontLife||!fontCooldown)
    {
        std::cout << "Không thể tải font: " << TTF_GetError() << std::endl;
        return false;
    }

    enterrect = {0, 0, rong, cao};
    winrect = {0, 0, rong, cao};
    loserect = {0, 0, rong, cao};
    //pacman
    for (int i = 0; i < 5; i++) {
        pacmanFrames[i].x = i * 18;
        pacmanFrames[i].y = 0;
        pacmanFrames[i].w = 18;
        pacmanFrames[i].h = 24;
    }

    //bom
    boolbom = true;
    moctg = 0;

    running = true;
    return true;
}

bool Game::kiemtravacham(int x, int y)
{
    int Row1 = y / tile_size;
    int Col1 = x / tile_size;
    int Row2 = (y + pacman.h -1) / tile_size;
    int Col2 = (x + pacman.w -1) / tile_size;

    for (int i = Row1; i <= Row2; i++)
    {
        for (int j = Col1; j <= Col2; j++)
        {
            if (Map[i][j] == 1)
            {
                return true;
            }
        }
    }
    return false;
}

//xu ly su kien
void Game::xulysukien()
{
    SDL_Event sukien;
    while(SDL_PollEvent(&sukien))
    {
        if(sukien.type == SDL_QUIT)
        {
            choitiep = false;
            running = false;
        }
        else if(sukien.type == SDL_KEYDOWN)
        {
            switch (sukien.key.keysym.sym)
            {
                case SDLK_UP:
                    huongMoi = UP;
                    break;
                case SDLK_DOWN:
                    huongMoi = DOWN;
                    break;
                case SDLK_LEFT:
                    huongMoi = LEFT;
                    break;
                case SDLK_RIGHT:
                    huongMoi = RIGHT;
                    break;
                case SDLK_h:
                    kichhoatbom();
                    break;
            }
        }
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime < waitingtime1) return;

    lastMoveTime = currentTime;
    int xNew = pacman.x;
    int yNew = pacman.y;

    switch (huongMoi)
    {
        case UP:
            yNew -= tocdo;
            break;
        case DOWN:
            yNew += tocdo;
            break;
        case LEFT:
            xNew -= tocdo;
            break;
        case RIGHT:
            xNew += tocdo;
            break;
    }

    if (!kiemtravacham(xNew, yNew))
    {
        pacman.x = xNew;
        pacman.y = yNew;
        huongHienTai = huongMoi;
        animationFrame = (animationFrame + 1) % 5;
    }
    else
    {
        huongMoi = huongHienTai;
    }
}
//cap nhat trang thai
void Game::capnhat()
{
    foods.checkeating(pacman);
    for (auto& g : ghosts)
    {
        g.changewaitingtime(waitingtime1, foods);
    }
    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(amthanhgame, -1);
    }
    hoichieu();
    if(checkno)
    {
        if((SDL_GetTicks() - batdauno) > 400)
        {
            checkno = false;
        }
    }

    for(Ghost &g : ghosts) g.capnhatvitri(pacman);
    if(foods.winORlost())
    {
        Mix_HaltMusic();
        SDL_Event e;
        velenmanhinh();
        bool wait = true;
        while(wait)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT||e.type == SDL_KEYDOWN) wait = false;
            }
        }
        choitiep = false;
        running  = false;
    }
}
//diem
void Game::diemvamangvahoichieu(int score, int lifes, int cooldown)
{
    std::string diem = std::to_string(score);
    std::string life = std::to_string(lifes);
    std::string cd = std::to_string(cooldown) + " s";

    SDL_Surface* textsurface1 = TTF_RenderText_Solid(fontScore, diem.c_str(), {255, 255, 255, 255});
    SDL_Surface* textsurface2 = TTF_RenderText_Solid(fontLife, life.c_str(), {255, 255, 255, 255});
    SDL_Surface* textsurface3 = TTF_RenderText_Solid(fontCooldown, cd.c_str(), {255, 255, 255, 255});

    if (!textsurface1 || !textsurface2 || !textsurface3) return;

    scoretexture = SDL_CreateTextureFromSurface(renderer, textsurface1);
    lifetexture = SDL_CreateTextureFromSurface(renderer, textsurface2);
    cooldowntexture = SDL_CreateTextureFromSurface(renderer, textsurface3);

    scorerect = {50, 10, textsurface1->w, textsurface1->h};
    liferect = {170, 10, textsurface2->w, textsurface2->h};
    cooldownRect = {290, 10, textsurface3->w, textsurface3->h};

    SDL_FreeSurface(textsurface1);
    SDL_FreeSurface(textsurface2);
    SDL_FreeSurface(textsurface3);
}

void Game::enter()
{
    SDL_Event e;
    bool check = true;
    Mix_PlayMusic(amthanhcho,1);
    while(check)
    {
        SDL_RenderCopy(renderer, entertexture, NULL, &enterrect);
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                choitiep = false;
                running = false;
                check = false;
            }
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_RETURN)
                {
                    check = false;
                }
            }
        }
    }
    Mix_HaltMusic();
}
//load anh
SDL_Texture * Game::loadtexture(const char* path)
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
//ve len man hinh
void Game::velenmanhinh()
{
    SDL_RenderClear(renderer);
    for(int i = 0; i < map_row; i++)
    {
        for(int j = 0; j < map_column; j++)
        {
            SDL_Rect rect = {j*tile_size, i*tile_size, tile_size, tile_size};
            if(i == 0&& j == 0)
            {
                SDL_RenderCopy(renderer, Stexture, NULL, &rect);
            }
            else if(i == 0 && j == 3)
            {
                SDL_RenderCopy(renderer, Ltexture, NULL, &rect);
            }
            else if(i == 0 && j == 6)
            {
                SDL_RenderCopy(renderer, Ttexture, NULL, &rect);
            }
            else if(Map[i][j]==1)
            {
                SDL_RenderCopy(renderer, tuongtexture, NULL, &rect);
            }
        }
    }
    if (pacmantexture)
    {
        SDL_Rect frame = pacmanFrames[(pacmanFrameIndex * 5 + animationFrame) % 5];
        SDL_RenderCopy(renderer, pacmantexture, &frame, &pacman);
    }
    if(foodtexture)
    {
        foods.draw(renderer,foodtexture);
    }
    if(fontScore)
    {
        diemvamangvahoichieu(foods.score, mang-solanchet,tgconlai);
        SDL_RenderCopy(renderer, scoretexture, NULL, &scorerect);
        SDL_RenderCopy(renderer, lifetexture, NULL, &liferect);
        SDL_RenderCopy(renderer, cooldowntexture, NULL, &cooldownRect);
    }
    if(ghosttexture)
    {
        for(Ghost &g : ghosts)
        g.ve(renderer,ghosttexture);
    }
    if(checkno)
    {
        SDL_SetTextureBlendMode(bomtexture, SDL_BLENDMODE_BLEND);
        int frame = (SDL_GetTicks() - batdauno) / 100;
        SDL_Rect framerect = {frame*272, 0, 272, 236};
        SDL_RenderCopy(renderer,bomtexture ,&framerect, &bomrect);
    }
    continuerect = {130, 450, 250, 100};
    menurect = {430, 450, 250, 100};

    static int i = 1;
    bool reseti = false;
    if (foods.winORlost())
    {
        SDL_Event e;
        Mix_PlayMusic(amthanhwin, 0);
        SDL_RenderCopy(renderer, wintexture , NULL, NULL);
        SDL_RenderPresent(renderer);

        bool waitingForEvent = true;
        while (waitingForEvent)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    choitiep = false;
                    running = false;
                    waitingForEvent = false;
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    if (mouseX >= continuerect.x && mouseX <= continuerect.x + continuerect.w &&
                        mouseY >= continuerect.y && mouseY <= continuerect.y + continuerect.h)
                    {
                        choitiep = false;
                        running = false;
                        waitingForEvent = false;
                    }

                    if (mouseX >= menurect.x && mouseX <= menurect.x + menurect.w &&
                        mouseY >= menurect.y && mouseY <= menurect.y + menurect.h)
                    {
                        choitiep = false;
                        running = false;
                        waitingForEvent = false;
                    }
                }
            }
        }
    }
    else
    {
        SDL_Event e;

        for (Ghost &ghost : ghosts)
        {
            mang = ghost.winORlost(pacman,mang);
            if (mang == 0)
            {
                Mix_PlayMusic(amthanhlost, 0);
                SDL_RenderCopy(renderer, losetexture , NULL, NULL);
                SDL_RenderPresent(renderer);

                bool waitingForEvent = true;
                while (waitingForEvent)
                {
                    while (SDL_PollEvent(&e))
                    {
                        if (e.type == SDL_QUIT)
                        {
                            choitiep = false;
                            running = false;
                            waitingForEvent = false;
                        }
                        else if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);

                            if (mouseX >= continuerect.x && mouseX <= continuerect.x + continuerect.w &&
                                mouseY >= continuerect.y && mouseY <= continuerect.y + continuerect.h)
                            {
                                choitiep = false;
                                running = false;
                                waitingForEvent = false;
                            }

                            if (mouseX >= menurect.x && mouseX <= menurect.x + menurect.w &&
                                mouseY >= menurect.y && mouseY <= menurect.y + menurect.h)
                            {
                                choitiep = false;
                                running = false;
                                waitingForEvent = false;
                            }
                        }
                    }
                }
            }
            else if (i == mang)
            {
                pacman.x = 800 / 2 + 50;
                pacman.y = (800 - 100) / 2 + 50;
                i++;
            }

            SDL_RenderPresent(renderer);
        }
    }
    if (reseti)
    {
        i = 1;
        std::cout<<i;
        reseti = false;
    }
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
    if(foodtexture)
    {
        SDL_DestroyTexture(foodtexture);
        foodtexture = nullptr;
    }
    if(scoretexture)
    {
        SDL_DestroyTexture(scoretexture);
        scoretexture = nullptr;
    }
    if(entertexture)
    {
        SDL_DestroyTexture(entertexture);
        entertexture = nullptr;
    }
    if(cooldowntexture)
    {
        SDL_DestroyTexture(cooldowntexture);
        cooldowntexture = nullptr;
    }
    if(wintexture)
    {
        SDL_DestroyTexture(wintexture);
        wintexture = nullptr;
    }
    if(losetexture)
    {
        SDL_DestroyTexture(losetexture);
        losetexture = nullptr;
    }
    if(tuongtexture)
    {
        SDL_DestroyTexture(tuongtexture);
        tuongtexture = nullptr;
    }
    if(Ltexture)
    {
        SDL_DestroyTexture(Ltexture);
        Ltexture = nullptr;
    }
    if(Stexture)
    {
        SDL_DestroyTexture(Stexture);
        Stexture = nullptr;
    }
    if(Ttexture)
    {
        SDL_DestroyTexture(Ttexture);
        Ttexture = nullptr;
    }
    if (fontScore) TTF_CloseFont(fontScore);
    if (fontLife) TTF_CloseFont(fontLife);
    if (fontCooldown) TTF_CloseFont(fontCooldown);

    if (amThanhNo) Mix_FreeChunk(amThanhNo);
    if (amthanhan) Mix_FreeChunk(amthanhan);
    if (amthanhdie) Mix_FreeChunk(amthanhdie);
    if (amthanhgame) Mix_FreeMusic(amthanhgame);
    if (amthanhwin) Mix_FreeMusic(amthanhwin);
    if (amthanhlost) Mix_FreeMusic(amthanhlost);
    if (amthanhcho) Mix_FreeMusic(amthanhcho);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::ktkhoangcach(Ghost &ghost)
{
    int dx = (pacman.x + pacman.w / 2) - (ghost.rectghost.x + ghost.rectghost.w / 2);
    int dy = (pacman.y + pacman.h / 2) - (ghost.rectghost.y + ghost.rectghost.h / 2);

    return (abs(dx) <= Rbom && abs(dy) <= Rbom);
}

void Game::kichhoatbom()
{
    if (boolbom )
    {
        checkno = true;
        batdauno = SDL_GetTicks();
        Mix_PlayChannel(0, amThanhNo, 0);
        int tam_x = pacman.x + pacman.w / 2;
        int tam_y = pacman.y + pacman.h / 2;
        bomrect.x = tam_x - Rbom / 2;
        bomrect.y = tam_y - Rbom / 2;
        bomrect.w = Rbom;
        bomrect.h = Rbom;
        for(Ghost &ghost : ghosts)
        {
            if(ktkhoangcach(ghost)) ghost.vt(400,400);
        }
    }
    boolbom = false;
    moctg = SDL_GetTicks();
}
void Game::hoichieu()
{
    if (!boolbom)
    {
        int thoigian = (SDL_GetTicks() - moctg);
        tgconlai = (timebom - thoigian) / 1000;
        if (thoigian >= timebom)
        {
            boolbom = true;
            tgconlai = 0;
        }
    }
}

void Game::reset()
{
    pacman.x = (800)/2+50;
    pacman.y = (800-100)/2+50;
    pacman.w = 20;
    pacman.h = 20;
    solanchet = 0;
    mang = 3;
    tgconlai = timebom;
    pacmanFrameIndex = 0;
    animationFrame = 0;
    foods.score = 0;
}
