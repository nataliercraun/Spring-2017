CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/llistint.o $(BIN_DIR)/queueint.o 
	-@echo "--- All Built!---"

scheduling: $(BIN_DIR)/llistint.o $(BIN_DIR)/queueint.o $(BIN_DIR)/.dirstamp
	$(CC) -g $(BIN_DIR)/llistint.o $(BIN_DIR)/queueint.o scheduling.cpp -o $@

$(BIN_DIR)/llistint.o: llistint.cpp llistint.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/queueint.o: queueint.cpp queueint.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@



cnfeval: $(BIN_DIR)/cnf.o $(BIN_DIR)/.dirstamp
	$(CC) -g $(BIN_DIR)/cnf.o cnfeval.cpp -o $@

$(BIN_DIR)/cnf.o: cnf.cpp cnf.h $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c $< -o $@



$(BIN_DIR)/llistintTest: listtest.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/queueintTest: queuetest.cpp $(BIN_DIR)/queueint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean tests

queuetest: $(BIN_DIR)/queueintTest
	-@$(BIN_DIR)/queueintTest
	-@echo "--- All Tested!---"

listtest: $(BIN_DIR)/llistintTest
	-@$(BIN_DIR)/llistintTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"