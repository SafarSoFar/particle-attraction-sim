
#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>


std::random_device rd;
std::default_random_engine eng(rd());

#define SCREEN_WIDTH 920 
#define SCREEN_HEIGHT 800
#define ENTITY_AMOUNT 20000
#define ENTITY_RADIUS 3
#define ENTITY_SPEED 150.0f


Vector2 g_mousePos;
bool g_isHoldingLMB;

Vector2 operator+(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x+rhs.x, lhs.y+rhs.y};
}

Vector2 operator-(Vector2 lhs, Vector2 rhs){
  return Vector2{lhs.x-rhs.x, lhs.y-rhs.y};
}

Vector2 operator*(Vector2 lhs, float rhs){
  return Vector2{lhs.x*rhs, lhs.y * rhs};
}

Vector2 operator/(Vector2 lhs, float rhs){
  return Vector2{lhs.x/rhs, lhs.y/rhs};
}

Vector2 GetRandomVector2(){
  std::uniform_real_distribution<float> distrX(0, SCREEN_WIDTH-ENTITY_RADIUS);
  float x = distrX(eng); 
  std::uniform_real_distribution<float> distrY(0, SCREEN_HEIGHT-ENTITY_RADIUS);
  float y = distrY(eng);
  return Vector2{(float)x,(float)y};
}

class Entity{
  public:
    Vector2 position;
    Entity(){
      this->position = GetRandomVector2();
    }
    void Move(){
      Vector2 distanceVec = g_mousePos-this->position;
      Vector2 dir = Vector2Normalize(distanceVec);
      float distance = Vector2Length(distanceVec);

      if(g_isHoldingLMB){
        distance = -distance;
      }

      if(abs(distance) > 2.0f){
        Vector2 velocity;
        velocity = (dir / distance) * ENTITY_SPEED;
        position = position + velocity;
      }
      
    }
  private:
    /*Vector2 m_velocity;*/
};

int main(void)
{

    Entity entities[ENTITY_AMOUNT];
    for(int i = 0; i < ENTITY_AMOUNT; i++){
      entities[i] = Entity();
    }


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravity");

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

            g_mousePos = GetMousePosition();
            g_isHoldingLMB = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

            for(int i = 0; i < ENTITY_AMOUNT; i++){
              DrawCircleV(entities[i].position, ENTITY_RADIUS, BLACK);
              entities[i].Move();
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
