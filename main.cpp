/*
TODO:
  - make it so instead of ones and zeros its actually black or white.
  - make everything centered.
*/

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace std;

#define MAX_ROWS 20
#define MAX_COLS 20
#define MAX_CELLS 100

int getTerminalWidth();
void printCenteredText(const string&);
void displayUniverse(int, int, int[][MAX_COLS]);
void copyUniverse(int, int, int[][MAX_COLS], int[][MAX_COLS]);
void populateUniverse(int, int, int, int[][MAX_COLS]);
void simulatesUniverse(int, int, int, int[][MAX_COLS], int[][MAX_COLS]);
void checkNeighbors(int, int, int[][MAX_COLS], int[][MAX_COLS]);

int main(){
  int theUniverse[MAX_ROWS][MAX_COLS] = {0}, theUniverseCopy[MAX_ROWS][MAX_COLS] = {0};
  populateUniverse(MAX_ROWS, MAX_COLS, MAX_CELLS, theUniverse);
  simulatesUniverse(10, MAX_ROWS, MAX_COLS, theUniverse, theUniverseCopy);
  

}

int getTerminalWidth(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}
void printCenteredText(const string& text){
  int terminalWidth = getTerminalWidth();
  int textLength = text.length();
  int padding = (terminalWidth - textLength) / 2;

  for(int i = 0; i < padding; i++){
    cout << " ";
  }
  cout << text << endl;

}

void displayUniverse(int numRows, int numCols, int theUni[][MAX_COLS]){
  /*
   Outputs all the values in our universe. Either 0 (dead) or 1 (alive).
  */
  int terminalWidth = getTerminalWidth();
  int matrixWidth = numCols * 2;
  int padding = (terminalWidth - matrixWidth) / 2;
  for(int i = 0; i < numRows; i++){
    for(int p = 0; p < padding; p++){
      cout << " ";
    }
    for(int j = 0; j < numCols; j++){
      if(theUni[i][j] == 1){
        cout << "\033[47m  \033[0m";
      }
      else{
        cout << "\033[40m  \033[0m";
      }
    }
    cout << endl;
  }
  cout << endl;
}

void copyUniverse(int numRows, int numCols, int originalUni[][MAX_COLS], int copiedUni[][MAX_COLS]){
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numCols; j++){
      copiedUni[i][j] = originalUni[i][j];
    } } } void populateUniverse(int maxRows, int maxCols, int maxCells, int theUni[][MAX_COLS]){ /*
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

void simulatesUniverse(int numIterations, int numRows, int numCols, int theUni[][MAX_COLS], int theUniCopy[][MAX_COLS]){
  copyUniverse(numRows, numCols, theUni, theUniCopy);
  printCenteredText("- - - SIMULATION STARTING - - -");
  this_thread::sleep_for(1s);
  for(int i = 0; i < numIterations; i++){
    system("clear"); 
    
    string iterationText = "Iteration " + to_string(i + 1);
    printCenteredText(iterationText);
    displayUniverse(numRows, numCols, theUniCopy);
    this_thread::sleep_for(1s);

    checkNeighbors(numRows, numCols, theUni, theUniCopy);
  }
  printCenteredText("- - - SIMULATION COMPLETE - - -");
} 

void checkNeighbors(int numRows, int numCols, int theUni[][MAX_COLS], int theUniCopy[][MAX_COLS]){ int liveCells = 0; for(int i = 0; i < numRows; i++){
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
        liveCells = theUni[i + 1][j] + theUni[i + 1][j + 1] + theUni[i][j + 1] + theUni[i +  1][j - 1] + theUni[i][j - 1];
      }
      else if(i == numRows - 1 && (j != 0 && j != numCols - 1)){
          liveCells = theUni[i - 1][j] + theUni[i - 1][j + 1] + theUni[i][j - 1] + theUni[i - 1][j - 1] + theUni[i][j + 1];
      }
        else if((i != 0 && i != numRows - 1) && j == 0){
        liveCells = theUni[i][j + 1] + theUni[i + 1][j] + theUni[i + 1][j + 1] + theUni[i - 1][j + 1] + theUni[i - 1][j];
      }
        else if((i != 0 && i != numRows - 1) && j == numCols - 1){
          liveCells = theUni[i][j - 1] + theUni[i - 1][j] + theUni[i - 1][j - 1] + theUni[i + 1][j - 1] + theUni[i + 1][j]; 
      }
      
      // Checks everywhere else.
      else{
        liveCells = theUni[i - 1][j - 1] + theUni[i - 1][j] + theUni[i - 1][j + 1] + theUni[i][j - 1] + theUni[i][j + 1] + theUni[i + 1][j - 1] + theUni[i + 1][j] + theUni[i + 1][j + 1];
      }

      // The Result
      if(theUni[i][j] == 1 && (liveCells < 2 || liveCells > 3)){
        theUniCopy[i][j] = 0;
      }
      else if(theUni[i][j] == 1 && (liveCells == 2 || liveCells == 3)){
        theUniCopy[i][j] = 1;
      }
      else if(theUni[i][j] == 0 && liveCells == 3){
        theUniCopy[i][j] = 1;
      }
    }
  }
  copyUniverse(numRows, numCols, theUniCopy, theUni);
}
