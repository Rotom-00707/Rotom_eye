#include "Emotion.h"

EmotionState EmotionManager::get(Emotion e) {
    switch(e) {
        case NEUTRAL:   
            return {0.10f, 0.05f,  0.0f, 1.0f};
        case HAPPY:     
            return {0.20f, 0.40f,  0.0f, 1.0f}; // Cheeks pushed up
        case ANGRY:     
            return {0.35f, 0.15f,  0.4f, 0.7f}; // Slanted brows, contracted iris
        case SLEEPY:    
            return {0.65f, 0.20f,  0.0f, 1.0f}; // Droopy lids
        case SURPRISED: 
            return {0.00f, 0.00f,  0.0f, 0.5f}; // Wide eyes, contracted iris
        default:        
            return {0.10f, 0.05f,  0.0f, 1.0f};
    }
}