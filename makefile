programExecutable: main.o
	g++ -o programExecutable main.o

main.o:
	g++ -c main.cpp

clean:
	rm *.o programExecutable
