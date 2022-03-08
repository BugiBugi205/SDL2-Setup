#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH    1280 
#define SCREEN_HEIGHT   720

FILE *log_file;

int main(int argc, char** argv){
    log_file = fopen("log.txt","wt");

    //wlacza wszystko co mozliwe(dostep do myszki itp) i sprawdza czy dziala
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL_Init Error" << SDL_GetError() << endl;
        return 0;
    }

    //tworzenie okienka
    SDL_Window *window = SDL_CreateWindow(  "Wonsz", 
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            SCREEN_WIDTH, SCREEN_HEIGHT,
                                            SDL_WINDOW_SHOWN
                                            |SDL_WINDOW_RESIZABLE
                                            //|SDL_WINDOW_FULLSCREEN_DESKTOP
                                            );

    //sprawdza czy wskaznik jest pusty
    if(window == nullptr)
    {
        fprintf(log_file,"SDL_CreateWindow() Error: %s\n", SDL_GetError());
        return 0;
    }

    //tworzy obiekt potrzebny do rysowania rzeczy na ekranie
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //sprawdza czy wskaznik jest pusty
    if(renderer == nullptr)
    {
        fprintf(log_file,"SDL_CreateRenderer() Error: %s\n", SDL_GetError());
        return 0;
    }

    //tworzenie bitmapy
    SDL_Surface *bmp = SDL_LoadBMP("img/grass.bmp");

    //sprawdza czy wskaznik jest pusty
    if(bmp == nullptr)
    {
        fprintf(log_file,"SDL_LoadBMP() Error: %s\n", SDL_GetError());
        return 0;
    } 

    //stworzenie tekstury z bitmapy ktora mozna wyswietlic na ekranie
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if(texture == nullptr)
    {
        fprintf(log_file,"SDL_CreateTextureFromSurface() Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_RenderClear(renderer);  //czysci bufor renderera
    SDL_RenderCopy(renderer, texture, NULL, NULL);  //kopiuje teksture na renderer
    SDL_RenderPresent(renderer);    //wyswietla bufor po ktorym sie rysowalo

    SDL_Delay(3000);

    //zwalnianie pamieci
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    fclose(log_file);    
    SDL_Quit();     //przestaje uzywac sdl
    return 0;
}