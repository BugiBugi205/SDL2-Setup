#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH    1280 
#define SCREEN_HEIGHT   720

FILE *log_file;

int main(int argc, char** argv){
    log_file = fopen("log.txt","wt");

    //turns on everything possible(e.g mouse access) and looks for errors
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL_Init Error" << SDL_GetError() << endl;
        return 0;
    }

    //window creator
    SDL_Window *window = SDL_CreateWindow(  "Wonsz", 
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            SCREEN_WIDTH, SCREEN_HEIGHT,
                                            SDL_WINDOW_SHOWN
                                            |SDL_WINDOW_RESIZABLE
                                            //|SDL_WINDOW_FULLSCREEN_DESKTOP
                                            );

    //checks is pointer empty
    if(window == nullptr)
    {
        fprintf(log_file,"SDL_CreateWindow() Error: %s\n", SDL_GetError());
        return 0;
    }

    //creates object necessary for drawing things on screen
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //checks is pointer empty
    if(renderer == nullptr)
    {
        fprintf(log_file,"SDL_CreateRenderer() Error: %s\n", SDL_GetError());
        return 0;
    }

    //bitmap creator
    SDL_Surface *bmp = SDL_LoadBMP("img/grass.bmp");

    //checks is pointer empty
    if(bmp == nullptr)
    {
        fprintf(log_file,"SDL_LoadBMP() Error: %s\n", SDL_GetError());
        return 0;
    } 

    //creates texture from bitmap that can be displayed on screen
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if(texture == nullptr)
    {
        fprintf(log_file,"SDL_CreateTextureFromSurface() Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_RenderClear(renderer);  //clears render buffer
    SDL_RenderCopy(renderer, texture, NULL, NULL);  //copy texture to renderer
    SDL_RenderPresent(renderer);    //displays buffer what we were drawing on

    SDL_Delay(3000);

    //memory cleaning
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    fclose(log_file);    
    SDL_Quit();     //stops using sdl
    return 0;
}