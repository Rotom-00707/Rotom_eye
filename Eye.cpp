#include "Eye.h"

Eye::Eye(int id, float x, float y) : id(id), x(x), y(y) {
    curX = tarX = 0;
    curY = tarY = 0;
    curUpperLid = tarUpperLid = 0.1f;
    curLowerLid = tarLowerLid = 0.1f;
    curSlant = tarSlant = 0;
    curIrisScale = tarIrisScale = 1.0f;
    curSquish = tarSquish = 1.0f;
    isWinking = false;
}

void Eye::update() {
    // Easing interpolation for all physical properties
    curX += (tarX - curX) * MOVEMENT_SPEED;
    curY += (tarY - curY) * MOVEMENT_SPEED;
    curUpperLid += (tarUpperLid - curUpperLid) * BLINK_SPEED;
    curLowerLid += (tarLowerLid - curLowerLid) * BLINK_SPEED;
    curSlant += (tarSlant - curSlant) * MOVEMENT_SPEED;
    curIrisScale += (tarIrisScale - curIrisScale) * MOVEMENT_SPEED;
    curSquish += (tarSquish - curSquish) * (BLINK_SPEED * 1.5f);
}

void Eye::setEmotion(EmotionState state) {
    tarUpperLid = state.upperLid;
    tarLowerLid = state.lowerLid;
    tarSlant = state.slant;
    tarIrisScale = state.irisScale;
}