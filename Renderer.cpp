#include "Renderer.h"

Renderer::Renderer(Adafruit_SSD1306* disp) : display(disp) {}

void Renderer::draw(Eye& leftEye, Eye& rightEye) {
    display->clearDisplay();
    drawEye(leftEye);
    drawEye(rightEye);
    display->display();
}

void Renderer::drawEye(Eye& eye) {
    float cx = eye.x + eye.curX;
    float cy = eye.y + eye.curY;
    float w = EYE_WIDTH;
    float h = EYE_HEIGHT * eye.curSquish;

    // 1. Draw Sclera (Eyeball)
    display->fillRoundRect(cx - w/2, cy - h/2, w, h, w/4, SSD1306_WHITE);

    // 2. Draw Iris & Pupil
    float irisRadius = (IRIS_SIZE * eye.curIrisScale) / 2.0f;
    float maxOffset = (w/2) - irisRadius;
    float ox = constrain(eye.curX, -maxOffset, maxOffset);
    float oy = constrain(eye.curY, -(h/2)+irisRadius, (h/2)-irisRadius);
    
    display->fillCircle(cx + ox, cy + oy, irisRadius, SSD1306_BLACK);

    // 3. Draw Multiple Procedural Reflections
    float reflRadius1 = irisRadius * 0.35f;
    float reflRadius2 = irisRadius * 0.15f;
    display->fillCircle(cx + ox - irisRadius*0.25f, cy + oy - irisRadius*0.25f, reflRadius1, SSD1306_WHITE);
    display->fillCircle(cx + ox + irisRadius*0.35f, cy + oy + irisRadius*0.2f, reflRadius2, SSD1306_WHITE);

    // 4. Mask Top Eyelid
    float topLidY = cy - h/2;
    float topLidH = h * eye.curUpperLid;
    display->fillRect(cx - w/2 - 2, topLidY - 2, w + 4, topLidH + 2, SSD1306_BLACK);

    // 5. Calculate Slants (Expressions) using dynamic masking triangles
    if (eye.curSlant > 0.0f) { // Angry
        float slantH = h * eye.curSlant;
        if (eye.id == 0) { // Left eye
            display->fillTriangle(cx - w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH + slantH, SSD1306_BLACK);
        } else {           // Right eye
            display->fillTriangle(cx - w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH, cx - w/2, topLidY + topLidH + slantH, SSD1306_BLACK);
        }
    } else if (eye.curSlant < 0.0f) { // Sad / Worried
        float slantH = h * -eye.curSlant;
        if (eye.id == 0) { 
            display->fillTriangle(cx - w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH, cx - w/2, topLidY + topLidH + slantH, SSD1306_BLACK);
        } else {
            display->fillTriangle(cx - w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH, cx + w/2, topLidY + topLidH + slantH, SSD1306_BLACK);
        }
    }

    // 6. Mask Bottom Eyelid
    float botLidH = h * eye.curLowerLid;
    float botLidY = cy + h/2 - botLidH;
    display->fillRect(cx - w/2 - 2, botLidY, w + 4, botLidH + 2, SSD1306_BLACK);
}