CXX = g++
CXXFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I/usr/include/gtest -l gtest -l gtest_main -pthread

all: gtest

gtest: gtest.cpp  $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) gtest.cpp $(GTEST_LL) -o $(BIN_DIR)/gtest
	#./$(BIN_DIR)/avltest 


.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstampsu