#include "board.h"
#include <stdlib.h>
//***************Objects**********************************
struct board{
    Cell ***cellMatrix;
};
struct cell{
    int numPossibilities;
    int *possibilities;
    int marker;
};
//**************Internal help functions******************
Cell *create_cell(){
    Cell *cell = malloc(sizeof(struct cell));

    cell -> numPossibilities = 9;
    cell -> possibilities = calloc(9,sizeof(int));

    memset(cell ->possibilities, 1, sizeof(int));

    cell -> marker = 0;
    return cell;
}
Cell *make_cell(int value){
    Cell *emptyCell = create_cell();

    memset(emptyCell -> possibilities, 0, sizeof(int)*9);

    emptyCell -> possibilities[value-1] = 1;
    emptyCell -> numPossibilities = 1;
    emptyCell -> marker = value -1;

    return emptyCell;
}
void destroy_cell(Cell *cell){

}
//**************Public interface*************************
Board *make_board_from_file(FILE *boardFile){
    Board *board = malloc(sizeof(struct board));
    board -> cellMatrix = calloc(9,sizeof(struct cell**));

    for(int i = 0; i < 9; i++){
        board -> cellMatrix[i] = calloc(9, sizeof(struct cell*));
        for(int j = 0; j < 9; j++){
            int readValue;

            if(fscanf(boardFile,"%d",&readValue) != 1){
                for(int x = 0; x<i+1; x++){
                    for(int y = 0; y < x == i ? j:9; y++){
                        destroy_cell(board ->cellMatrix[x][y]);
                    }
                }
                for(int x = 0; x < 9; x++){
                    free(board -> cellMatrix[x]);
                }
                free(board -> cellMatrix);
                free(board);

                fprintf(stderr, "Was unable to read sudoku board from file");

                return NULL;
            }

            board ->cellMatrix[i][j] = readValue == 0 ? create_cell():make_cell(readValue);
        }
    }

    return board;
}

Board *set_cell(Board *board, Cell *sudokuCell, int value){

}

bool board_is_valid(Board *board){

}

bool board_is_filled(Board *board){

}

Cell *get_cell_min_possibilities(Board *board){

}

int get_possibility(Cell *cell){

}

void print_board(Board *board){

}

void destroy_board(Board *board){

}
