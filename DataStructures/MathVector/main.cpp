#include <iostream>
#include <string>
#include "Vector2d.hpp"

const int WIDTH = 400;
const int HEIGHT = 400;
class Object{
public:
  Vector2D<float> pos;
  Vector2D<float> velocity;
};

int main() {
  // Vector2D<float> pos(0, 0);
  // pos.print();
  // float five = 5.0f;
  // pos = pos  + VECTOR2D_DOWN * five;
  // pos.print();
  // VECTOR2D_DOWN.print();
  Vector2D<float> gravity(0, 0.4);
  Vector2D<float> jump_height = VECTOR2D_UP * 5;
  Object player;
  player.pos.print();
  player.velocity = Vector2D<float>(10, 0);

  for(int i = 0; i < 600; i++) {
    player.velocity.Add(gravity);
    if(i > 300 && i < 350) {
      player.velocity.Add(jump_height);
    }
    player.pos.Add(player.velocity);
    {// limiting the pos to within the screen bounds
      player.pos.y = std::min(player.pos.y, (float)HEIGHT);
      player.pos.y = std::max(player.pos.y, -(float)HEIGHT);
      player.pos.x = std::min(player.pos.x, (float)WIDTH);
      player.pos.x = std::max(player.pos.x, -(float)WIDTH);
    }
    player.pos.print();
  }

  return 0;
}
