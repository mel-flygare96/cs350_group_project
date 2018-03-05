#include <fstream>
#include <string>
#include <map>

using namespace std;

const int NUM_RANGE = 10;
const int NUM_GROUPS = 5;

int testFrequency(int*, int[][NUM_RANGE]);
int testSerial(int*, int[][NUM_RANGE]);
int testPoker(int*, int*, string);
int matchHand(int*);
int checkMap(map<int, int>, int*);
string convertToString(int[][NUM_RANGE], int);
string convertPokerToString(int*);
int displayColumns(int[][NUM_RANGE], int);
int writeToFile(string, string);
int getRandList(string, int*);
