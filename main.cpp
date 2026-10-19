#include "Color.hpp"
#include <flecs.h>
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>

struct Position {
  float x{};
  float y{};
};

struct Planet {
  float radius{};
  raylib::Color color{};
};

int main(int argc, char **argv) {
  flecs::world world{};
  const int screenWidth = 800;
  const int screenHeight = 600;

  world.entity("RedPlanet")
      .set<Position>({screenWidth / 2.f, screenHeight / 2.f})
      .set<Planet>({.radius = 30.f, .color = raylib::Color::Red()});
  world.entity("GrayPlanet")
      .set<Position>({screenWidth / 3.f, screenHeight / 2.f})
      .set<Planet>({.radius = 15.f, .color = raylib::Color::Gray()});

  raylib::Window window(screenWidth, screenHeight, "Little solar system");
  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground(raylib::Color::DarkBlue());

    // raylib::DrawText("Hi! ;)", 370, 290, 24, raylib::Color::Purple());

    world.query<Position, Planet>().each(
        [](const Position &pos, const Planet &planet) {
          DrawCircle(pos.x, pos.y, planet.radius, planet.color);
        });

    EndDrawing();
  }

  std::cout << "hi! ;)" << "\n" << std::flush;

  return 0;
}
