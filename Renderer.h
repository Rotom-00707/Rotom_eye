#ifndef RENDERER_H
#define RENDERER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Eye.h"

class Renderer {
private:
    Adafruit_SSD1306* display;
public:
    Renderer(Adafruit_SSD1306* disp);
    void draw(Eye& leftEye, Eye& rightEye);
private:
    void drawEye(Eye& eye);
};

#endif