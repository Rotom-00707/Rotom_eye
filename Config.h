#ifndef CONFIG_H
#define CONFIG_H

// Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define PIN_SDA 21
#define PIN_SCL 22

// Eye Geometry (Customizable)
#define EYE_WIDTH 36
#define EYE_HEIGHT 48
#define EYE_SPACING 52
#define IRIS_SIZE 14
#define PUPIL_SIZE 6

// Animation Tuning
#define BLINK_SPEED 0.35f
#define MOVEMENT_SPEED 0.15f
#define SQUISH_FACTOR 0.8f // Vertical scaling during blink

// Timing
#define MIN_BLINK_INTERVAL 1500
#define MAX_BLINK_INTERVAL 6000
#define MIN_IDLE_INTERVAL 2000
#define MAX_IDLE_INTERVAL 5000

#endif