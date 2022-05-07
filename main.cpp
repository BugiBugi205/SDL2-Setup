#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH    1280 
#define SCREEN_HEIGHT   720

int main(int argc, char** argv){
    FILE *log_file = fopen("log.txt","wt");

    //turns on everything possible(e.g mouse access) and looks for errors
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL_Init Error" << SDL_GetError() << endl;
        return 0;
    }

    //window creator
    SDL_Window *window = SDL_CreateWindow(  "SDL setup", 
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);  //clears render buffer

    SDL_RenderPresent(renderer);    //displays buffer what we were drawing on

    SDL_Delay(5000);

    //memory release
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    fclose(log_file);
    SDL_Quit();     //stops using sdl
    return 0;
}