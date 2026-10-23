/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "player.h"
#include <iostream>

Player::Player(float x, float y)
    : x(x), y(y), vx(0), vy(0), speed(200.0f),
      width(32), height(32), texture(nullptr),
      frameIndex(0), animationTimer(0.0f) {
}

Player::~Player() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Player::handleInput(const uint8_t* keystate) {
    // Reset velocity each frame (we'll set it based on input)
    vx = 0;
    vy = 0;
    
    // Check for movement keys (WASD or arrow keys)
    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        vy = -speed;
    }
    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        vy = speed;
    }
    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        vx = -speed;
    }
    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        vx = speed;
    }
}

void Player::update(float deltaTime) {
    // Update position based on velocity
    x += vx * deltaTime;
    y += vy * deltaTime;
    
    // Basic world bounds (we'll refine this later with tile collisions)
    const float worldWidth = 1024.0f;
    const float worldHeight = 768.0f;
    
    if (x < 0) x = 0;
    if (x + width > worldWidth) x = worldWidth - width;
    if (y < 0) y = 0;
    if (y + height > worldHeight) y = worldHeight - height;
    
    // Update animation (placeholder for now)
    if (vx != 0 || vy != 0) {
        animationTimer += deltaTime;
        if (animationTimer > 0.1f) {
            animationTimer = 0;
            frameIndex = (frameIndex + 1) % 4;
        }
    }
}

void Player::setVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

SDL_Rect Player::getCollisionBox() const {
    return SDL_Rect{(int)x, (int)y, width, height};
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect destRect{(int)x, (int)y, width, height};
    
    if (texture) {
        // TODO: Render sprite texture when we have assets
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    } else {
        // For now, render a green square as placeholder
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &destRect);
        
        // Draw outline
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &destRect);
    }
}

