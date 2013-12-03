 
#ifndef GLOBALS_H
#define GLOBALS_H

#include "utils.h"

#include "interface.h"

#include "structs.h"
#include "consts.h"


//########################################################
// Function prototypes.
//########################################################

//========================================================
// Generate a list of moves that 'player'
//   can make in the given position. (excluding safe moves).
//
// The moves are places in the movelist array.
// Returns the number of moves that were placed in movelist.
//========================================================
int move_generator(int rows, u32bit board[32], Move movelist[MAXMOVES]);
int move_generator_stage1(int rows, u32bit board[32], Move movelist[MAXMOVES]);
int move_generator_stage2(int rows, u32bit board[32],
                          int start, Move movelist[MAXMOVES]);

// Need to define this in a better place...
s32bit does_next_player_win(s32bit next_player, s32bit print);
s32bit does_who_just_moved_win(s32bit who_just_moved, s32bit print);

//=================================================================
// Move ordering uses a simple evaluation function as well as
//   a value associated with each position.
// The first two function set these values in a dynamic way.
// The 'set_position_values' function does it statically.
//=================================================================
#ifdef DYNAMIC_POSITION_VALUES
void    init_move_value     ();
s32bit  set_move_value      (Move movelist, s32bit player);
void    unset_move_value    (Move movelist, s32bit player);
#else
void    set_position_values ();
#endif

//========================================================
// Toggle a move, if a move hasn't been played then play it, if
//   it has then undo it.
//========================================================
void    toggle_move    (Move move, s32bit player);

//========================================================
// Give score of move relative to current position.
//========================================================
//s32bit  score_move(Move move, s32bit player);
void
score_and_get_first(Move movelist[MAXMOVES], s32bit num_moves,
                    s32bit player, Move first);

//========================================================
// Use the value of movelist[i].info to sort the moves in
//   descending order.
//========================================================
void    sort_moves(Move movelist[MAXMOVES], s32bit start, s32bit num_moves);


void
update_safe(s32bit player, s32bit row);

void
update_real(s32bit player, s32bit row);


void init_less_static_tables();


void init_static_tables();



// make the bitboard consistent with the info past into this function.
void    init__board(s32bit num_rows, s32bit num_cols, s32bit board[30][30]);

void    initialize_tables();



//########################################################
// Functions for interacting with the hashtable.
//========================================================
// Store the current search value into the hashtable if there
//   is a position available.
//========================================================
void    hashstore      (s32bit value, s32bit alpha, s32bit beta,
                        u32bit nodes, s32bit depth_remaining,
                        Move best, s32bit player);


//========================================================
// Check the hashtable to see if we have already seen the current
//   position before.
//========================================================
s32bit  hashlookup     (s32bit *value, s32bit *alpha, s32bit *beta,
                        s32bit depth_remaining,
                        Move *force_first, s32bit player);


//########################################################
// Functions for information display or sanity checks.
//========================================================
// Functions which varify pieces of information.
//========================================================
void    check_board();
void    check_board_info();

void    check_hash_code_sanity();


//========================================================
// Functions which print various pieces of information in a
//   readable format.
//========================================================
void    print_board(s32bit player);
void    print_board_info();
void    print_bitboard(s32bit player);
void    print_hashkey(Hash_Key key);
void    print_u64bit(u64bit val);
void    print_hashentry(s32bit index);



//########################################################
// Global variables.
//########################################################

extern u64bit       g_num_nodes;


// two bitboard arrays [0] is horizontals, [1] is verticals.
extern u32bit       g_board[2][32];

// number of rows and cols in the board.
// [0] is the num of rows, [1] is the num of cols.
extern s32bit       g_board_size[2];

// keep track of simple info such as real and safe moves.
extern Basic_Info   g_info[2][32];
extern Basic_Info   g_info_totals[2];
extern s32bit       g_empty_squares;

// zobrist value for each position on the board.
extern s32bit       g_zobrist[32][32];

// Transposition table.
extern Hash_Entry  *g_trans_table;

// Current boards hash key and code (flipped in various ways).
extern Hash_Key     g_norm_hashkey;
extern Hash_Key     g_flipV_hashkey;
extern Hash_Key     g_flipH_hashkey;
extern Hash_Key     g_flipVH_hashkey;

extern s32bit       g_first_move[2][32][32];

extern s32bit       g_move_number[128];



//########################################################
// Tables of precalculated information.
//
// Calling initialize_board should initialize the information in
//   all these tables.
//########################################################


//========================================================
// Declare the table we use for updating our hashkey after each move.
//========================================================
extern KeyInfo      g_keyinfo[2][32][32];

#endif //ifndef GLOBALS_H
