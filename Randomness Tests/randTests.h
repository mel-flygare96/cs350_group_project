#include <fstream>
#include <string>

using namespace std;

const int NUM_RANGE = 10;
const int NUM_GROUPS = 5;

int testFrequency(int*, int[][NUM_RANGE]);
string convertToString(int[][NUM_RANGE], int);
int writeToFile(string, string);
int getRandList(string, int*);
