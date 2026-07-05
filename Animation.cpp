#include "Animation.h"

Animation::Animation(Eye* l, Eye* r) : leftEye(l), rightEye(r) {
    blinkState = OPEN;
    doDoubleBlink = false;
    currentEmotion = NEUTRAL;
    nextBlinkTime = millis() + 2000;
    nextIdleTime = millis() + 2000;
}

void Animation::update() {
    handleBlink();
    handleIdle();
}

void Animation::look(float x, float y) {
    leftEye->tarX = x;
    leftEye->tarY = y;
    rightEye->tarX = x;
    rightEye->tarY = y;
}

void Animation::blink() {
    nextBlinkTime = millis(); // Force blink immediately
}

void Animation::wink() {
    leftEye->isWinking = true;
    nextBlinkTime = millis();
}

void Animation::setEmotion(Emotion e) {
    currentEmotion = e;
    EmotionState state = EmotionManager::get(e);
    if (blinkState == OPEN) {
        leftEye->setEmotion(state);
        rightEye->setEmotion(state);
    }
}

void Animation::handleBlink() {
    switch (blinkState) {
        case OPEN:
            if (millis() > nextBlinkTime) {
                blinkState = CLOSING;
                leftEye->tarUpperLid = 1.0f;
                leftEye->tarLowerLid = 1.0f;
                leftEye->tarSquish = SQUISH_FACTOR; // Squish effect
                if (!leftEye->isWinking) {
                    rightEye->tarUpperLid = 1.0f;
                    rightEye->tarLowerLid = 1.0f;
                    rightEye->tarSquish = SQUISH_FACTOR;
                }
            }
            break;
            
        case CLOSING:
            if (leftEye->curUpperLid > 0.95f) {
                blinkState = PAUSED;
                blinkTimer = millis() + 40; // Human micro-pause
            }
            break;
            
        case PAUSED:
            if (millis() > blinkTimer) {
                blinkState = OPENING;
                EmotionState state = EmotionManager::get(currentEmotion);
                leftEye->setEmotion(state);
                leftEye->tarSquish = 1.0f;
                rightEye->setEmotion(state);
                rightEye->tarSquish = 1.0f;
            }
            break;
            
        case OPENING:
            if (leftEye->curUpperLid < EmotionManager::get(currentEmotion).upperLid + 0.05f) {
                blinkState = OPEN;
                leftEye->isWinking = false;
                
                // Double blink logic
                if (doDoubleBlink) {
                    doDoubleBlink = false;
                    nextBlinkTime = millis() + 50; 
                } else {
                    nextBlinkTime = millis() + random(MIN_BLINK_INTERVAL, MAX_BLINK_INTERVAL);
                    if (random(0, 100) < 15) doDoubleBlink = true; // 15% chance
                }
            }
            break;
    }
}

void Animation::handleIdle() {
    if (millis() > nextIdleTime) {
        int r = random(0, 100);
        if (r < 10) look(0, -12);       // Look up
        else if (r < 20) look(0, 12);   // Look down
        else if (r < 35) look(-15, 0);  // Look left
        else if (r < 50) look(15, 0);   // Look right
        else if (r < 80) look(0, 0);    // Look center
        else look(random(-8, 8), random(-8, 8)); // Micro-saccade/curious
        
        nextIdleTime = millis() + random(MIN_IDLE_INTERVAL, MAX_IDLE_INTERVAL);
    }
}