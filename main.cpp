/*
TODO:
  - create a new matrix where we will put the next iteration in,
  then we just pass that in as the next matrix to work on.
  - continue with debugging check neighbors function.
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

#define MAX_ROWS 3
#define MAX_COLS 3
#define MAX_CELLS 5

void displayUniverse(int, int, int[][MAX_COLS]);
void populateUniverse(int, int, int, int[][MAX_COLS]);
void simulatesUniverse(int, int, int, int[][MAX_COLS]);
void checkNeighbors(int, int, int[][MAX_COLS]);

int main(){
  int theUniverse[MAX_ROWS][MAX_COLS] = {0};
  populateUniverse(MAX_ROWS, MAX_COLS, MAX_CELLS, theUniverse);
  simulatesUniverse(10, MAX_ROWS, MAX_COLS, theUniverse);
  

}

void displayUniverse(int numRows, int numCols, int theUni[][MAX_COLS]){
  /*
   Outputs all the values in our universe. Either 0 (dead) or 1 (alive).
  */
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      cout << theUni[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}


void populateUniverse(int maxRows, int maxCols, int maxCells, int theUni[][MAX_COLS]){
  /*
  Picks out a random cell in the universe and populates it (replaces the value with a 1).
  */ 
  srand(time(0));
  int liveCells = 0;
  while(liveCells < maxCells){
    int randomRow = rand() % maxRows;
    int randomCol = rand() % maxCols;

    if(theUni[randomRow][randomCol] != 1){
      theUni[randomRow][randomCol] = 1;
      liveCells++;
    }
  }
}

void simulatesUniverse(int numIterations, int numRows, int numCols, int theUni[][MAX_COLS]){
  for(int i = 0; i < numIterations; i++){
    // system("clear");
    cout << "Iteration " << i + 1 << endl;
    displayUniverse(numRows, numCols, theUni);
    // this_thread::sleep_for(1s);
    checkNeighbors(numRows, numCols, theUni);
  }
}

void checkNeighbors(int numRows, int numCols, int theUni[][MAX_COLS]){
  int liveCells = 0;
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      // Checks corners.
      if(i == 0 && j == 0){
        liveCells = theUni[i + 1][j] + theUni[i][j + 1] + theUni[i + 1][j + 1];
      }
      else if(i == 0 && j == numCols - 1){
          liveCells = theUni[i + 1][j] + theUni[i + 1][j - 1] + theUni[i][j - 1];
      }
      else if(i == numRows - 1 && j == 0){
          liveCells = theUni[i][j + 1] + theUni[i - 1][j] + theUni[i - 1][j + 1];
      }
        else if(i == numRows - 1 && j == numCols - 1){
          liveCells = theUni[i - 1][j] + theUni[i][j - 1] + theUni[i - 1][j - 1];
      }

      // Checks edges.
      else if(i == 0 && (j != 0 && j != numCols - 1)){
        liveCells = theUni[i - 1][j] + theUni[i - 1][j + 1] + theUni[i][j + 1] + theUni[i +  1][j + 1] + theUni[i + 1][j];
      }
      else if(i == numRows - 1 && (j != 0 && j != numCols - 1)){
          liveCells = theUni[i - 1][j] + theUni[i - 1][j + 1] + theUni[i][j + 1] + theUni[i +  1][j + 1] + theUni[i + 1][j];
      }
        else if((i != 0 && i != numRows - 1) && j == 0){
        liveCells = theUni[i][j + 1] + theUni[i + 1][j] + theUni[i + 1][j + 1] + theUni[i + 1][j - 1] + theUni[i][j - 1];
      }
        else if((i != 0 && i != numRows - 1) && j == numCols - 1){
          liveCells = theUni[i][j + 1] + theUni[i - 1][j] + theUni[i - 1][j + 1] + theUni[i - 1][j - 1] + theUni[i][j - 1];
      }
      
      // Checks everywhere else.
      else{
        liveCells = theUni[i - 1][j + 1] + theUni[i][j + 1] + theUni[i + 1][j + 1] + theUni[i - 1][j] + theUni[i + 1][j] + theUni[i - 1][j - 1] + theUni[i][j - 1] + theUni[i + 1][j - 1];
      }

      // The Result
      if(theUni[i][j] == 1 && (liveCells < 2 || liveCells > 3)){
        theUni[i][j] = 0;
      }
      else if(theUni[i][j] == 1 && (liveCells == 2 || liveCells == 3)){
        theUni[i][j] = 1;
      }
      else if(theUni[i][j] == 0 && liveCells == 3){
        theUni[i][j] = 1;
      }
    }
  }
}
