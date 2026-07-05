#ifndef EYE_H
#define EYE_H

#include <Arduino.h>
#include "Config.h"
#include "Emotion.h"

class Eye {
public:
    int id; // 0 for left, 1 for right
    float x, y; // Base anchor coordinates

    // Easing variables: Current state & Target state
    float curX, tarX;
    float curY, tarY;
    float curUpperLid, tarUpperLid;
    float curLowerLid, tarLowerLid;
    float curSlant, tarSlant;
    float curIrisScale, tarIrisScale;
    float curSquish, tarSquish;

    bool isWinking;

    Eye(int id, float x, float y);
    void update();
    void setEmotion(EmotionState state);
};

#endif