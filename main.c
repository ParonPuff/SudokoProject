#include <stdio.h>
#include "board.h"

int main(int argc, char *argv){
    if(argc != 2){
        return 1;
    }
    
    FILE *fp = fopen(argv[1],"r");

    if(fp = NULL){
        return 1;
    }

    return 0;
}