#include "Headers/window.h"


Window::Window() {
    Running = true; // Boolean for the while loop
}
 
int Window::OnExecute() {   // Called in the main function 
    if(!OnInit()){          // if the window cannot init, return -1 (mains return value)
        return -1;
    }

    SDL_Event Event;
    
                //    x   y  w  h
    SDL_Rect rect = {100,100,25,25};// A struct that holds rectangle data
    // Game loop
    while(Running){
        while(SDL_PollEvent(&Event)){
            OnEvent(&Event);
        }
        OnLoop();
        OnRender(&rect);
    }
    // Game loop
    OnCleanup(); // Cleans up

    return 0;   //mains return function
}

bool Window::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){ // if the init code of init everything is < 0 then return false
        return false;
    }
    
    Surf_Display = SDL_CreateWindow("Sample program in SDL2",SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      640, 480, 0);
    if(Surf_Display == NULL){
        printf("Error couldnt create window\nReason:\t%s\nEnding program....",SDL_GetError());
        return false;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC; // Used to say how to render the window
    Rend = SDL_CreateRenderer(Surf_Display, -1, render_flags); // The renderer
    
    if(!Rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(Surf_Display);
        SDL_Quit();
        return false;
    }
    return true;
}

void Window::OnEvent(SDL_Event* Event) { // Reads user events
    switch(Event->type){

        case SDL_QUIT:
            Running = false;
            break;
        case SDL_KEYDOWN:
            switch(Event->key.keysym.scancode){ // reads keyCodes

                case SDL_SCANCODE_SPACE:
                    std::cout << "Lol space" << std::endl;
                    break;
                default:
                    break;
            }
            default:
            break;
    }
}

void Window::OnLoop() { // idk what this is for tbh
}

void Window::OnRender(SDL_Rect* r) { // function for what the renderer should do
    
    SDL_SetRenderDrawColor(Rend, 0, 0, 0, 255); // draw background
    SDL_RenderClear(Rend);  // clear frame

    SDL_SetRenderDrawColor(Rend, 255, 0, 0, 255); // set colour in buffer
    SDL_RenderFillRect(Rend, r); // send the colour to fill the rect pixels
    SDL_RenderPresent(Rend); // render all that was previous to the screen
    SDL_Delay(1000/60); // force 60FPS cap
}

void Window::OnCleanup() { // does all it says on the tin tbh
    SDL_DestroyRenderer(Rend);
    SDL_DestroyWindow(Surf_Display);
    SDL_Quit();
}