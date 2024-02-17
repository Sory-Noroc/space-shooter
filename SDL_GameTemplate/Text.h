#pragma once
#include <SDL_ttf.h>
#include <iostream>
#include "TextureManager.h"

class Text {
    //The actual hardware texture
    SDL_Texture* texture = nullptr;
    SDL_Rect destRect = {};
    TTF_Font* gFont = NULL;

public:
    SDL_Surface* surface = nullptr;
    char* text = nullptr;
    SDL_Color white = { 255, 255, 255, 255 };

    Text(const char* fontPath, int fontSize = 28) {
        gFont = TTF_OpenFont(fontPath, fontSize);
    }

    int createSurface() {
        SDL_FreeSurface(surface);
        surface = TTF_RenderText_Solid(gFont, text, white);
        if (surface == NULL) {
            printf("Can't render surface for text. Error code : %s\n", SDL_GetError());
            return -1;
        }
        return 1;
    }

    void update(int x, int y) {
        if (createSurface() != -1) {
            destRect.x = x;
            destRect.y = y;
            createTexture();
        }
    }

    void createTexture() {
        SDL_DestroyTexture(texture);
        texture = TextureManager::LoadTexture(surface);
        destRect.w = surface->w;
        destRect.h = surface->h;
    }

    void update(int x, int y, char* newText) {
        setText(newText);
        update(x, y);
    }

    void update() {
        if (createSurface() == -1) {
            printf("Couldn't create surface. Error code: %s\n", SDL_GetError());
        }
        else {
            createTexture();
        }
    }

    void setText(char* newText) {
        strcpy_s(this->text, strlen(newText) + 1, newText);
    }

    void draw(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        TextureManager::Draw(texture, nullptr, &destRect);
    }

    ~Text() {
        if (text != nullptr) {
            delete[] text;
        }
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
};