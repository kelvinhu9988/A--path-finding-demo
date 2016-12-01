//
//  LButton.cpp
//  A* Demo
//
//  Created by Kelvin Hu on 11/16/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "LButton.hpp"

void LButton::setPosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
};

int LButton::getButtonW()
{
    return buttonW;
}

int LButton::getButtonH()
{
    return buttonH;
}

SDL_Point LButton::getPos()
{
    return pos;
}

void LButton::handleMouseEvent(SDL_Event* e, bool* toStart)
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

void LButton::render(SDL_Renderer* renderer)
{
    glColor4f(159/255.0f, 164/255.0f, 172/255.0f, 1.0f);
    SDL_Rect rect = { pos.x, pos.y, buttonW, buttonH };
    SDL_RenderFillRect(renderer, &rect);
};

