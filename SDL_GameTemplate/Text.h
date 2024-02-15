#pragma once
#include <SDL_ttf.h>
#include <string>

//Globally used font
TTF_Font* gFont = NULL;

class Text {

public:
    //Initializes variables
    Text();

    //Deallocates memory
    ~Text();

    //Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};