//Кардиоида: вращение, масштабирование, смещение оси координат
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#define PI 3.1415
void drawPoint (SDL_Renderer *renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}
void drawBoldPoint (SDL_Renderer *renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderDrawPoint(renderer, x+1, y);
    SDL_RenderDrawPoint(renderer, x, y+1);
    SDL_RenderDrawPoint(renderer, x+1, y-1);
    SDL_RenderDrawPoint(renderer, x+1, y+1);
    SDL_RenderDrawPoint(renderer, x-1, y+1);
    SDL_RenderDrawPoint(renderer, x-1, y);
    SDL_RenderDrawPoint(renderer, x, y-1);
    SDL_RenderDrawPoint(renderer, x-1, y-1);
    SDL_RenderDrawPoint(renderer, x+2, y+1);
    SDL_RenderDrawPoint(renderer, x+2, y);
    SDL_RenderDrawPoint(renderer, x+2, y-1);
    SDL_RenderDrawPoint(renderer, x-2, y+1);
    SDL_RenderDrawPoint(renderer, x-2, y);
    SDL_RenderDrawPoint(renderer, x-2, y-1);
    SDL_RenderDrawPoint(renderer, x+1, y+2);
    SDL_RenderDrawPoint(renderer, x, y+2);
    SDL_RenderDrawPoint(renderer, x-1, y+2);
    SDL_RenderDrawPoint(renderer, x+1, y-2);
    SDL_RenderDrawPoint(renderer, x, y-2);
    SDL_RenderDrawPoint(renderer, x-1, y-2);
}

void drawLine (SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }
    int width = 800, height = 800;
    int shiftY = 300, shiftX = 300;
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (win == NULL){
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        printf("SDL_CreateRenderer Error: %s", SDL_GetError());
        return 1;
    }
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
        int scale = 100;
        
        
        for (double angle = 0, scale = 100, shiftX = 400, shiftY = 400; angle < 40 * PI; angle+=PI/13, scale+=-20+ rand()%41, shiftX+=-20+ rand()%41, shiftY+=-20+rand()%41){
            SDL_SetRenderDrawColor(ren, 18, 18, 18, 255);
            SDL_RenderClear(ren);
            SDL_SetRenderDrawColor(ren, 180, 180, 180, 255);
            drawLine(ren, -shiftX*cos(angle) + shiftX, shiftX*sin(angle) + shiftY, shiftX*cos(angle)+shiftX, -shiftX*sin(angle) + shiftY);
            drawLine(ren, -shiftY*sin(angle) + shiftX, -shiftY*cos(angle) + shiftY, shiftY*sin(angle) + shiftX , shiftY*cos(angle)+shiftY);
            SDL_SetRenderDrawColor(ren, 187, 134, 252, 255);
            for (double i = 0; i < 2*PI; i+=0.001) {
                double x = cos(i)*(1+cos(i));
                double y = sin(i)*(1+cos(i));
                drawPoint(ren, (x * cos(angle) + y * sin(angle))*scale+shiftX, (- x * sin(angle) + y * cos(angle))*scale+shiftY);
            }
            SDL_SetRenderDrawColor(ren, 190, 0, 32, 255);
            drawBoldPoint(ren, (2 * cos(angle) + 0 * sin(angle))*scale+shiftX, (- 2 * sin(angle) + 0 * cos(angle))*scale + shiftY);
            drawBoldPoint(ren,
                            ( 3*cos(angle)/4 + sqrt(3)*3*sin(angle)/4 )*scale+shiftX,
                            ( -3*sin(angle)/4 + sqrt(3)*3*cos(angle)/4 )*scale+shiftY
                          );
            drawBoldPoint(ren,
              ( 3*cos(angle)/4 - sqrt(3)*3*sin(angle)/4 )*scale+shiftX,
              ( - 3*sin(angle)/4 - sqrt(3)*3*cos(angle)/4 )*scale+shiftY
            );
            drawBoldPoint(ren, shiftX, shiftY);
            SDL_RenderPresent(ren);
            
        }
        
      
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
