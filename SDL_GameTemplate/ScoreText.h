#pragma once
#include "Text.h"

class ScoreText: public Text {

public:
    //Initializes variables
    ScoreText(char *text, int screenHeight, int fontSize = 28): Text("assets/Terminal.ttf", fontSize) {
        this->text = new char[30];
        setText(text);
        this->screenHeight = screenHeight;
        if (createSurface() != -1) {
            Text::update(0, screenHeight - surface->h);
        }
    }

    void update(int score) {
        numToString(score, text);
        Text::update();
    }

    void numToString(int num, char* str) {
        sprintf_s(str, 16, "Score: %d", num);
    }

    //Draws texture at given point
    void render() {
        Text::draw();
    }

private:
    int screenHeight;
};