/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(float x, float y);
    ~Player();
    
    // Input handling
    void handleInput(const uint8_t* keystate);
    
    // Physics & collision
    void update(float deltaTime);
    void setVelocity(float vx, float vy);
    
    // Getters
    SDL_Rect getCollisionBox() const;
    float getX() const { return x; }
    float getY() const { return y; }
    
    // Rendering
    void render(SDL_Renderer* renderer);
    
private:
    float x, y;                    // Position
    float vx, vy;                  // Velocity
    float speed;                   // Movement speed (pixels/sec)
    
    int width, height;             // Sprite dimensions
    SDL_Texture* texture;          // Sprite texture (nullptr for now, we'll use colored rect)
    
    // Animation state (for later)
    int frameIndex;
    float animationTimer;
};

#endif

