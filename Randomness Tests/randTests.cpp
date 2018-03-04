#include "randTests.h"
#include <iostream>

int testFrequency(int randList[], int numGroups, int frequencyTable[][NUM_RANGE]){
    frequencyTable = new int[numGroups][NUM_RANGE];
    for(int i = 0; i < numGroups; ++i){
        ++frequencyTable[i / (1000000 / numGroups)][randList[i]];
    }
    return 1;
}

string convertToString(int ** testTable, int numRows){
    string outputString = NULL;

    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < NUM_RANGE; ++j){
            //outputString.push_back(to_string(testTable[i][j]));
            outputString.append("herro ");
        }
        outputString.push_back('\n');
    }
    return outputString;
}

int writeToFile(string toWrite, string outputFile){
    ofstream out(outputFile);

    if(out.is_open()){
        out << toWrite;
        out.close();
        return 1;
    }
    return 0;
}

int getRandList(string inputFile, int randList[]){
    ifstream in(inputFile);
    char tempNum;

    if(in.is_open()){
        for(int i = 0; i < 1000000; ++i){
            in >> tempNum;
            in.ignore(10, ' ');
            randList[i] = tempNum - '0';
        }
    }

    for(int j = 50; j > 0; --j){
        cout << randList[1000000 - j] << ' ';
    }
    return 1;
}


int main(){
    int randList[1000000];

    getRandList("mersenneRandList.txt", randList);

    return 0;
}
