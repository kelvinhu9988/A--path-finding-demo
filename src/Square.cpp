//
//  Square.cpp
//  A* Demo
//
//  Created by Kelvin Hu on 11/16/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#include "Square.hpp"

std::vector<Square*> Square::getAdjacentSquares(std::vector<std::vector<Square*>>& world) {
    std::vector<Square*> tempV;
    int nRows = (int)world.size();
    int nCols = (int)world[0].size();
    
#define ADD_IF_NOT_BARRIER(s) if (!s->isBarrier) tempV.push_back(s)
    
    if (rowIndex == 0)
    {
        if (colIndex == 0)
        {
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
        }
        else if (colIndex == nCols-1)
        {
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
        }
        else
        {
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
        }
    }
    else if (rowIndex == nRows-1)
    {
        if (colIndex == 0)
        {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
        }
        else if (colIndex == nCols-1)
        {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
        }
        else
        {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
        }
        
    }
    else if (colIndex == 0)
    {
        ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
        ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
        ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
    }
    else if (colIndex == nCols-1)
    {
        ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
        ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
        ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
    }
    else
    {
        ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
        ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
        ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
        ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
    }
    return tempV;
}

void Square::calculateHeuristic(Square* endPoint) {
    this->HScore = abs(endPoint->rowIndex - rowIndex) + abs(endPoint->colIndex - colIndex);
}

void Square::handleEvent(SDL_Event* e) {
    
    if (!isStart && !isEnd)
    {
        if (e->type == SDL_MOUSEBUTTONDOWN)
        {   // Click on the grid to permanently set the square color to black
            int x, y;
            SDL_GetMouseState(&x, &y);
            
            bool inside = true;
            if (x <= pos.x)
            {
                inside = false;
            }
            else if (x >= pos.x + edgeLength)
            {
                inside = false;
            }
            else if (y <= pos.y)
            {
                inside = false;
            }
            else if (y >= pos.y + edgeLength)
            {
                inside = false;
            }
            
            if (inside)
            {
                r = 0;
                g = 0;
                b = 0;
                isBarrier = true;
                isUsed = true;
            }
        }
        else
        {
            // Hover the mouse over the grid temporarily to set the square color to black
            int x, y;
            SDL_GetMouseState(&x, &y);
            
            bool inside = true;
            if (x <= pos.x)
            {
                inside = false;
            }
            else if (x >= pos.x + edgeLength)
            {
                inside = false;
            }
            else if (y <= pos.y)
            {
                inside = false;
            }
            else if (y >= pos.y + edgeLength)
            {
                inside = false;
            }
            
            
            if (inside)
            {
                r = 0;
                g = 0;
                b = 0;
            }
            else if (!isUsed)
            {
                r = 255;
                g = 255;
                b = 255;
            }
        }
        
    }
    
    
    if (!isStart && !isEnd && e->type == SDL_MOUSEBUTTONDOWN)
    {   // Hover the mouse over the grid temporarily sets the square color to black
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        bool inside = true;
        if (x <= pos.x)
        {
            inside = false;
        } else if (x >= pos.x + edgeLength)
        {
            inside = false;
        } else if (y <= pos.y)
        {
            inside = false;
        } else if (y >= pos.y + edgeLength)
        {
            inside = false;
        }
        
        
        if (inside)
        {
            r = 0;
            g = 0;
            b = 0;
            isBarrier = true;
            isUsed = true;
        }
    }
    
}

void Square::draw() {
    float padding = 1.0f;
    float width = edgeLength - padding;
    float height = edgeLength - padding;
    float x = pos.x;
    float y = 500 - pos.y;
    glColor4f((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();
}

void Square::setAsStartPoint()
{
    isStart = true;
    GScore = 0;
    r = 255;
    g = 204;
    b = 92;
    isUsed = true;
    
}

void Square::setAsEndPoint()
{
    isEnd = true;
    HScore = 0;
    r = 255;
    g = 76;
    b = 76;
    isUsed = true;
}

void Square::setColor(int _r, int _g, int _b)
{
    r = _r;
    g = _g;
    b = _b;
    isUsed = true;
}

