/*=============================================================================
 |   Assignment:  A* Demo
 |
 |       Author:  Siyuan Hu (Kelvin)
 |     Language:  C++11
 |       To Run:  Build in Xcode with essential frameworks added to Build Phases
 |
 |        Class:  Introduction to Game Programming
 |   Instructor:  John Sterling
 |     Due Date:  Nov 19, 2016 11:55 pm
 |
 +-----------------------------------------------------------------------------
 |  Description:
 |
 *===========================================================================*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <queue>
#include "Square.hpp"
#include "PriorityQueue.hpp"
#include "LButton.hpp"


using namespace std;
const int SQUARES_PER_ROW = 30;
const int NROWS = 20;


vector<vector<Square*>> world;

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 500;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const string FONT_PATH = "/Users/Kelvin/Desktop/Game_Programming/HW5PathFinding/A\*\ Demo/A\*\ Demo/Georgia.ttf";

//template<typename T> void print_queue(T& q);


function<bool(Square*, Square*)> cmp = [](Square* a, Square* b) { return a->FScore - b->FScore > 0; };
void print_vector(vector<Square*> const& v);
void print_square(Square* s);
void enable2D(int width, int height);
bool init();
void close();
void draw_rect(float x, float y, float width, float height);
void draw_text(string fontPath, string message, SDL_Rect* r);


int main(int argc, const char * argv[]) {

    
    PriorityQueue<Square*> openList;
    vector<Square*> closedList;
    vector<Square*> optimalPath;
    
    for (int i = 0; i < NROWS; i++) {
        vector<Square*> tempRow;
        for (int j = 0; j < SQUARES_PER_ROW; j++) {
            tempRow.push_back(new Square(i, j));
        }
        world.push_back(tempRow);
    }
    
    Square* startPoint = world[0][0];
    startPoint->setAsStartPoint();
    Square* endPoint = world[NROWS-1][SQUARES_PER_ROW-1];
    endPoint->setAsEndPoint();
    startPoint->calculateHeuristic(endPoint);
    openList.add(startPoint);
    bool optimalPathFound = false;
    bool startButtonClicked = false;
    
    
    LButton b;
    b.setPosition(WINDOW_WIDTH - b.getButtonW() - 25, WINDOW_HEIGHT/2 - b.getButtonH()/2);
    
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        enable2D(WINDOW_WIDTH, WINDOW_HEIGHT);
        bool done = false;
        SDL_Event event;
        
        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
                {
                    done = true;
                }
            }

            SDL_SetRenderDrawColor(renderer, 44, 42, 64, 255);
            SDL_RenderClear(renderer);


            SDL_Rect rect = { b.getPos().x, b.getPos().y, b.getButtonW(), b.getButtonH() };
//            draw_text(FONT_PATH, "Start", &rect);
            b.render(renderer);

            for (vector<Square*> v : world) {
                for (Square* s : v) {
                    s->draw();
                }
            }
            
            for (vector<Square*> v : world) {
                for (Square* s : v) {
                    s->handleEvent(&event);
                }
            }
            
            
            b.handleMouseEvent(&event, &startButtonClicked);
            
            if (!optimalPathFound && startButtonClicked) {
                while (!openList.isEmpty())
                {
                    
                    
                    Square* currentPoint = openList.removeMin();
//                    print_square(currentPoint);  // Show current square
                    closedList.push_back(currentPoint);
                    
                    if (find(closedList.begin(), closedList.end(), endPoint) != closedList.end()) {
                        break;
                    }
                    
                    vector<Square*> adjacentSquares = currentPoint->getAdjacentSquares(world);
//                    cout << "---Adjacent squares---" << endl;
//                    print_vector(adjacentSquares);  // Show squares adjacent to the current square
                    
                    
                    
                    for (Square* s : adjacentSquares)
                    {
                        if (find(closedList.begin(), closedList.end(), s) != closedList.end())
                        {
                            continue;
                        }
                        
                        vector<Square*> openListContainer = openList.getContainer();
                        if (find(openListContainer.begin(), openListContainer.end(), s) == openListContainer.end())
                        {
                            // if s is not in the open list
                            s->GScore = currentPoint->GScore + 1;
                            s->calculateHeuristic(endPoint);
                            s->FScore = s->GScore + s->HScore;
                            s->prev = currentPoint;
                            openList.add(s);
                        } else
                        {
                            // if s is already in the open list
                            int tempGScore = currentPoint->GScore + 1;
                            int tempFScore = tempGScore + s->HScore;
                            if (tempFScore < s->FScore)
                            {
                                s->GScore = tempGScore;
                                s->FScore = tempFScore;
                                s->prev = currentPoint;
                                int s_index = (int)(find(openListContainer.begin(), openListContainer.end(), s) - openListContainer.begin());
                                openList.upheap(s_index);
                            }
                        }
                        
                    }
                    vector<Square*> openListContainer = openList.getContainer();
                    Square* first_item = openListContainer[0];
                    for (Square* s : openListContainer)
                    {
                        if (first_item->FScore > s->FScore)
                            exit(1);
                    }
                    
//                    cout << "------------------------" << endl;
                }
                
                cout << "<----Retrieving path---->" << endl;
                Square* s_temp = endPoint;
                while (s_temp != nullptr)
                {
                    print_square(s_temp);
                    optimalPath.push_back(s_temp);
                    s_temp = s_temp->prev;
                }
                optimalPathFound = true;
            }
            
            if (optimalPathFound && !openList.isEmpty())
            {
                vector<Square*> openListContainer = openList.getContainer();
                for (Square* s : openListContainer)
                {
                    if (s != endPoint && s != startPoint)
                        s->setColor(69, 238, 208);
                }
                
            }
            
            
            if (optimalPathFound && !closedList.empty())
            {
                for (Square* s : closedList)
                {
                    if (s != endPoint && s != startPoint)
                        s->setColor(210, 105, 30);
                }
            }
            
            
            if (optimalPathFound && !optimalPath.empty())
            {
                for (Square* s : optimalPath)
                {
                    if (s != endPoint && s != startPoint)
                    {
                        s->setColor(15, 70, 183);
                    }
                }
            }
            
            
            SDL_RenderPresent(renderer);
        }
    }

    close();
    
    return 0;
}

void print_vector(vector<Square*> const& v) {
    for (Square* item : v) {
        cout << "(" << item->rowIndex << ", " << item->colIndex << ")" << endl;
    }
}

void print_square(Square* s) {
    cout << "(" << s->rowIndex << ", " << s->colIndex << ")" << endl;
}


void enable2D(int width, int height) {
    // Set the viewport within the window in pixels
    glViewport(0, 0, width, height);
    
    // Specify which matrix stack is the target for subsequent matrix operations
    // GL_PROJECTION matrix defines the properties of camera that views the objects in the
    // world coordinate frame, which typically include the zoom factor, aspect ratio,
    // and the near and far clipping planes
    glMatrixMode(GL_PROJECTION);
    
    // Replace the current matrix with the identity matrix
    glLoadIdentity();
    
    // Multiply the current matrix (M) by an orthographic matrix (O),
    // so M is replaced by M • O
    glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    
    // GL_MODELVIEW matrix defines how objects are transformed, which typically
    // include translation, rotation and scaling in the world coordinate frame
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Clear and set new values for the color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

}

bool init()
{
    // Initialization flag
    bool success = true;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        
        // Create window
        window = SDL_CreateWindow("Kelvin's A* Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create an OpenGL context for use with an OpenGL window
            SDL_GLContext context = SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, context);
            
            // Create vsynced renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init(imgFlags) & imgFlags ) ) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    
    if (TTF_Init() != 0)
    {
        cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
        success = false;
    }
    
    return success;
}

void close()
{
    for (vector<Square*> v : world) {
        for (Square* s : v) {
            delete s;
            s = nullptr;
        }
    }
    
    
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    
    // Quit SDL environment
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void draw_rect(float x, float y, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}


void draw_text(string fontPath, string message, SDL_Rect* r) {
    TTF_Font *font;
    font = TTF_OpenFont(fontPath.c_str(), 24);
    if (font == NULL)
    {
        cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
        close();
        exit(1);
    }
    SDL_Color startMessageColor = { 255, 255, 255, 255 };
    SDL_Surface* startMessageS = TTF_RenderText_Solid(font, message.c_str(), startMessageColor);
    SDL_Texture* startMessageT = SDL_CreateTextureFromSurface(renderer, startMessageS);
    SDL_FreeSurface(startMessageS);
    SDL_RenderCopy(renderer, startMessageT, NULL, r);
    SDL_DestroyTexture(startMessageT);
}