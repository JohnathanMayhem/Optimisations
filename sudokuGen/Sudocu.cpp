#include "sudocu.h"


Sudocu::Sudocu(int n){
    srtN = (int)sqrt(n);
    table = new int[n*n];
    size = n;
    predict_table = new int[n * n];
    for (int i = 0; i < n * n; ++i) {
        predict_table[i] = 0b111111111;
        table[i] = 0;
    }
}

int Sudocu::randomInt() {
    // return rand() % 9 + 1;
    return std::experimental::randint(1, 9);
}

int Sudocu::findMinPredict() {
    int index;
    int start = size;
    int count;
    for (int j = 0; j < size*size; ++j) {
        count = 0;
        if (table[j] == 0) {
            for (int k = 0; k < size; ++k) {
                count += ((predict_table[j]>>k & 0b1) > 0) ? 1 : 0;
            }
            if (count <= start) {
                start = count;
                index = j;
            }
        }
    }
    return index;
}

bool Sudocu::checkRulls(std::vector<int> &chanched) {
    bool hasChanged = false;

    for (int i = 0; i < size * size; ++i) {
        int newPredict = 0b111111111;
        if (table[i] == 0) {
            newPredict &= ~(1<<(table[((int)(i / size)) * size]-1));
            for (int j = ((int)(i / size)) * size + 1;  (j) % size != 0; ++j) {
                newPredict &= ~(1<<(table[j]-1));
            }
            for (int j = i % size; j < size * size; j += size) {
                newPredict &= ~(1<<(table[j]-1));
            }
            int upLeft = (((int) i / size) - ((int) i / size) % srtN) * size + ((int)(i % size)/srtN) * srtN;
            for (int j = upLeft; j < upLeft + srtN; ++j) {
                for (int k = j; k - j <= 2 * size; k += size){
                    newPredict &= ~(1<<(table[k]-1));
                }
            }
            predict_table[i] = newPredict;
            if (log2(newPredict) - (int)log2(newPredict) < EPS && newPredict != 0) {
                chanched.push_back(i);
                int num = (int)log2(newPredict);
                table[i] = num + 1;
                hasChanged = true;
            }
        }
    }
    // std::cout<<"-----------------------------------\n";
    // printSudocu();
    // std::cout<<"-----------------------------------\n";
    // printPredict();
    return hasChanged;
}

bool Sudocu::tryPut() {
    std::vector<int> changed;
    int count = 0;
    for (int i = 0; i < size * size; ++i) {
        if (table[i] == 0 && predict_table[i] == 0) {
            return false;
        }
        count += (table[i] == 0)? 1 : 0;
    }
    if (count == 0) {
        return true;
    }
    int index = findMinPredict();
    for (int i = 0; i < size; ++i) {
        if ((predict_table[index]>>i & 1) != 0) {
            table[index] = i + 1;
        } else {
            continue;
        }
        std::vector<int> changed;
        while(this->checkRulls(changed)){}
        if (tryPut()) {
            return true;
        } else {
            table[index] = 0;
            for (int k: changed) {
                table[k] = 0;
            }
        }
    }
    return false;
}

bool Sudocu::unUsedInBox(int i, int num) {
    for (int j = i; j - i < srtN; ++j) {
        for (int k = j; k - j <= 2 * size; k += size) {
            if (table[k] == num) {
                return true;
            }
        }
    }
    return false;
}

void Sudocu::fillBox(int i) {
    int num;
    for (int j = i; j - i < srtN; ++j) {
        for (int k = j; k - j <= 2 * size; k += size) {
            do {
                num = randomInt();
            } while (unUsedInBox(i, num));
        this->table[k] = num;
        }
    }
    
}

void Sudocu::putDiagonals() {
    for (int i = 0; i < size * size; i += srtN * size + srtN) {
        fillBox(i);
    }
}

void Sudocu::remove(int n) {
    std::set<int> indexes;
    int number = std::experimental::randint(0, size * size - 1);
    indexes.insert(number);
    for (int i = 0; i < n; i++) {
        while (indexes.count(number)) {
            number = std::experimental::randint(0, size * size - 1);
        }
        indexes.insert(number);
    }
    for (int i : indexes) {
        table[i] = 0;
    }
}

void Sudocu::printSudocu() {
    // for(int i = 0; i < size * size; i+=size) {
    //     for (int j = 0; j < size; ++j) {
    //         std::cout<<this->table[i + j]<<' ';
    //     }
    //     std::cout<<'\n';
    // }
    for(int i = 0; i < size * size; i+=size) {
        for (int j = 0; j < size; ++j) {
            if (table[i + j] == 0) std::cout<<".";
            else std::cout<<table[i + j];
        }
        std::cout<<'\n';
    }
}

void Sudocu::generateSudoku() {
    this->putDiagonals();
    std::vector<int> chenged;
    while(this->checkRulls(chenged)){}
    this->tryPut();
    printSudocu();
    std::cout<<"*****************************\n";
}

void Sudocu::printPredict() {
    std::cout<<"***********************\n";
    for(int i = 0; i < size * size; i+=size) {
        for (int j = 0; j < size; ++j) {
            for (int k = 8; k >=0; --k) {
                std::cout<<((predict_table[i + j]>>k)&1);
            }
            std::cout<<this->predict_table[i + j]<<' ';
        }
        std::cout<<'\n';
    }
}
