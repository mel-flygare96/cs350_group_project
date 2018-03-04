#include "randTests.h"
#include <iostream>

int testFrequency(int randList[], int frequencyTable[][NUM_RANGE]){
    for(int j = 0; j < NUM_RANGE * NUM_GROUPS; ++j){
        frequencyTable[j / NUM_RANGE][j % NUM_RANGE] = 0;
    }
    for(int i = 0; i < 1000000; ++i){
        ++frequencyTable[i / (1000000 / NUM_GROUPS)][randList[i]];
    }
    return 1;
}

int testSerial(int randList[], int serialTable[][NUM_RANGE]){
    for(int i = 0; i < NUM_RANGE * NUM_RANGE; ++i){
        serialTable[i / NUM_RANGE][i % NUM_RANGE] = 0;
    }
    for(int j = 0; j < 1000000; ++j){
        if(j == 999999){
            ++serialTable[randList[j]][randList[0]];
        } else {
            ++serialTable[randList[j]][randList[j + 1]];
        }
    }
    return 1;
}

string convertToString(int testTable[][NUM_RANGE], int numRows){
    string outputString = "";

    for(int i = 0; i < numRows; ++i){
        for(int j = 0; j < NUM_RANGE; ++j){
            //outputString.push_back(to_string(testTable[i][j]));
            outputString.append(to_string(testTable[i][j]));
            outputString.push_back(' ');
            //cout << testTable[i][j] << " ";
        }
        //cout << endl;
        outputString.push_back('\n');
    }
    cout << outputString;
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
    return 1;
}


int main(){
    int randList[1000000];
    int frequencyTable[NUM_GROUPS][NUM_RANGE];
    int serialTable[NUM_RANGE][NUM_RANGE];

    getRandList("mersenneRandList.txt", randList);
    testFrequency(randList, frequencyTable);
    testSerial(randList, serialTable);
    writeToFile(convertToString(frequencyTable, NUM_GROUPS), "mersenneFrequencyResults.txt");
    writeToFile(convertToString(serialTable, NUM_RANGE), "mersenneSerialResults.txt");

    return 0;
}
