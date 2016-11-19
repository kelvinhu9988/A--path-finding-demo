//
//  Square.hpp
//  A* Demo
//
//  Created by Kelvin Hu on 11/16/16.
//  Copyright © 2016 Kelvin Hu. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <vector>



class Square {
public:
    int rowIndex;
    int colIndex;
    int edgeLength = 25;
    int FScore, GScore, HScore;
    int r, g, b;
    bool clicked;
    bool isBarrier;
    bool isStart;
    bool isEnd;
    bool isUsed;
    SDL_Point pos;
    Square* prev;
    Square* next;
    
    Square(int row, int col) {
        this->rowIndex = row;
        this->colIndex = col;
        this->prev = nullptr;
        this->next = nullptr;
        this->pos.x = colIndex * edgeLength;
        this->pos.y = rowIndex * edgeLength;
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->clicked = false;
        this->isBarrier = false;
        this->isStart = false;
        this->isEnd = false;
        this->FScore = INT_MAX;
        this->GScore = INT_MAX;
        this->HScore = INT_MAX;
    }
    
    void calculateHeuristic(Square* endPoint) {
        this->HScore = abs(endPoint->rowIndex - rowIndex) + abs(endPoint->colIndex - colIndex);
    }
    
    std::vector<Square*> getAdjacentSquares(std::vector<std::vector<Square*>>& world) {
        std::vector<Square*> tempV;
        int nRows = (int)world.size();
        int nCols = (int)world[0].size();
        
        #define ADD_IF_NOT_BARRIER(s) if (!s->isBarrier) tempV.push_back(s)
        
        if (rowIndex == 0) {
            if (colIndex == 0) {
                ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
            } else if (colIndex == nCols-1) {
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
                ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
//                if (!world[rowIndex][colIndex-1]->isBarrier) tempV.push_back(world[rowIndex][colIndex-1]);
//                if (!world[rowIndex+1][colIndex]->isBarrier) tempV.push_back(world[rowIndex+1][colIndex]);
            } else {
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
                ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
//                tempV.push_back(world[rowIndex][colIndex-1]);
//                tempV.push_back(world[rowIndex+1][colIndex]);
//                tempV.push_back(world[rowIndex][colIndex+1]);
            }
        } else if (rowIndex == nRows-1) {
            if (colIndex == 0) {
                ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
//                tempV.push_back(world[rowIndex-1][colIndex]);
//                tempV.push_back(world[rowIndex][colIndex+1]);
            } else if (colIndex == nCols-1) {
                ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
//                tempV.push_back(world[rowIndex-1][colIndex]);
//                tempV.push_back(world[rowIndex][colIndex-1]);
            } else {
                ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
                ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
//                tempV.push_back(world[rowIndex-1][colIndex]);
//                tempV.push_back(world[rowIndex][colIndex-1]);
//                tempV.push_back(world[rowIndex][colIndex+1]);
            }
            
        } else if (colIndex == 0) {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
//            tempV.push_back(world[rowIndex-1][colIndex]);
//            tempV.push_back(world[rowIndex+1][colIndex]);
//            tempV.push_back(world[rowIndex][colIndex+1]);
        } else if (colIndex == nCols-1) {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
//            tempV.push_back(world[rowIndex-1][colIndex]);
//            tempV.push_back(world[rowIndex][colIndex-1]);
//            tempV.push_back(world[rowIndex+1][colIndex]);
        } else {
            ADD_IF_NOT_BARRIER(world[rowIndex-1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex-1]);
            ADD_IF_NOT_BARRIER(world[rowIndex+1][colIndex]);
            ADD_IF_NOT_BARRIER(world[rowIndex][colIndex+1]);
//            tempV.push_back(world[rowIndex-1][colIndex]);
//            tempV.push_back(world[rowIndex][colIndex-1]);
//            tempV.push_back(world[rowIndex+1][colIndex]);
//            tempV.push_back(world[rowIndex][colIndex+1]);
        }
        return tempV;
    }
    
    
    void handleEvent(SDL_Event* e) {
    
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
            } else
            {
                // Hover the mouse over the grid temporarily to set the square color to black
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
                } else if (!isUsed) {
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
    
    void draw() {
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
    
    void setAsStartPoint()
    {
        isStart = true;
        GScore = 0;
        r = 255;
        g = 204;
        b = 92;
        isUsed = true;
    
    }
    
    void setAsEndPoint()
    {
        isEnd = true;
        HScore = 0;
        r = 255;
        g = 76;
        b = 76;
        isUsed = true;
    }
    
    
    
    void setColor(int _r, int _g, int _b)
    {
        r = _r;
        g = _g;
        b = _b;
        isUsed = true;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
};


#endif /* Square_hpp */
