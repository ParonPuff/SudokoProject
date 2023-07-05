#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdbool.h>

typedef struct board Board;
typedef struct cell Cell;

/**
 * @brief given a file this function will create the board described in the file
 * 
 * @param board a file containing a description for a file
 * @return Board* a pointer to board object
 */
Board *make_board_from_file(FILE *board);

/**
 * @brief given a board, a cell and a value this function 
 * will set the given cell to the given value and return a copy of the board with the given state
 
 * @param board
 * @param sudokuCell 
 * @param value 
 * @return Board* 
 */
Board *set_cell(Board *board, Cell *sudokuCell, int value);

/**
 * @brief given a board this function will return true if the given board has a valid state
 * 
 * @param board 
 * @return true 
 * @return false 
 */
bool board_is_valid(Board *board);

/**
 * @brief given a board this function will return true if the given board has any remaining possible changes
 * 
 * @param board 
 * @return true 
 * @return false 
 */
bool board_is_filled(Board *board);

/**
 * @brief Get the cell with the least possibilities on the board
 * 
 * @param board 
 * @return Cell* 
 */
Cell *get_cell_min_possibilities(Board *board);

/**
 * @brief given a cell this function will return one of the possible values of that cell. If this function
 * is called again the function will return a new possibiliy
 * 
 * @param cell 
 * @return int 
 */
int get_possibility(Cell *cell);



#endif