#ifndef SUCMANH_H
#define SUCMANH_H

#include <SDL.h>

class SucManh {
public:
    SucManh();

    void capNhat(Uint32 thoigianHienTai);
    void ve(SDL_Renderer* renderer, SDL_Texture* texture);
    void datLai();

    bool dangHienThi() const;
    bool daAn() const;
    void xuLyAn(SDL_Rect pacman, Uint32 thoigianHienTai);
    void sauKhiAn(Uint32 thoigianHienTai);

private:
    SDL_Rect hinhdang;
    bool hienthi;
    bool daan;
    Uint32 lanXuatHienGanNhat;
    Uint32 thoigianXuatHien;
    Uint32 thoigianDuocAn;

    const int thoiGianChoLanTiepTheo = 20000;
    const int thoiGianTonTai = 8000;
    const int thoiGianTangToc = 5000;
};

#endif
