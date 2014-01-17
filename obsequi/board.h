// Class to handle the board state.
#ifndef BOARD_H
#define BOARD_H

#include "bitops.h"
#include "board-ops.h"
#include "hash-table.h"
#include "score-board.h"

class PositionalValues;
class Move;

// Basic board info which we keep track of.
struct BasicInfo {
  int safe;
  int real;
};

class BoardShared {
 public:
  BoardShared() {
    empty_squares = 0;
  }

  int empty_squares;
  HashKeys hashkey;
};

class Board {
 public:
  // Constructor actually creates two boards, this and the opponent.
  Board(int num_rows, int num_cols);
  ~Board() {}

  int GetNumRows() const { return num_rows_; }
  Board* GetOpponent() const { return opponent_; }

  void SetBlock(int row, int col);
  void ApplyMove(const Move& move);
  void UndoMove(const Move& move);

  bool IsGameOver(int* score) const;
  bool IsGameOverExpensive(int* score);

  void Print() const;
  void PrintInfo() const;
  void PrintBitboard() const;

  const HashKeys& GetHashKeys(const Move& move) const {
    return move_hash_keys_[move.array_index][move.mask_index];
  }

 public:
  // TODO(nathan): need to migrate these all to private.
  u32bit board[32];

  // Basic safe move/real move stats.
  BasicInfo info[32];
  BasicInfo info_totals;

  PositionalValues* position;

  BoardShared* shared;

 private:
  void ToggleMove(const Move& move);
  void UpdateSafe(int row);
  void UpdateReal(int row);

 private:
  Board(int num_rows, int num_cols, Board* opponent);
  void Initialize(int num_rows, int num_cols, Board* opponent,
                  bool is_horizontal);
  void InitInfo();

  // You can get the number of cols by looking at the opponent->num_rows.
  const int num_rows_;

  // this and the opponent should always be kept consistent.
  Board* opponent_;

  // HashKeys associated with every move.
  HashKeys move_hash_keys_[32][32];

 private:
  // Disallow copy and assign.
  Board(const Board&);
  void operator=(const Board&);
};

inline bool Board::IsGameOver(int* score) const {
  if(this->info_totals.safe > opponent_->info_totals.real){
    // current player wins.
    *score = 5000;
    return true;
  }

  if(opponent_->info_totals.safe >= this->info_totals.real){
    // opponent wins.
    *score = -5000;
    return true;
  }
  return false;
}
 
inline bool Board::IsGameOverExpensive(int* score) {
  int a = does_next_player_win(this, 0);
  if (a > 0) {
    // current player wins.
    *score = 5000;
    return true;
  }

  int b = does_who_just_moved_win(opponent_, 0);
  if(b >= 0) {
    // opponent wins.
    *score = -5000;
    return true;
  }

  *score = a - b;
  return false;
}

#endif  // BOARD_H
