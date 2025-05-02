#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


//function prototpes 
void * rowsCheckHandler(void * arg);
void * colsCheckHandler(void * arg);
void * squareCheckHandler(void * arg);


// sodoku input 
int sudoku[9][9] = 
{{6,2,4,5,3,9,1,8,7},
{5,1,9,7,2,8,6,3,4},
{8,3,7,6,1,4,2,9,5},
{1,4,3,8,6,5,7,2,9},
{9,5,8,2,4,7,3,6,1},
{7,6,2,3,9,1,4,5,8},
{3,7,1,9,5,6,8,4,2},
{4,9,6,1,8,2,5,7,3},
{2,8,5,4,7,3,9,1,6}};

// structure to save start points for 3*3 squares 

typedef struct 
{
    int row;
    int col;
} startPoint;





int main() {

    //pointer to the 9 3*3 squares' start points

    startPoint *square1 = (startPoint *) malloc(sizeof(startPoint));
    square1->row = 0;
    square1->col= 0;

    startPoint *square2 = (startPoint *) malloc(sizeof(startPoint));
    square2->row = 0;
    square2->col= 3;

    startPoint *square3 = (startPoint *) malloc(sizeof(startPoint));
    square3->row = 0;
    square3->col = 6; 

    startPoint *square4 = (startPoint *) malloc(sizeof(startPoint));
    square4->row = 3;
    square4->col= 0;

    startPoint *square5 = (startPoint *) malloc(sizeof(startPoint));
    square5->row = 3;
    square5->col= 3;

    startPoint *square6 = (startPoint *) malloc(sizeof(startPoint));
    square6->row = 3;
    square6->col= 6;

    startPoint *square7 = (startPoint *) malloc(sizeof(startPoint));
    square7->row = 6;
    square7->col= 0;

    startPoint *square8 = (startPoint *) malloc(sizeof(startPoint));
    square8->row = 6;
    square8->col= 3;

    startPoint *square9 = (startPoint *) malloc(sizeof(startPoint));
    square9->row = 6;
    square9->col= 6;



    pthread_t row_thread, col_thread , s1_thread , s2_thread , s3_thread , s4_thread , s5_thread , s6_thread , s7_thread , s8_thread , s9_thread;
    
    // declaring output variables for the threads 
    void * isValid[11];

    // creating threads 

    pthread_create(&row_thread , NULL , rowsCheckHandler , NULL);
    pthread_create(&col_thread , NULL , colsCheckHandler , NULL);

 
    pthread_create(&s1_thread , NULL, squareCheckHandler , (void *)square1);
    pthread_create(&s2_thread , NULL, squareCheckHandler , (void *)square2);
    pthread_create(&s3_thread , NULL, squareCheckHandler , (void *)square3);
    pthread_create(&s4_thread , NULL, squareCheckHandler , (void *)square4);
    pthread_create(&s5_thread , NULL, squareCheckHandler , (void *)square5);
    pthread_create(&s6_thread , NULL, squareCheckHandler , (void *)square6);
    pthread_create(&s7_thread , NULL, squareCheckHandler , (void *)square7);
    pthread_create(&s8_thread , NULL, squareCheckHandler , (void *)square8);
    pthread_create(&s9_thread , NULL, squareCheckHandler , (void *)square9);
    
    // waiting for all threads to finish
    pthread_join(row_thread , &isValid[0]);
    pthread_join(col_thread , &isValid[1]);
    pthread_join(s1_thread , &isValid[2]);
    pthread_join(s2_thread , &isValid[3]);
    pthread_join(s3_thread , &isValid[4]);
    pthread_join(s4_thread , &isValid[5]);
    pthread_join(s5_thread , &isValid[6]);
    pthread_join(s6_thread , &isValid[7]);
    pthread_join(s7_thread , &isValid[8]);
    pthread_join(s8_thread , &isValid[9]);
    pthread_join(s9_thread , &isValid[10]);


    // checking if each condition is met

    int isSudokuCorrect = 1;
    for(int i=0; i < 11;++i) isSudokuCorrect *= (int)isValid[i];
    
    // printing the output

    if(isSudokuCorrect) printf("\033[32mThis sudoku is correct!\033[39m");
    else printf("\033[31mThis sudoku is not correct!\033[39m");


}


// function for the thread to check if the rows of the sodoku are valid

void * rowsCheckHandler(void * arg) {
    for(int i=0; i < 9 ;++i) {
        int row_values[10] = {0};
        for(int j=0; j < 9 ;++j) {
            if(sudoku[i][j] <= 1 && sudoku[i][j] >= 10) return (void *) 0;
            
            if(row_values[sudoku[i][j]]) return (void *) 0;
            
            else row_values[sudoku[i][j]] = 1;
        }
    }

    return (void *) 1;
} 

// function for the thread to check if the cols of the sodoku are valid

void * colsCheckHandler(void * arg) {
    for(int j=0; j < 9 ;++j) {
        int col_values[10] = {0};
        for(int i=0; i < 9 ;++i) {
            if(sudoku[i][j] <= 1 && sudoku[i][j] >= 10) return (void *) 0;
            
            if(col_values[sudoku[i][j]]) return (void *) 0;
            
            else col_values[sudoku[i][j]] = 1;
        }
    }

    return (void *) 1;
} 


// function for the thread to check if the 3*3 squares of the sodoku are valid

void * squareCheckHandler(void * arg) {
    startPoint * squareStartPoints = (startPoint *)arg;
    int square_values[10] = {0};
    for(int i= squareStartPoints->row; i < squareStartPoints->row + 3;++i) {
        for(int j = squareStartPoints->col; j < squareStartPoints->col + 3;++j) {
            if(sudoku[i][j] <= 1 && sudoku[i][j] >= 10) return (void *) 0;
            
            if(square_values[sudoku[i][j]]) return (void *) 0;
            
            else square_values[sudoku[i][j]] = 1;
        }
    }
    return (void *) 1;
}