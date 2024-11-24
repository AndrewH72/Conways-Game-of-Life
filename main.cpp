#include <iostream>
#include <random>
using namespace std;

#define MAX_ROWS 5
#define MAX_COLS 5
#define MAX_CELLS 5

void displayUniverse(int, int, int[][MAX_COLS]);
void populateUniverse(int, int[][MAX_COLS]);
void simulatesUniverse(int, int, int[][MAX_COLS]);
bool checkNeighbors(int);

int main(){
  int theUniverse[MAX_ROWS][MAX_COLS] = {0};

  populateUniverse(MAX_CELLS, theUniverse);

  displayUniverse(MAX_ROWS, MAX_COLS, theUniverse);

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
}


void populateUniverse(int maxCells, int theUni[][MAX_COLS]){
  /*
  Picks out a random cell in the universe and populates it (replaces the value with a 1).
  */ 
  srand(time(0));
  int liveCells = 0;
  while(liveCells < maxCells){
    int randomRow = rand() % 5;
    int randomCol = rand() % 5;

    if(theUni[randomRow][randomCol] != 1){
      theUni[randomRow][randomCol] = 1;
      liveCells++;
    }
  }
}

void simulatesUniverse(int numRows, int numCols, int theUni[][MAX_COLS]){
  for(int i = 0; i < numRows; i++){}
}
