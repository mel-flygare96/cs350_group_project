#include "randTests.h"
#include <iostream>

void log(int size, int trial, int table[][20]){
    switch(size)
    {
        case 1: ++table[0][trial];
                break;
        case 2: ++table[1][trial];
                break;
        case 3: ++table[2][trial];
                break;
        case 4: ++table[3][trial];
                break;
        case 5: ++table[4][trial];
                break;
        default:++table[5][trial];
    }
}

int sanityCheck(int trial, int table[][20])
{
    cout << endl << table[0][trial] << endl
         << table[1][trial] << endl
         << table[2][trial] << endl
         << table[3][trial] << endl
         << table[4][trial] << endl
         << table[5][trial] << endl;
    return table[0][trial] + 2*table[1][trial] + 3*table[2][trial] + 
           4*table[3][trial] + 5*table[4][trial] + 6*table[5][trial];
}

string convertRunToString(int runTable[][20]){
    string output = "";

    for(int i = 0; i < 20; ++i)
    {
        output.push_back('\n');
        output.append(to_string(i+1));
        output.push_back('\n');
        for(int j = 0; j < 6; ++j)
        {
            output.append(to_string(runTable[j][i]));
            output.push_back('\n');
        }
    }
    return output;
}


string runTest(int randList[], int runTable[][20]){
    int lower = 0;      //Lower index of current trial
    int upper = 49999;  //Upper index of current trial
    int count = 1;      //Size of current run, also used to ignore beginning in case of wrapping run
    int wrapSize = 0;   //Stores size of initial run IFF the first and last elements are equal

        //Initialize runTable
    for(int i = 0; i < 6; ++i){
        for(int j = 0; j < 20; ++j)
            runTable[i][j] = 0;
    }
        //Outermost loop, performs 5 trials
    for(int i = 0; i < 20; ++i){
        //cout << endl << "TEST:\nLower: " << lower << "\nUpper: " << upper << endl;
        //If wrapping run, skip the leading run
        while(randList[wrapSize + lower] == randList[upper]){
            ++wrapSize;
        }
        //Do the thing for the list
        for(int j = lower + wrapSize; j <= upper; ++j){
            if(j == upper){
                log(count + wrapSize, i, runTable);
            } else {
                if(randList[j] == randList[j+1]){
                    ++count;
                } else {
                    log(count, i, runTable);
                    count = 1;
                }
            }
        }
        wrapSize = 0;
        lower = upper + 1;
        upper += 50000;
        cout << "Trial " << i+1 << ": " << sanityCheck(i, runTable) << " numbers, at least" << endl;
    }
    return convertRunToString(runTable);
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
    int runTable[6][20];

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
        if(argv[2][0] == 'a' || argv[2][0] == 'r'){
            runTest(randList, runTable);
            if(randEngine.compare("custom")){
                writeToFile(runTest(randList, runTable), "mersenneRunResults.txt");
            } else {
                writeToFile(runTest(randList, runTable), "customRunResults.txt");
            }
        }
    }

    //getRandList("customRandList.txt", randList);
    //testFrequency(randList, frequencyTable);
    //testSerial(randList, serialTable, "customSerialResults");
    //testSerial(randList, serialTable, randEngine + "SerialResults");
    //writeToFile(convertToString(frequencyTable, NUM_GROUPS), "customFrequencyResults.txt");

    return 0;
}
