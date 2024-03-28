#include <cmath>
#include <vector>
#include <iostream>
#include <experimental/random>
#include <set>
#define EPS 1e-4

class Sudocu {
  int *table;
  int size;
  int *predict_table;
  int srtN;

public:
  Sudocu(int n);
  void putDiagonals();
  void fillBox(int i);
  bool checkRulls(std::vector<int> &chanched);
  int findMinPredict();
  bool tryPut();
  void generateSudoku();
  int randomInt();
  bool unUsedInBox(int i, int num);
  void printSudocu();
  void printPredict();
  void remove(int n);
};