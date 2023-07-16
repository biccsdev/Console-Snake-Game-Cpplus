//author: @biccsdev

#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

int x,y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int tailLength;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};

eDirection dir;

//Initializing program variables, setting initial positions for fruit and snake, setting score to 0
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

//Draws the game in the console screen
void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j == 0)
            {
                cout << "#";
            }
            //Prints the snake head
            if (i == y && j == x)
            {
                cout << "0";
            }
            //Prints the fruit
            else if (i == fruitY && j == fruitX )
            {
                cout << "$";
            }
            else
            {
                bool print = false;
                //Prints the snake body if any
                for(int k = 0; k < tailLength; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                {
                    cout << " ";
                }
            }


            if(j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

//Manages the user input ( W,A,S,D keys)
void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

//States the game Logic
void Logic()
{
    //Calculates the snake's body position
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < tailLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    //Changes the snake's head position
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    //Set game Over if the snake's head touches any wall
    if(x > width || x < 0 | y > height || y < 0)
    {
        gameOver = true;
    }

    //Checks if the snake hits its tail, if so turns the game over
    for (int i = 0; i < tailLength; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }

    //Checks if the snake's head touches the fruit, if so increments the score, increments tail's length and re-spawns the fruit
    if(x == fruitX && y == fruitY)
    {
        score+= 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}

//Implements the game
int main()
{
    Setup();
    while(!gameOver )
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    return 0;
}
