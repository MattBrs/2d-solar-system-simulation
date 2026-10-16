#include "Color.hpp"
#include "Window.hpp"
#include <iostream>
#include <raylib-cpp.hpp>
#include <raylib.h>

int main(int argc, char **argv) {
  int screenWidth = 800;
  int screenHeight = 600;

  raylib::Window window(screenWidth, screenHeight, "Little solar system");
  SetTargetFPS(60);

  while (!window.ShouldClose()) {
    BeginDrawing();

    window.ClearBackground(raylib::Color::DarkBlue());

    raylib::DrawText("Hi! ;)", 370, 290, 24, raylib::Color::Purple());

    EndDrawing();
  }

  std::cout << "hi! ;)" << "\n" << std::flush;

  return 0;
}
