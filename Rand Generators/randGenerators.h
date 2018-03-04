// randGen header
#include <random>
#include <functional>
#include <fstream>

const int LIST_SIZE = 1000000;

int generateRandListMersenne(int, int, int*);
int generateRandListCustom(int, int, int*);

int writeToFile(int*, char*);
