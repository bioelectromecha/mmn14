Assembler: commonFuncs.o main.o directivesManager.o firstPassCommandsManager.o firstPassManager.o outputManager.o passManager.o secondPassCommandManager.o secondPassManager.o
	gcc -g -ansi -Wall -pedantic commonFuncs.o main.o directivesManager.o firstPassCommandsManager.o firstPassManager.o outputManager.o
		passManager.o secondPassCommandManager.o secondPassManager.o
	-o Assembler

secondPassManager.o: secondPassManager.c
	gcc -c -ansi -Wall -pedantic secondPassManager.c -o secondPassManager.o

secondPassCommandManager.o: secondPassCommandManager.c
	gcc -c -ansi -Wall -pedantic secondPassCommandManager.c -o secondPassCommandManager.o

passManager.o: passManager.c
	gcc -c -ansi -Wall -pedantic passManager.c -o passManager.o

outputManager.o: outputManager.c
	gcc -c -ansi -Wall -pedantic outputManager.c -o outputManager.o

firstPassManager.o: firstPassManager.c
	gcc -c -ansi -Wall -pedantic firstPassManager.c -o firstPassManager.o

firstPassCommandsManager.o: firstPassCommandsManager.c
	gcc -c -ansi -Wall -pedantic firstPassCommandsManager.c -o firstPassCommandsManager.o

directivesManager.o: directivesManager.c
	gcc -c -ansi -Wall -pedantic directivesManager.c -o directivesManager.o

main.o: main.c
	gcc -c -ansi -Wall -pedantic main.c -o main.o

commonFuncs.o: commonFuncs.c
	gcc -c -ansi -Wall -pedantic commonFuncs.c -o commonFuncs.o

clean:
	rm *.o
