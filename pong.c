#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

void ballMove(Rectangle* ball, int* player){
    if(*player == 0){
        ball->x += 6.0f; 
    }
    else if(*player == 1){
        ball->x -= 6.0f;
    }
    else if(*player == 2){
        ball->x += 6.0f;
    }
}
void paddleMovement(Rectangle* paddle, int up, int down){
    if(IsKeyDown(up)){ 
        paddle->y -= 6.0f;
    }
    if(IsKeyDown(down)) {
        paddle->y += 6.0f;
    }
}
void colDect(Rectangle* ball, Rectangle* paddleLeft, Rectangle* paddleRight, int* player){
    if(CheckCollisionRecs(*ball, *paddleRight) == 1){
     
         if(*player != 1){
                *player = 1;
         }
    }
    else if(CheckCollisionRecs(*ball, *paddleLeft) == 1){
        if(*player != 2){
                *player = 2;
         }
    }
}
void initRects(Rectangle* rect, float x, float y, float width, float height){
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
}
void point(Rectangle* ball, Rectangle* paddle, int screenWidth){  
    if(ball->x > screenWidth) {
        //Left paddle wins point
        printf("Point: left\n");
        ball->x = screenWidth/2 - 20;
    }
    else if(ball->x < 0){
        //Right paddle wins point
        printf("Point: right\n");
        ball->x = screenWidth /2 - 20;
    }
}

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetWindowSize(screenWidth, screenHeight); 

    //malloc rectangle shapes and initialize them
    Rectangle* ball = (Rectangle*)malloc(sizeof(Rectangle));
    Rectangle* paddleRight = (Rectangle*)malloc(sizeof(Rectangle));
    Rectangle* paddleLeft = (Rectangle*)malloc(sizeof(Rectangle));
    
    
    initRects(ball, (float)screenWidth/2 - 20, (float)screenHeight/2 - 20, 10, 10);
    initRects(paddleRight, (float)screenWidth - 20, (float)screenHeight/2, 10, 120);
    initRects(paddleLeft, 5, (float)screenHeight/2, 10, 120);
 
    int* player  = (int*)malloc(sizeof(int));
    *player = 0;
    
    SetTargetFPS(144);
    // Main game loop
    printf("screenwidth: %d\n", screenWidth);
    while (!WindowShouldClose())
    {   
        ballMove(ball, player); 
        paddleMovement(paddleRight, KEY_I, KEY_K);
        paddleMovement(paddleLeft, KEY_W, KEY_S); 
        colDect(ball, paddleLeft, paddleRight, player);
        point(ball, paddleLeft, screenWidth);
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(*ball, WHITE);
            DrawRectangleRec(*paddleLeft, BLUE);
            DrawRectangleRec(*paddleRight, RED);
        EndDrawing();
    }

    // ***********************************************De-Initialization****************************************************
    CloseWindow();
    free(paddleLeft);
    free(paddleRight);
    free(ball);
    free(player);
    //**********************************************************************************************************************
    return 0;
}