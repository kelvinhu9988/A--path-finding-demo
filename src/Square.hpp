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
    
    
    void draw();
    void setAsStartPoint();
    void setAsEndPoint();
    void setColor(int _r, int _g, int _b);
    void handleEvent(SDL_Event* e);
    void calculateHeuristic(Square* endPoint);
    std::vector<Square*> getAdjacentSquares(std::vector<std::vector<Square*>>& world);
};


#endif /* Square_hpp */
