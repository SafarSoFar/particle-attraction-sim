
#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>


std::random_device rd;
std::default_random_engine eng(rd());

#define SCREEN_WIDTH 920 
#define SCREEN_HEIGHT 800
#define ENTITY_AMOUNT 30

Vector2 operator+(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Vector2 operator-(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Vector2 operator*(Vector2 lhs, float rhs){
  return Vector2{lhs.x*rhs, lhs.y * rhs};
}

Vector2 GetRandomVector2(){
  std::uniform_real_distribution<float> distrX(0, SCREEN_WIDTH);
  float x = distrX(eng); 
  std::uniform_real_distribution<float> distrY(0, SCREEN_HEIGHT);
  float y = distrY(eng);
  return Vector2{(float)x,(float)y};
}

class Entity{
  public:
    Vector2 position;
    Entity(){
      this->position = GetRandomVector2();
    }
    void Move(Vector2 attractionPos){
      Vector2 distance = attractionPos-this->position;
      Vector2 dir = Vector2Normalize(distance);
      /*position = position + dir * (Vector2Length(distance)); */
      position = position + dir;
    }
  private:

};

int main(void)
{

    Entity entities[ENTITY_AMOUNT];
    for(int i = 0; i < ENTITY_AMOUNT; i++){
      entities[i] = Entity();
    }

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Gravity");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            Vector2 mousePos = GetMousePosition();
            for(int i = 0; i < ENTITY_AMOUNT; i++){
              DrawCircleV(entities[i].position, 20, BLACK);
              entities[i].Move(mousePos);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
