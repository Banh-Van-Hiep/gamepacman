#include "sucmanh.h"
#include <cstdlib>
#include "thongsochung.h"
#include<iostream>
Mix_Chunk* amthanhansucmanh = nullptr;
SucManh::SucManh()
{
    hienthi = false;
    daan = false;
    lanXuatHienGanNhat = 0;
    thoigianXuatHien = 0;
    thoigianDuocAn = 0;
    hinhdang = {0, 0, 40, 40};
}
void SucManh::capNhat(Uint32 thoigianHienTai)
{
    if (!hienthi && !daan && thoigianHienTai - lanXuatHienGanNhat >= thoiGianChoLanTiepTheo)
    {
        bool timduoc = false;
        int x, y;

        while (!timduoc)
        {
            int j = rand() % map_column;
            int i = rand() % map_row;

            if (Map[i][j] == 0)
            {
                x = j * tile_size + tile_size / 2 - 20;
                y = i * tile_size + tile_size / 2 - 20;
                timduoc = true;
            }
        }

        hinhdang.x = x;
        hinhdang.y = y;
        hinhdang.w = 40;
        hinhdang.h = 40;

        hienthi = true;
        thoigianXuatHien = thoigianHienTai;
        lanXuatHienGanNhat = thoigianHienTai;

    }

    if (hienthi && thoigianHienTai - thoigianXuatHien >= thoiGianTonTai)
    {
        hienthi = false;
    }

    if (daan && thoigianHienTai - thoigianDuocAn >= thoiGianTangToc)
    {
        daan = false;
    }
}
void SucManh::ve(SDL_Renderer* renderer, SDL_Texture* texture)
{
    if (hienthi && texture)
    {
        SDL_RenderCopy(renderer, texture, nullptr, &hinhdang);
    }
}

void SucManh::xuLyAn(SDL_Rect pacman, Uint32 thoigianHienTai)
{
    if (hienthi && SDL_HasIntersection(&pacman, &hinhdang))
    {
        hienthi = false;
        daan = true;
        Mix_PlayChannel(0, amthanhansucmanh, 0);
        thoigianDuocAn = thoigianHienTai;
    }
}

bool SucManh::dangHienThi() const { return hienthi; }
bool SucManh::daAn() const { return daan; }

void SucManh::datLai()
{
    hienthi = false;
    daan = false;
    lanXuatHienGanNhat = 0;
    thoigianXuatHien = 0;
    thoigianDuocAn = 0;
}
void SucManh::sauKhiAn(Uint32 thoigianHienTai)
{
    hienthi = false;
    daan = false;
    lanXuatHienGanNhat = thoigianHienTai;
}
