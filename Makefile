FindComponents: FindComponents.o Graph.o List.o
	gcc -o FindComponents FindComponents.o Graph.o List.o

FindComponents.o : FindComponents.c Graph.h List.h
	gcc -c -std=c99 -Wall FindComponents.c

Graph.o : Graph.c Graph.h
	gcc -c -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f FindComponents FindComponents.o Graph.o List.o