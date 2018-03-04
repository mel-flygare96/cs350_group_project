#include <fstream>
#include <string>

using namespace std;

const int NUM_RANGE = 10;

int testFrequency(int*, int, int[][NUM_RANGE]);
string convertToString(int**, int);
int writeToFile(string, string);
int getRandList(string, int*);
