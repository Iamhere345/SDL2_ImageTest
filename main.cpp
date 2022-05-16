#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

using std::string;

SDL_Window* getWindow(SDL_Window* window, char* title, int window_width, int window_height) {

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, NULL);

    if (window != NULL) {
        return window;
    } else {
        printf("An error has occurred creating the %s window. SDL_ERROR: %s", title, SDL_GetError());
        return NULL;
    }

}

SDL_Surface* loadMedia() {

    bool success = NULL;

    SDL_Surface* image = SDL_LoadBMP("img/bliss.bmp");

    if (!image) {
        printf("Unable to load image %s. SDL_ERROR: %s\n", "img/bliss.bmp", SDL_GetError());
        return NULL;
    }

    return image;

}

int main(int argc, char** argv) {

    int init = SDL_Init(SDL_INIT_VIDEO);

    if (init < 0) {
        printf("An error has occurred initialising SDL. SDL_ERROR: %s", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = getWindow(window, "SDL2 Image Test", 895, 720);
    SDL_Surface* screen;
    SDL_Surface* image = loadMedia();

    if (window == NULL) {
        return 1;
    }

    screen = SDL_GetWindowSurface(window);

    if (!image) {
        printf("Failed to load media.");
        return 1;
    }

    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_UpdateWindowSurface(window);

    bool active = true;
    SDL_Event event;

    while (active) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                active = false;
            }
        }
        SDL_Delay(16);
    }

    SDL_FreeSurface(image);
    image = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;

}