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

int generateRandListCustom(int rangeLower, int rangeUpper, int randList[]){
    //int x = static_cast<int>(time(0));   
    int x = 23475;
    int n = x;
    for(int i = 0; i < LIST_SIZE; ++i){
        int a = n % x;       
        int c = 3;                    
        int m = pow(2, n % 28) + x;       
        n = ((a * n) + c) % m;       
        if(n < 0){
            n = n * -1;
        }
        randList[i] = n % 10;   
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
    int customList[LIST_SIZE];
    //generateRandListMersenne(0, 9, mersenneList);
    generateRandListCustom(0, 9, customList);

    /*for(int i = 0; i < LIST_SIZE; ++i){
      std::cout << mersenneList[i] << " ";
      if(i % 20 == 0 && i){
      std::cout << std::endl;
      }
      }*/

    //std::cout << writeToFile(mersenneList, "mersenneRandList.txt");
    std::cout << writeToFile(customList, "customRandList.txt");

    return 0;
}
