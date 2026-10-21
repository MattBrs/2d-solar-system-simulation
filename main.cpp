#include "Color.hpp"
#include <cstddef>
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
  Vector2 velocity{};
};

int main(int argc, char **argv) {
  flecs::world world{};
  const int screenWidth = 800;
  const int screenHeight = 600;

  world.entity("RedPlanet")
      .set<Position>({screenWidth / 2.f, screenHeight / 2.f})
      .set<Planet>({.radius = 30.f,
                    .color = raylib::Color::Red(),
                    .velocity = Vector2{.x = 150.f, .y = 0.f}});
  world.entity("GrayPlanet")
      .set<Position>({screenWidth / 3.f, screenHeight / 2.f})
      .set<Planet>({.radius = 15.f,
                    .color = raylib::Color::Gray(),
                    .velocity = Vector2{.x = 0.f, .y = 100.f}});

  world.system<Position, const Planet>().each(
      [](flecs::iter &it, size_t index, Position &pos, const Planet &planet) {
        // for each planet, execute this function
        pos.x += planet.velocity.x * it.delta_time();
        pos.y += planet.velocity.y * it.delta_time();
      });

  raylib::Window window(screenWidth, screenHeight, "Little solar system");
  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    world.progress(GetFrameTime());

    BeginDrawing();

    window.ClearBackground(raylib::Color::DarkBlue());

    world.query<Position, Planet>().each(
        [](const Position &pos, const Planet &planet) {
          DrawCircle(pos.x, pos.y, planet.radius, planet.color);
        });

    EndDrawing();
  }

  std::cout << "hi! ;)" << "\n" << std::flush;

  return 0;
}
