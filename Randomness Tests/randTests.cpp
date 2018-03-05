#include "randTests.h"
#include <iostream>

int runTest(int randList[], int frequencyTable[][NUM_RANGE]){
    int lower = 0;
    int upper = 49999;
}

int testFrequency(int randList[], int frequencyTable[][NUM_RANGE]){
    for(int j = 0; j < NUM_RANGE * NUM_GROUPS; ++j){
        frequencyTable[j / NUM_RANGE][j % NUM_RANGE] = 0;
    }
    for(int i = 0; i < 1000000; ++i){
        ++frequencyTable[i / (1000000 / NUM_GROUPS)][randList[i]];
    }
    return 1;
}

int testSerial(int randList[], int serialTable[][NUM_RANGE], string fileName){
    for(int i = 0; i < NUM_RANGE * NUM_RANGE; ++i){
        serialTable[i / NUM_RANGE][i % NUM_RANGE] = 0;
    }
    for(int j = 0; j < 1000000; ++j){
        if(j != 0 && j % 200000 == 0){
            //displayColumns(serialTable, j / 200000);
            writeToFile(convertToString(serialTable, NUM_RANGE), fileName + to_string(j / 200000) + ".txt");
            for(int i = 0; i < NUM_RANGE * NUM_RANGE; ++i){
                serialTable[i / NUM_RANGE][i % NUM_RANGE] = 0;
            }
        }
        if((j + 1) % 200000 == 0){
            ++serialTable[randList[j]][randList[j - 199999]];
        } else {
            ++serialTable[randList[j]][randList[j + 1]];
        }
    }
    //displayColumns(serialTable, 5);
    writeToFile(convertToString(serialTable, NUM_RANGE), fileName + "5.txt");
    return 1;
}

int testPoker(int randList[], int pokerTable[], string fileName){
    // bust, pair, 2 pair, 3-kind, full house, 4-kind, 5-kind
    int numValues[NUM_RANGE];
    int match = -1;
   
    for(int i = 0; i < NUM_RANGE; ++i){
        numValues[i] = 0;
    }

    for(int k = 0; k < 7; ++k){
        pokerTable[k] = 0;
    }

    for(int j = 0; j < 1000000; j += 5){
        if(j != 0 && j % 200000 == 0){
            //displayColumns(serialTable, j / 200000);
            writeToFile(convertPokerToString(pokerTable), fileName + to_string(j / 200000) + ".txt");
            for(int k = 0; k < 7; ++k){
                pokerTable[k] = 0;
            }
        }
        for(int i = 0; i < 5; ++i){
            ++numValues[randList[j + i]];
        }
        match = matchHand(numValues);
        if(match < 0){
            return 0;
        }
        ++pokerTable[match];
        for(int k = 0; k < NUM_RANGE; ++k){
            numValues[k] = 0;
        }
    }
    writeToFile(convertPokerToString(pokerTable), fileName + "5.txt");
}

int matchHand(int numValues[]){
    map<int, int> handMap;
    for(int i = 0; i < NUM_RANGE; ++i){
        if(handMap.find(numValues[i]) != handMap.end()){
            ++handMap[numValues[i]];
        } else {
            handMap[numValues[i]] = 1;
        }
    }
    int pokerHands[7][5] = 
    {
        {1,1,1,1,1},    //bust                           
        {1,1,1,2,0},             //pair
        {1,2,2,0,0},             //2 pair
        {1,1,3,0,0},             //3 kind
        {2,3,0,0,0},             //full house
        {1,4,0,0,0},             //4 kind
        {5,0,0,0,0}              //5 kind
    };
 
    for(int j = 0; j < 7; ++j){
        if(checkMap(handMap, pokerHands[j])){
            return j;
        }
    }
    return -1;
}

int checkMap(map<int, int> handMap, int pokerHand[]){
     for(int i = 0; i < 5; ++i){
        if(handMap.find(pokerHand[i]) != handMap.end()){
            if(handMap[pokerHand[i]] == 0){
                break;
            } else {
                --handMap[pokerHand[i]];
            }
        } else {
            break;
        }
        if(i == 4){
            return 1;
        }
    }
    return 0;
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
//    cout << outputString;
    return outputString;
}

string convertPokerToString(int pokerTable[]){
    string outputString = "";

    for(int i = 0; i < 7; ++i){
        outputString.append(to_string(pokerTable[i]));
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
    return 1;
}

int displayColumns(int serialTable[][NUM_RANGE], int tableNum){
    cout << "TABLE ";
    cout << tableNum;
    cout << '\n' << "==============================" << '\n';
    for(int i = 0; i < NUM_RANGE; ++i){
        for(int j = 0; j < NUM_RANGE; ++j){
            cout << serialTable[j][i] << '\n';
        }
        cout << "====================" << '\n';
    }
    return 1;
}


int main(int argc, char *argv[]){
    int randList[1000000];
    int frequencyTable[NUM_GROUPS][NUM_RANGE];
    int serialTable[NUM_RANGE][NUM_RANGE];
    int pokerTable[7];

    string randEngine = "";

    if(argc > 1 && argv[1][0] == 'm'){
        randEngine = "mersenne";
    } else if(argc > 1 && argv[1][0] == 'c'){
        randEngine = "custom";
    } else {
        cerr << "Missing rand engine type" << endl;
    }

    getRandList(randEngine + "RandList.txt", randList);

    if(argc < 2){
        cerr << "Missing test type" << endl;
    } else {
        if(argv[2][0] == 'a' || argv[2][0] == 'f'){
            testFrequency(randList, frequencyTable);
        }
        if(argv[2][0] == 'a' || argv[2][0] == 's'){
            testSerial(randList, serialTable, randEngine + "SerialResults");
        }
        if(argv[2][0] == 'a' || argv[2][0] == 'p'){
            testPoker(randList, pokerTable, randEngine + "PokerResults");
        }
    }

    //getRandList("customRandList.txt", randList);
    //testFrequency(randList, frequencyTable);
    //testSerial(randList, serialTable, "customSerialResults");
    //testSerial(randList, serialTable, randEngine + "SerialResults");
    //writeToFile(convertToString(frequencyTable, NUM_GROUPS), "customFrequencyResults.txt");

    return 0;
}
