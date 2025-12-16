#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/sdlhelpers.h"
#include "../headers/algorithms.h"

#include <SDL3/SDL.h>
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"

#define WIDTH 800
#define HEIGHT 700

#define WHITE (SDL_Color) {255, 255, 255, 255}
#define RED (SDL_Color) {255, 0, 0, 255}
#define GREEN (SDL_Color) {0, 255, 0, 255}


void visualBubbleSort(int* arr, SDL_Renderer* prenderer, int n, SDL_FRect* bars, bool* running, size_t skipFrames) {
    size_t frameCount = 0;

    drawAllBars(prenderer, n, bars, WHITE);
    delay(1500, running);  //just to see the unsorted array before sorting starts
    
    bool swapped = true; 
    int outer = n - 1;
    while (swapped && outer >= 0) {
        swapped = false;
        for (int inner = 0; inner < outer; inner++) {

            if (arr[inner] > arr[inner + 1]) {
                int temp = arr[inner];
                arr[inner] = arr[inner + 1];
                arr[inner + 1] = temp;
                swapped = true;
            }

            frameCount++;
            if (frameCount >= skipFrames) {
                frameCount = 0;
                regenerateBarsFromArray(arr, n, bars);
                drawAllBars(prenderer, n, bars, WHITE);
            } 
        }
        outer--;
    }
    SDL_Delay(20);
    regenerateBarsFromArray(arr, n, bars);
    drawAllBars(prenderer, n, bars, WHITE);
    makeItGreen(bars, n, prenderer);
}

void visualInsertionSort(int* arr, SDL_Renderer* prenderer, uint32_t n, SDL_FRect* bars, bool* running, size_t skipFrames) {
    size_t frameCount = 0;
    drawAllBars(prenderer, n, bars, WHITE);
    delay(1500, running);  //just to see the unsorted array before sorting starts
    
    for(size_t i = 1; i < n; i++) {

        SDL_FRect value = bars[i];
        uint32_t position = i;

        while(position > 0 && bars[position - 1].h > value.h) {
            bars[position] = bars[position - 1];
            position--;
        }
        bars[position] = value;

        frameCount++;
        if (frameCount >= skipFrames) {
            frameCount = 0;
            regenerateBarsFromArray(arr, n, bars);
            drawAllBars(prenderer, n, bars, WHITE);
        } 
    }
    drawAllBars(prenderer, n, bars, WHITE);
    delay(1500, running);  //just to see the unsorted array before sorting starts
    //
    SDL_Delay(20);
    regenerateBarsFromArray(arr, n, bars);
    drawAllBars(prenderer, n, bars, WHITE);
    makeItGreen(bars, n, prenderer);
}

int main(int argc, char **argv) {

    int barWidth, skipFrames = 0;

    if (argc >= 2) { barWidth = atoi(argv[1]); }
    if (argc >= 3) { skipFrames = atoi(argv[2]); }
    
    int choice;
    printf("(1) Bubble Sort\n");
    printf("(2) Insertion Sort\n");
    printf("(3) Quick Sort\n");
    scanf_s("%d", &choice);

    srand(time(NULL));

    //init SDL
    SDL_Window *pwindow = SDL_CreateWindow("SDL3 Window", WIDTH, HEIGHT, 0);
    if (!pwindow) { printf("Could not create window: %s\n", SDL_GetError()); return 1; }

    SDL_Renderer *prenderer = SDL_CreateRenderer(pwindow, NULL);
    if (!prenderer) { printf("Could not create renderer: %s\n", SDL_GetError()); return 1; }


    //create array and bars
    int n = WIDTH / barWidth;
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % HEIGHT;
    }

    bool running = true;
    SDL_FRect *bars = malloc(n * sizeof(SDL_FRect));

    for (int i = 0; i < n; i++) {
        int barHeight = arr[i];
        bars[i].x = i * barWidth;
        bars[i].y = HEIGHT - barHeight;
        bars[i].w = barWidth - 1;
        bars[i].h = barHeight;
    }

    //call sorting algorithm
    switch (choice) {
        case 1:
            visualBubbleSort(arr, prenderer, n, bars, &running, skipFrames);
            break;
        case 2:
            visualInsertionSort(arr, prenderer, n, bars, &running, skipFrames);
            break;
        case 3:
            break;
    }

    printArray(arr, n);
    delay(3000, &running);
   
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
