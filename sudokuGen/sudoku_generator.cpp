#include <fstream>
#include "sudocu.h"

int main() {
    int n = 9;
    int k = 50;
    Sudocu sud (n);
    sud.generateSudoku();
    sud.remove(k);
    sud.printSudocu();
//   ofstream MyFile("filename.txt");

//   MyFile.close();
    return 0;
}