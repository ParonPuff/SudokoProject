#include <stdio.h>
#include <stdbool.h>
#include "board.h"


Board *solve_board(Board *board);

int main(int argc, char *argv[]){
    if(argc != 2){
        return 1;
    }
    
    FILE *fp = fopen(argv[1],"r");

    if(fp == NULL){
        return 1;
    }

    Board *board = make_board_from_file(fp);
    fclose(fp);
    print_board(board);
    if(!board_is_valid(board)){
        printf("The given board is not valid\n");
        destroy_board(board);
        return 1;
    }

    Board *solvedBoard = solve_board(board);

    if(solvedBoard == NULL){
        printf("The given board is not valid\n");
    }
    else{
        printf("The board was solved!!! :)\n\n");
        print_board(solvedBoard);
    }

    destroy_board(board);
    destroy_board(solvedBoard);
    return 0;
}

Board *solve_board(Board *board){
    if(board_is_filled(board) && board_is_valid(board))
        return board;

    Cell *minCell = get_cell_min_possibilities(board);

    int consideredValue = get_possibility(minCell);

    do{
        Board *consideredBoard = set_cell(board,minCell,consideredValue);

        if(board_is_valid(consideredBoard)){
            Board *result = solve_board(consideredBoard);
            if(result != NULL){
                destroy_board(consideredBoard);
                return result;
            }
        }

        destroy_board(consideredBoard);
        consideredValue = get_possibility(minCell);
    }while (consideredValue != 0); 

    return NULL;
}