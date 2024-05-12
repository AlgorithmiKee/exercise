#include <string.h>
#include <stdio.h>
#include "PathInMatrix.h"

static char stack[STACK_SIZE] = {'\0'};
static int Y[20][20];


static void push(char* stack){
    int top = strlen(stack);
    stack[top] = '.';
    if (top < STACK_SIZE-1){
        stack[top+1] = '\0';
    }
}

static void pop(char* stack){
    int top = strlen(stack);
    if(top > 0){
        stack[top-1] = '\0';
    }
}

static void init_cache(int x[20][20], int value){
    for(int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            x[i][j] = value;
        }
    }
}


int count_path_naiv(int X[20][20], int n, int m){
    push(stack);
    
    int result = NIL;
    
    if (X[n][m] == 0){
        result = 0;
    }else{
        if (n==0 && m==0){
            result = 1;
        }else if (n==0){
            result = count_path_naiv(X, n, m-1);
        }else if (m==0){
            result = count_path_naiv(X, n-1, m);
        }else{
            result = count_path_naiv(X, n-1, m) + count_path_naiv(X, n, m-1);
        }
    }
    
    // printf("%s Y[%d, %d] = %d \n", stack, n, m, result);
    pop(stack);
    return result;
}

int count_path_memo_wrapped(int X[20][20], int n, int m){
    push(stack);
    
    if (Y[n][m] == NIL){
        if (X[n][m] == 0){
            Y[n][m] = 0;
        }else{
            if (n==0 && m==0){
                Y[n][m] = 1;
            }else if (n==0){
                Y[n][m] = count_path_memo_wrapped(X, n, m-1);
            }else if (m==0){
                Y[n][m] = count_path_memo_wrapped(X, n-1, m);
            }else{
                Y[n][m] = count_path_memo_wrapped(X, n-1, m) + count_path_memo_wrapped(X, n, m-1);
            }
        } 
        // printf("%s Y[%d, %d] = %d \n", stack, n, m, Y[n][m]);
        
    }
    pop(stack);
    
    return Y[n][m];
}

int count_path_memo(int X[20][20], int n, int m){
    init_cache(Y, NIL);
    return count_path_memo_wrapped(X, n, m);
}

