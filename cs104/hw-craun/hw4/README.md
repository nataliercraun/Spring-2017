Action/Commands for compiling, running, and memory check: 

   compile -- 

   		make all 

   run -- 

   		./amazon database.txt 
  
   memory check -- 

   		valgrind --tool=memcheck --leak-check=yes ./amazon database.txt 
