//
//  LButton.hpp
//  A* Demo
//
//  Created by Kelvin Hu on 11/16/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef LButton_hpp
#define LButton_hpp

#include <stdio.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>


class LButton

{
public:
    // Constructor
    LButton() {};
    
    // Set bottom left position
    void setPosition(int x, int y);
    
    int getButtonW();
    int getButtonH();
    SDL_Point getPos();
    
    //Handle mouse event
    void handleMouseEvent(SDL_Event* e, bool* toStart);
    
    //Show button sprite
    void render(SDL_Renderer* renderer);
    
    
private:
    //Top left position
    SDL_Point pos;
    int buttonW = 100;
    int buttonH = 50;
    
};




#endif /* LButton_hpp */
