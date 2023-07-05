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
    free(cell -> possibilities);
    free(cell);
}
void reset_cell_marker(Cell *cell){
    cell -> marker = 0;
    for(cell -> marker; cell ->marker < 9 && cell -> possibilities[cell ->marker] != 1; cell->marker++);
    cell->marker;
}
int get_cell_value(Cell *cell){
    if(cell -> numPossibilities != 1){
        return 0;
    }
    reset_cell_marker(cell);
    return cell ->marker + 1;
}
Cell *copy_cell(Cell *cell){
    Cell *newCell = malloc(sizeof(struct cell));
    newCell -> numPossibilities = cell -> numPossibilities;
    newCell -> marker = cell -> marker;

    newCell -> possibilities = calloc(9,sizeof(int));

    for(int i = 0; i < 9; i++){
        newCell -> possibilities[i] = cell -> possibilities[i];
    }

    return newCell;
}
Board *copy_board(Board *board){
    Board *newBoard = malloc(sizeof(struct board));
    newBoard -> cellMatrix = calloc(9,sizeof(struct cell**));
    for(int i = 0; i < 9; i++){
        newBoard -> cellMatrix[i] = calloc(9,sizeof(struct cell*));
        for(int j = 0; j < 9; j++){
            newBoard -> cellMatrix[i][j] = copy_board(board -> cellMatrix[i][j]);
        }
    }
    return newBoard;
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
    Board *newBoard = copy_board(board);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board ->cellMatrix[i][j] == sudokuCell){
                newBoard -> cellMatrix[i][j] ->marker = value -1;
                newBoard -> cellMatrix[i][j] ->numPossibilities = 1;

                memset(newBoard ->cellMatrix[i][j] -> possibilities, 0, sizeof(int)*9);

                newBoard -> cellMatrix[i][j] -> possibilities[value -1] = 1;
            }
        }
    }
}

bool board_is_valid(Board *board){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board -> cellMatrix[i][j] ->numPossibilities == 0)
                return false;
            
        }
    }
}

bool board_is_filled(Board *board){
    for(int i = 0; i <9; i++){
        for (int j = 0; j < 9; j++)
        {
            if(board -> cellMatrix[i][j] ->numPossibilities != 1){
                return false;
            }
        } 
    }
    return true;
}

Cell *get_cell_min_possibilities(Board *board){
    Cell *minCell = board -> cellMatrix[0][0];
    for(int i = 0; i <9; i++){
        for (int j = 0; j < 9; j++)
        {
            if(board ->cellMatrix[i][j] -> numPossibilities < minCell -> numPossibilities){
                minCell = board -> cellMatrix[i][j];
            }
        } 
    }
    return minCell;
}

int get_possibility(Cell *cell){
    if(cell -> marker > 8){
        return 0;
    }
    for(cell -> marker; cell -> marker < 9 && cell -> possibilities[cell->marker] != 1; cell->marker++);
    int value = cell ->marker < 9 ? cell->marker: 0;
    return value;
}

void print_board(Board *board){
    for (int i = 0; i < 9; i++)
    {
        if(i != 0 && i%3 == 0){
            printf("----------------------\n");
        }
        for(int j = 0; j < 9; j++){
            if(j != 0 && j%3 == 0){
                printf("| ");
            }
            int value = get_cell_value(board -> cellMatrix[i][j]);
            if(value == 0){
                printf("  ");
            }
            else{
                printf("%d ", value);
            }
        }
        printf("\n");
    } 
}

void destroy_board(Board *board){
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            destroy_cell(board->cellMatrix[i][j]);
        } 
        free(board->cellMatrix[i]);
    }
    free(board ->cellMatrix);
    free(board);
}
