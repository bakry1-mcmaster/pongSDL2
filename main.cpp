#define SDL_MAIN_HANDLED


#include <iostream>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_image.h"

using namespace std;

SDL_Window* gamewindow;
SDL_Renderer* gamerenderer;


bool switcher = true;

bool gamerunning = false;



void initialize();
void InputProcessing();
void drawScreen();
void resize();
void exitGame();

int main(int argc, char *argv[])
{
    

    initialize();

    while(!gamerunning)
    {
        drawScreen();
        SDL_Delay(10);
    }

    return 0;
}

void initialize()
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout<<"Failed to initialize. Exiting...."<< endl;
        SDL_Quit();
        return;
    }

    else
    {
        

        gamewindow = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, 0);
        SDL_SetWindowFullscreen(gamewindow, 0);
        gamerenderer = SDL_CreateRenderer(gamewindow, -1, 0);

        SDL_SetRenderDrawColor(gamerenderer, 0, 0, 255, 255);
        SDL_RenderClear(gamerenderer);
        SDL_RenderPresent(gamerenderer);

        if(gamewindow == nullptr)
        {
            cout<<"Failed to initialize. Exiting.... (Why do I even put this message lmao im not looking at the terminal)"<< endl;
            SDL_DestroyWindow(gamewindow);
            SDL_DestroyRenderer(gamerenderer);
            SDL_Quit();
            return;
        }
    }
}

void InputProcessing()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    exitGame();
                    break;
                
                case SDLK_f:
                    resize();
                    break;
                
                default:
                    break;
            }
        }

        else if(e.type == SDL_QUIT)
        {
            exitGame();
            return;
        }

    }


}


void drawScreen()
{
    SDL_SetRenderDrawColor(gamerenderer, 0, 0, 255, 255);
    SDL_RenderClear(gamerenderer);


    SDL_RenderPresent(gamerenderer);
}

void resize()
{
    if(switcher == false)
    {
        switcher = true;
        SDL_SetWindowFullscreen(gamewindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

        int width, height;

        SDL_SetWindowSize(gamewindow, 1920, 1080);
        
        
        
    }


    else if(switcher == true)
    {
        switcher = false;
        SDL_SetWindowFullscreen(gamewindow, 0);
    

        SDL_SetWindowSize(gamewindow, 640, 360);

        
    }
    
}

void exitGame()
{
    SDL_DestroyWindow(gamewindow);
    SDL_DestroyRenderer(gamerenderer);
    SDL_Quit();

    gamerunning = true;

    cout<<"Game exited"<<endl;
}


