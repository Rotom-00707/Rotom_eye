#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Config.h"
#include "Emotion.h"
#include "Eye.h"
#include "Animation.h"
#include "Renderer.h"

// --- Global Engine Instances ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Eye leftEye(0, SCREEN_WIDTH/2 - EYE_SPACING/2, SCREEN_HEIGHT/2);
Eye rightEye(1, SCREEN_WIDTH/2 + EYE_SPACING/2, SCREEN_HEIGHT/2);

Animation anim(&leftEye, &rightEye);
Renderer renderer(&display);

// --- Public API Engine Wrapper ---
void look(float x, float y) { anim.look(x, y); }
void blink()                { anim.blink(); }
void setEmotion(Emotion e)  { anim.setEmotion(e); }
void update()               { anim.update(); leftEye.update(); rightEye.update(); }
void draw()                 { renderer.draw(leftEye, rightEye); }


// --- Demonstration Tracker ---
unsigned long lastDemoSwitch = 0;

void setup() {
    Serial.begin(115200);
    
    // Maximize I2C speed to target 60FPS
    Wire.begin(PIN_SDA, PIN_SCL);
    Wire.setClock(1000000); 

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    display.clearDisplay();
    display.display();
    
    // Wake up animation delay
    delay(500); 
    setEmotion(NEUTRAL);
}

void loop() {
    // Cycles through expressions dynamically every 6 seconds to prove features
    if (millis() - lastDemoSwitch > 6000) {
        lastDemoSwitch = millis();
        int randomEmotion = random(0, 5);
        setEmotion((Emotion)randomEmotion);
    }

    // Engine Core Execution (Non-Blocking)
    update();
    draw();
}