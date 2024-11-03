#include <stdlib.h>

#include "../libs/c_structs.h"
#include "../libs/raylib.h"

#include "utils/utils.h"
#include "models/models.h"
#include "game.h"

void play_gui() {
  Player* p1 = player_new("Player 1", 'X');
  Player* p2 = player_new("Player 2", 'O');
  Grid* board = board_new(3, 3);
  
  int round_count = 1;
  int move_count = 0;
  int n_to_win = 3;
  bool end_game = false;

  // Initialize the window
  const uint screen_width = 600;
  const uint screen_height = 600;
  InitWindow(screen_width, screen_height, "Tic Tac Toe Board");

  // Set the line thickness for the grid
  const uint line_thickness = 10;
  const uint cell_size = screen_width / 3;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(BLACK);

      // Draw vertical lines
      DrawRectangle(cell_size - line_thickness / 2, 0, line_thickness, screen_height, WHITE);
      DrawRectangle(2 * cell_size - line_thickness / 2, 0, line_thickness, screen_height, WHITE);

      // Draw horizontal lines
      DrawRectangle(0, cell_size - line_thickness / 2, screen_width, line_thickness, WHITE);
      DrawRectangle(0, 2 * cell_size - line_thickness / 2, screen_width, line_thickness, WHITE);

      EndDrawing();
  }


  CloseWindow();

  player_free(&p1);
  player_free(&p2);
  grid_free(&board, (FreeFn) square_free);
}
