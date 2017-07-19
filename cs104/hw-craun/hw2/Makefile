BIN_DR = bin
CXX = g++
CPPFLAGS = -g -Wall

all: $(BIN_DR)/lab3

$(BIN_DR)/lab3: $(BIN_DR)/llistdbl.o $(BIN_DR)/.dirstamp 
	$(CXX) $(CPPFLAGS) $(BIN_DR)/llistdbl.o llistdbl_test.cpp -o $(BIN_DR)/lab3

$(BIN_DR)/llistdbl.o: llistdbl.h llistdbl.cpp $(BIN_DR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c llistdbl.cpp -o $(BIN_DR)/llistdbl.o 

.PHONY: clean
clean:
	rm -rf $(BIN_DR)
	 
$(BIN_DR)/.dirstamp: 
	mkdir -p $(BIN_DR)
	touch $(BIN_DR)/.dirstamp
