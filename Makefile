all: randGen randTest

randGen: Rand\ Generators/randGenerators.cpp Rand\ Generators/randGenerators.h
	g++ -o randGen.exe Rand\ Generators/randGenerators.cpp -std=c++11

randTest: Randomness\ Tests/randTests.cpp Randomness\ Tests/randTests.h
	g++ -o randTest.exe Randomness\ Tests/randTests.cpp -std=c++11
