#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/sdlhelpers.h"
#include "../headers/constants.h"
#include "../headers/algorithms.h"

#include <SDL3/SDL.h>
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"

void visualBubbleSort(SDL_Renderer* prenderer, SDL_FRect *bars, size_t n, bool *running, size_t skipFrames) {
    size_t frameCount = 0;

    drawAllBars(prenderer, n, bars, WHITE);
    delay(1500, running);  //just to see the unsorted array before sorting starts
    
    bool swapped = true; 
    int outer = n - 1;
    while (swapped && outer >= 0) {
        swapped = false;
        for (int inner = 0; inner < outer; inner++) {

            if (bars[inner].h > bars[inner + 1].h) {
                swapBars(&bars[inner], &bars[inner + 1]);
                swapped = true;
            }

            frameCount++;
            if (frameCount >= skipFrames) {
                frameCount = 0;
                drawAllBars(prenderer, n, bars, WHITE);
            } 
        }
        outer--;
    }
    SDL_Delay(20);
    drawAllBars(prenderer, n, bars, WHITE);
    makeItGreen(bars, n, prenderer);
}


void visualInsertionSort(SDL_Renderer* prenderer, size_t n, SDL_FRect* bars, bool* running, size_t skipFrames) {
    size_t frameCount = 0;
    drawAllBars(prenderer, n, bars, WHITE);
    delay(1500, running);  //just to see the unsorted array before sorting starts
    
    for (size_t i = 1; i < n; i++) {

        float valueH = bars[i].h;
        float valueY = bars[i].y;

        size_t position = i;

        while(position > 0 && bars[position - 1].h > valueH) {
            swapBars(&bars[position], &bars[position - 1]);
            position--;
        }
        bars[position].h = valueH;
        bars[position].y = valueY;

        frameCount++;
        if (frameCount >= skipFrames) {
            frameCount = 0;
            drawAllBars(prenderer, n, bars, WHITE);
        } 
        SDL_Delay(3);
    }

    SDL_Delay(20);
    drawAllBars(prenderer, n, bars, WHITE);
    makeItGreen(bars, n, prenderer);
}

int visualPartition(SDL_Renderer* prenderer, size_t n, SDL_FRect* bars, size_t skipFrames, int low, int high) {
    size_t frameCount = 0;

    SDL_FRect pivot = bars[high];
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (bars[j].h < pivot.h) {
            i++;
            swapBars(&bars[j], &bars[i]);

            if (frameCount >= skipFrames) {
                frameCount = 0;
                drawAllBars(prenderer, n, bars, WHITE);
            }
            frameCount++;
        }
    }
    SDL_Delay(10);
    swapBars(&bars[i + 1], &bars[high]);
    drawAllBars(prenderer, n, bars, WHITE);
    return i + 1;
}

void visualQuickSort(SDL_Renderer* prenderer, size_t n, SDL_FRect* bars, bool *running, size_t skipFrames, int low, int high) {
    if(low == 0 && high == n) {
        drawAllBars(prenderer, n, bars, WHITE);
        delay(2000, running);  //just to see the unsorted array before sorting starts
    }

    if (low < high) {
        int pi = visualPartition(prenderer, n, bars, skipFrames, low, high);
        visualQuickSort(prenderer, n, bars, running, skipFrames, low, pi - 1);
        visualQuickSort(prenderer, n, bars, running, skipFrames, pi + 1, high);
    } 
    drawAllBars(prenderer, n, bars, WHITE);
}


int main(int argc, char **argv) {

    int barWidth = 0;
    int skipFrames = 0;

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
        bars[i].w = barWidth - 0.2f;
        bars[i].h = barHeight;
    }

    switch (choice) {
        case 1:
            visualBubbleSort(prenderer, bars, n, &running, skipFrames);
            break;
        case 2:
            visualInsertionSort(prenderer, n, bars, &running, skipFrames);
            break;
        case 3:
            visualQuickSort(prenderer, n, bars, &running, skipFrames, 0, n);
            delay(1500, &running);
            makeItGreen(bars, n, prenderer);
            break;
    }

    delay(3000, &running);
   
    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
