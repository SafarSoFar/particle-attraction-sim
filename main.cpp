
#include "raylib.h"
#include <iostream>
#include "raymath.h"
#include <random>


std::random_device rd;
std::default_random_engine eng(rd());

#define SCREEN_WIDTH 920 
#define SCREEN_HEIGHT 800
#define ENTITY_AMOUNT 8000
#define ENTITY_RADIUS 7
#define ENTITY_SPEED 100.0f

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

class Entity;

Vector2 g_mousePos;
bool g_isHoldingLMB;

std::vector<Entity> g_entities(ENTITY_AMOUNT);

class Entity{
  public:
    Vector2 position;
    Vector2 velocity;
    Color color = BLACK;
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

        //blue gradient value mapping 
        float c = ((distance)/1500) * 255;
        unsigned char b = 255-(int)c;
        color = Color{0,0,b,255};

        velocity = (dir / distance) * ENTITY_SPEED;
        position = position + velocity;
      }
    }

  private:
};

int main(void)
{

    for(int i = 0; i < ENTITY_AMOUNT; i++){
      g_entities[i] = Entity();
    }


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle attraction");

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
            DrawCircleV(g_entities[i].position, ENTITY_RADIUS, g_entities[i].color);
            g_entities[i].Move();
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
