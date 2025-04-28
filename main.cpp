#include<iostream>
#include<raylib.h>
#include"Libs/variables.h"
#include "Libs/Classes.h"
using namespace std;


bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}



int main(){

    InitWindow(2*offSet + cellSize*cellCount , 2*offSet +  cellSize*cellCount , "Snake Game");
    SetTargetFPS(60);
    Game game = Game();

    while(WindowShouldClose() == false){
        BeginDrawing();

        // Drawing
        if(eventTriggered(0.2)){
            game.update();
        }

        if(IsKeyPressed(KEY_UP) && game.snake.Position.y != 1){
            game.snake.Position = {0,-1};
            game.running = true;
        }
        else if(IsKeyPressed(KEY_DOWN) && game.snake.Position.y != -1){
            game.snake.Position = {0 , 1};
            game.running = true;
        }
        else if(IsKeyPressed(KEY_RIGHT) && game.snake.Position.x != -1){
            game.snake.Position = {1 , 0};
            game.running = true;
        }
        else if(IsKeyPressed(KEY_LEFT) && game.snake.Position.x != 1){
            game.snake.Position = {-1 , 0};
            game.running = true;
        }
        ClearBackground(Green);
        Rectangle Rec = {(float)offSet-5 ,(float)offSet-5,(float)cellSize*cellCount+10,(float)cellSize*cellCount+10};
        DrawRectangleLinesEx(Rec , 5 , DarkGreen);
        DrawText("Snake Game" , offSet - 5 , 20 , 40 , DarkGreen);
        DrawText( TextFormat("%i",game.score) , offSet - 5 , offSet+cellSize*cellCount+10, 40 , DarkGreen );
        game.Draw();

        EndDrawing();
    }


    CloseWindow();
    return 0;
}