Action/Commands for compiling, running, and memory check: 

listtest 

   make listtest 
  
   valgrind --tool=memcheck --leak-check=yes ./bin/llistintTest

scheduling 

   make scheduling 
   
   ./scheduling workload1.in
   OR
   ./scheduling workload2.in 
   
   valgrind --tool=memcheck --leak-check=yes ./scheduling workload1.in

cnfeval 

	make cnfeval 

	./cnfeval input0.cnf
	OR 
	./cnfeval input1.cnf
	OR 
	./cnfeval input2.cnf

	valgrind --tool=memcheck --leak-check=yes ./cnfeval input0.cnf
   
