#include <stdint.h>

#include "../headers/constants.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"

void regenerateBarsFromArray(int* arr, int n, SDL_FRect* bars) {
    for (int i = 0; i < n; i++) {
        int barHeight = arr[i];
        bars[i].y = HEIGHT - barHeight;
        bars[i].h = barHeight;
    }
}

void renderFRect(SDL_Renderer *renderer, SDL_FRect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void drawAllBars(SDL_Renderer* prenderer, int n, SDL_FRect* bars, SDL_Color color) {

    SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255); //set the draw colour to black
    SDL_RenderClear(prenderer); //clear screen to black
    
    for (int i = 0; i < n; i++) {
        renderFRect(prenderer, bars[i], color);
    }
    SDL_RenderPresent(prenderer);
}

void delay(Uint32 milliseconds, bool* running) {
    if (milliseconds <= 0) return;
    Uint32 start = SDL_GetTicks();
    while (SDL_GetTicks() - start < milliseconds) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {  
            if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
                *running = false;
                return;
            }
        }
    }
}
 
void drawBarsColourIndex(SDL_FRect *bars, int n, SDL_Color color, SDL_Renderer *prenderer, int colourIndex) {
    SDL_SetRenderDrawColor(prenderer, 0, 0, 0, 255); //set the draw colour to black
    SDL_RenderClear(prenderer); //clear screen to black
    
    for (int i = 0; i < n; i++) {
        if (i <= colourIndex) { 
        //draws all the ones before the colour index as the colour
            renderFRect(prenderer, bars[i], color);
        } else {
            renderFRect(prenderer, bars[i], WHITE);
        }
    }
    SDL_RenderPresent(prenderer);
}

void makeItGreen(SDL_FRect* bars, int n, SDL_Renderer *prenderer) {
    int i = 0;
    while(true) {
        drawBarsColourIndex(bars, n, GREEN, prenderer, i++);
        if (i >= n) {
            break;
        }
        SDL_Delay(8);
    }
    SDL_Delay(30);
    drawBarsColourIndex(bars, n, GREEN, prenderer, n);
}


void printArray(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
}
