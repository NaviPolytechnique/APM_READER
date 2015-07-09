# MAKEFILE FOR test_reader

.PHONY: clean
.SUFFIXES:

main : main.o 
	g++ -o main main.o libserial.a

main.o : main.cpp
	g++ -c main.cpp -o main.o
	
clean : 
	rm *.o
	
