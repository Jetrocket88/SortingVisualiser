#ifndef SDLHELPERS_H
#define SDLHELPERS_H

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

void renderFRect(SDL_Renderer *renderer, SDL_FRect rect, SDL_Color color);
void drawAllBars(SDL_Renderer* prenderer, int n, SDL_FRect* bars, SDL_Color color);
void delay(Uint32 milliseconds, bool* running);
void drawBarsColourIndex(SDL_FRect *bars, int n, SDL_Color color, SDL_Renderer *prenderer, int colourIndex);
void makeItGreen(SDL_FRect* bars, int n, SDL_Renderer *prenderer);
void printArray(int *arr, size_t n);
void swapBars(SDL_FRect *bar1, SDL_FRect *bar2);
void drawBarsColourTwoIndex(SDL_FRect *bars, int n, SDL_Color color1, SDL_Color color2, SDL_Renderer *prenderer, int c1, int c2);
void drawBarsTwoColours(SDL_FRect *bars, int n, SDL_Color color1, SDL_Renderer *prenderer, int c1, int c2);

#endif
