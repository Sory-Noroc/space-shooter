#pragma once
#include <SDL_ttf.h>
#include <iostream>
#include "TextureManager.h"

class Text {
    SDL_Color white = { 255, 255, 255, 255 };

public:
    //Initializes variables
    Text(char *text, int screenHeight, int fontSize = 28) {
        this->text = new char[30];
        strcpy_s(this->text, strlen(text)+1, text);
        gFont = TTF_OpenFont("assets/Terminal.ttf", fontSize);
        this->screenHeight = screenHeight;
    }

    void update(int score) {
        SDL_FreeSurface(surface);
        numToString(score, text);
        surface = TTF_RenderText_Solid(gFont, text, white);
        if (surface == NULL) {
            printf("Can't render surface for text. Error code : %s\n", SDL_GetError());
        }
        else {
            SDL_DestroyTexture(texture);
            texture = TextureManager::LoadTexture(surface);
            destRect.x = 0;
            destRect.y = screenHeight - surface->h;
            destRect.w = surface->w;
            destRect.h = surface->h;
        }
    }

    void numToString(int num, char* str) {
        sprintf_s(str, 16, "Score: %d", num);
    }

    //Draws texture at given point
    void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        TextureManager::Draw(texture, nullptr, &destRect);
    }

    //Deallocates memory
    ~Text() {
        delete[] text;
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

private:
    //The actual hardware texture
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect destRect;
    TTF_Font* gFont = NULL;
    char* text;
    int screenHeight;
};