# RotomEyes V2

A fully procedural, hardware-accelerated, non-blocking Arduino Eye Engine built for the ESP32 and SSD1306 OLED displays. Built with completely modular object-oriented classes.

## Features
- **Zero Bitmaps:** 100% procedural primitive math rendering.
- **Asynchronous Easing:** Non-blocking `millis()` math interpolation means zero jumps or jagged movements.
- **Hardware Optimized:** Targets 60 FPS utilizing ESP32's 1MHz I2C hardware clock line.
- **Biomimicry Engine:** Includes macro and micro-saccades, squash and stretch (squish factor) eye blinks, double blinking probabilities, winks, dynamic pupil contraction, and parameterized eyelid slants.
- **Expressive:** Standardized Emotion API (NEUTRAL, HAPPY, ANGRY, SLEEPY, SURPRISED).

## Hardware & Wiring
- **Microcontroller:** ESP32 (or compatible boards)
- **Display:** 128x64 I2C SSD1306 OLED
- **Wiring (Default):** - ESP32 3V3 -> VCC
  - ESP32 GND -> GND
  - ESP32 GPIO 21 -> SDA
  - ESP32 GPIO 22 -> SCL

## Libraries Needed
1. `Adafruit GFX Library`
2. `Adafruit SSD1306`

## How to Customize
Edit `Config.h` without touching source code! 
- Adjust `EYE_WIDTH`, `EYE_HEIGHT`, `IRIS_SIZE` for new shapes.
- Alter `EYE_SPACING` to fit alternative displays or enclosures.
- Tweak `BLINK_SPEED` or `MOVEMENT_SPEED` to change the "personality" of the easing curves.

## Future Expansion
The highly extensible `.cpp` structures allow easy implementation of:
1. Interpolated emotional morphs (e.g., smoothly transitioning between Happy and Angry).
2. Look-tracking via serial data (passing XYZ coordinates to the `look()` API).
3. Adapting `Renderer.cpp` to drive full-color SPI LCDs by swapping `Adafruit_SSD1306` with `Adafruit_ST7789`.