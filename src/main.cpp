/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <SDL2/SDL.h>
#include "game.h"
#include "player.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    
    SDL_Window* window = SDL_CreateWindow(
        "Legend Of Haiku",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024, 768,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    
    // Create player at center of screen
    Player player(512 - 16, 384 - 16);
    
    bool running = true;
    uint32_t lastTicks = SDL_GetTicks();
    
    while (running) {
        uint32_t currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        
        const uint8_t* keystate = SDL_GetKeyboardState(nullptr);
        player.handleInput(keystate);
        player.update(deltaTime);
        
        // Render
        SDL_RenderClear(renderer);
        player.render(renderer);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); // ~60 FPS
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
