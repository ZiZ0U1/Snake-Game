#include<iostream>
#include<raylib.h>
#include <raymath.h>
#include<deque>
using namespace std;


bool ElementInDeque(Vector2 pos , deque<Vector2> snakeBody);


class Snake{
    public:
        bool IncreaseSize = false;
        deque<Vector2> snakeBody = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
        Vector2 Position = {0,1};
        void DrawSnake(){
            for(unsigned int i=0 ; i < snakeBody.size() ; ++i ){
                float x = snakeBody[i].x;
                float y = snakeBody[i].y;
                Rectangle Rec = {offSet + x*cellSize , offSet + y*cellSize ,(float)cellSize ,(float)cellSize};
                DrawRectangleRounded( Rec , 0.5 , 6 , DarkGreen);
            }
        }
        void updatePosition(){
            snakeBody.push_front(snakeBody[0] + Position);
            if(IncreaseSize){
                IncreaseSize = false;
                
            }else{
                snakeBody.pop_back();
            }
        }
        void reset(){
            snakeBody = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
            Position = {0,1};
        }
    
    };
    
    class Food{
    public:
        Vector2 Position ;
        Texture2D texture;
        
        Food(deque<Vector2> snakeBody){
            Image image = LoadImage("Images/food.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            Position = RandomPosition(snakeBody);
        }
    
    
        void DrawFood(){
            DrawTexture(texture , offSet + Position.x*cellSize , offSet + Position.y*cellSize , WHITE);
        }
        
        Vector2 GenerateRandomPosition(){
            Vector2 Position;
            float x = GetRandomValue(0,cellCount - 1);
            float y = GetRandomValue(0,cellCount - 1);
            Position = {x,y};
            return Position;
        }
    
        Vector2 RandomPosition(deque<Vector2> snakeBody){
            
            Vector2 Position = GenerateRandomPosition();
            while(ElementInDeque(Position , snakeBody)){
               Position = GenerateRandomPosition();
            }
            return Position;
        }
    
        ~Food(){
            UnloadTexture(texture);
        }
    
    
    };
    
    class Game{
     public:   
        Snake snake = Snake();
        Food food = Food(snake.snakeBody);
        bool running = true;
        int score = 0;

        Sound eatingSound;
        Sound wallSound;

        Game (){
            InitAudioDevice();
            eatingSound = LoadSound("Sounds/eat.mp3");
            wallSound = LoadSound("Sounds/wall.mp3");

        }

        ~Game(){
            UnloadSound(eatingSound);
            UnloadSound(wallSound);
            CloseAudioDevice();
        }
        void update(){
            if(running){
                snake.updatePosition();
                EatingFood();
                CollisionWithEdges();
                CollisionWithTail();
            }
        }

        void Draw(){
            snake.DrawSnake();
            food.DrawFood();
        }

        void EatingFood(){
            if(Vector2Equals(snake.snakeBody[0], food.Position)){
                food.Position = food.RandomPosition(snake.snakeBody);
                snake.IncreaseSize = true;
                ++score;
                PlaySound(eatingSound);
            }
        }
        
        void CollisionWithEdges(){
            if(snake.snakeBody[0].x == cellCount || snake.snakeBody[0].x == -1 ){
                GameOver();
            }else if(snake.snakeBody[0].y == cellCount || snake.snakeBody[0].y == -1){
                GameOver();
            }
        }
        
        void CollisionWithTail(){
            deque<Vector2> headlessSnake = snake.snakeBody;
            headlessSnake.pop_front();
            if(ElementInDeque(snake.snakeBody[0],headlessSnake)){
                GameOver();
            }
        }

        void GameOver(){
            snake.reset();
            food.Position = food.GenerateRandomPosition();
            running = false;
            score = 0;
            PlaySound(wallSound);
        }
    
    };
    
    bool ElementInDeque(Vector2 pos , deque<Vector2> snakeBody){
    for(unsigned int i = 0 ; i < snakeBody.size() ; ++i){
        if(Vector2Equals(pos,snakeBody[i])){
            return true;
        }
    }
    return false;
    }
