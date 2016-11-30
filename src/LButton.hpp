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
    void setPosition(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    };
    
    int getButtonW()
    {
        return buttonW;
    }
    
    int getButtonH()
    {
        return buttonH;
    }
    
    SDL_Point getPos()
    {
        return pos;
    }
    
    //Handle mouse event
    void handleMouseEvent(SDL_Event* e, bool* toStart)
    {
        if (e->type == SDL_MOUSEBUTTONUP)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            
            bool inside = true;
            if (x <= pos.x)
            {
                inside = false;
            } else if (x >= pos.x + buttonW)
            {
                inside = false;
            } else if (y <= pos.y)
            {
                inside = false;
            } else if (y >= pos.y + buttonH)
            {
                inside = false;
            }
            
            
            if (inside)
            {
                *toStart = true;
            }
            
            
        }
    };
    
    //Show button sprite
    void render(SDL_Renderer* renderer)
    {
        glColor4f(159/255.0f, 164/255.0f, 172/255.0f, 1.0f);
        SDL_Rect rect = { pos.x, pos.y, buttonW, buttonH };
        SDL_RenderFillRect(renderer, &rect);
    };
    
private:
    //Top left position
    SDL_Point pos;
    int buttonW = 100;
    int buttonH = 50;
    
};




#endif /* LButton_hpp */
