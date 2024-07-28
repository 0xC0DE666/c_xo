#include <stdlib.h>
#include <stdio.h>

#include "../utils/io.h"
#include "board.h"

// ####################
// BOARD
// ####################

// POSITION

Position* position_new(int row, int column) {
  Position* position = malloc(sizeof(Position));

  if (position == NULL) {
    return NULL;
  }

  position->row = row;
  position->column = column;

  return position;
}

void position_free(Position** position) {
  free(*position);
  *position = NULL;
}

char* position_to_string(Position* position) {
  char* str = string_new(10);

  if (str == NULL) {
    return NULL;
  }

  sprintf(
    str,
    "(%d, %d)",
    position->row,
    position->column
  );

  return str;
}


// SQUARE

Square* square_new(Position* position, char mark) {
  Square* square = malloc(sizeof(Square));

  if (square == NULL) {
    return NULL;
  }

  square->position = position;
  square->mark = mark;

  return square;
}

void square_free(Square** square) {
  position_free(&(*square)->position);
  free(*square);
  *square = NULL;
}

char* square_to_string(Square* square) {
  char* str = string_new(20);

  if (str == NULL) {
    return NULL;
  }

  sprintf(
    str,
    "(%d, %d, %c)",
    square->position->row,
    square->position->column,
    square->mark
  );

  return str;
}


// BOARD

Board* board_new() {
  Board* board = malloc(sizeof(Board));

  if (board == NULL) {
    return NULL;
  }

  board->marks = 0;
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      board->squares[r][c] = square_new(position_new(r, c), BLANK);
    }
  }

  return board;
}

void board_free(Board** board) {
  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      Position** p = &((*board)->squares[r][c]->position);
      position_free(p);
      Square** s = &((*board)->squares[r][c]);
      square_free(s);
    }
  }
  free(*board);
  (*board) = NULL;
}

// char* board_to_string(Board* board) {
//   char* str = string_new(100);
// 
//   for (int r = 0; r < 3; ++r) {
//     for (int c = 0; c < 3; ++c) {
//       board->squares[r][c] = square_new(position_new(r, c), BLANK);
//     }
//   }
// 
//   sprintf(
//     str,
//     "%s (%c) %d",
//     board->name,
//     board->symbol,
//     board->score
//   ); 
// 
//   return str;
// }

void board_mark(Board* board, Position* position, char mark) {
  int row = position->row;
  int col = position->column;
  board->squares[row][col]->mark = mark;
}

char board_get_mark(Board* board, Position* position) {
  int row = position->row;
  int col = position->column;
  return board->squares[row][col]->mark;
}

bool check_line(char line[], int length) {
  for (int i = 0; i < length - 1; ++i) {
    char a = line[i];
    char b = line[i + 1];

    if (a == BLANK || b == BLANK || a != b) {
      return false;
    }
  }

  return true;
}

// bool check_win(Board* board, int x_in_a_row) {
//   let dimension = board.dimension;
//   // check rows
//   for r in 0..n {
//       let mut row: Vec<char> = vec![];
//       let mut col: Vec<char> = vec![];
//       for c in 0..dimension {
//           let mark = board.get_mark(&Position::new(r, c));
//           row.push(mark);
// 
//           let mark = board.get_mark(&Position::new(c, r));
//           col.push(mark);
//       }
//       if check_line(&row) {
//           println!("win row {}", r);
//           return true;
//       } else if check_line(&col) {
//           println!("win col {}", r);
//           return true;
//       }
//   }
//   println!("\n\n");
// 
//   // check diags
//   let mut left_row = 0;
//   let mut left_col = 0;
// 
//   let mut right_row = 0;
//   let mut right_col = 2;
// 
//   let mut left_line: Vec<char> = vec![];
//   let mut right_line: Vec<char> = vec![];
// 
//   for _i in 0..n {
//       let left_mark = board.get_mark(&Position {
//           row: left_row,
//           col: left_col,
//       });
//       let right_mark = board.get_mark(&Position {
//           row: right_row,
//           col: right_col,
//       });
// 
//       left_line.push(left_mark);
//       right_line.push(right_mark);
// 
//       left_row += 1;
//       left_col += 1;
// 
//       right_row += 1;
//       if right_col > 0 {
//           right_col -= 1;
//       }
//   }
//   if check_line(&left_line) {
//       println!("win diag left down");
//       return true;
//   } else if check_line(&right_line) {
//       println!("win diag right down");
//       return true;
//   }
//   return false;
// }
