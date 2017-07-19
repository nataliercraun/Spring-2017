Action/Commands for .cpp files: 

h2_lists.cpp

   g++ -g -Wall hw2_lists.cpp -o hw2_lists
   
   ./hw2_lists testlist.txt output.txt 
   
   valgrind --tool=memcheck --leak-check=yes ./hw2_lists 
   testlist.txt output.txt

llistdbl.cpp 

   g++ -g -Wall -c llistdbl.cpp -o llistdbl.o 
   g++ -g -Wall llistdbl.o llistdbl_test.cpp -o llistdbl 
   
   ./llistdbl 
   
   valgrind --tool=memcheck --leak-check=yes ./llistdbl
   
