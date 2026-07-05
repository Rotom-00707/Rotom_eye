#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include "Eye.h"
#include "Emotion.h"

enum BlinkState { OPEN, CLOSING, PAUSED, OPENING };

class Animation {
private:
    Eye* leftEye;
    Eye* rightEye;
    
    unsigned long nextBlinkTime;
    unsigned long blinkTimer;
    BlinkState blinkState;
    bool doDoubleBlink;
    
    unsigned long nextIdleTime;
    Emotion currentEmotion;

public:
    Animation(Eye* l, Eye* r);
    void update();
    void look(float x, float y);
    void blink();
    void wink();
    void setEmotion(Emotion e);

private:
    void handleBlink();
    void handleIdle();
};

#endif