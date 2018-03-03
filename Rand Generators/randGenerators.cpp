#include <iostream>
#include "randGenerators.h"

int generateRandListMersenne(int rangeLower, int rangeUpper, int randList[]){
    std::mt19937::result_type seed = time(0);
    auto intRand = std::bind(std::uniform_int_distribution<int>(rangeLower,rangeUpper),
            std::mt19937(seed));

    for(int i = 0; i < LIST_SIZE; ++i){
        randList[i] = intRand();
    }

    return 1;
}

int writeToFile(int randList[], char outputFile[]){
    std::ofstream out(outputFile, std::ofstream::out);
    if(out.is_open()){
        for(int i = 0; i < LIST_SIZE; ++i){
            out << randList[i] << " ";
        }
        out.close();
    } else {
        return 0;
    }
    return 1;
}

int main(){
    int mersenneList[LIST_SIZE];
    generateRandListMersenne(0, 9, mersenneList);

    /*for(int i = 0; i < LIST_SIZE; ++i){
        std::cout << mersenneList[i] << " ";
        if(i % 20 == 0 && i){
            std::cout << std::endl;
        }
    }*/

    std::cout << writeToFile(mersenneList, "mersenneRandList.txt");

    return 0;
}
