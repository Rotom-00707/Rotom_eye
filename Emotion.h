#ifndef EMOTION_H
#define EMOTION_H

enum Emotion {
    NEUTRAL,
    HAPPY,
    ANGRY,
    SLEEPY,
    SURPRISED
};

struct EmotionState {
    float upperLid;  // 0.0 (wide open) to 1.0 (fully closed)
    float lowerLid;  // 0.0 (wide open) to 1.0 (fully closed)
    float slant;     // Positive = Angry (inner down), Negative = Sad (outer down)
    float irisScale; // 1.0 is normal, < 1.0 is contracted
};

class EmotionManager {
public:
    static EmotionState get(Emotion e);
};

#endif