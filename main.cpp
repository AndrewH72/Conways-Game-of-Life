#include <iostream>
#include <random>
using namespace std;

int main(){
  int numRows = 5, numColumns = 5;
  int gameBoard[numRows][numColumns];

  for(int i = 0; i < 5; i++){
    int randomNumber = rand() % 5;
    cout << randomNumber << endl;
  }

  

}
