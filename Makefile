all: project3.o item.o project3.h item.h
	gcc project3.o  item.o -o project3

project2.o: project3.c item.o project3.h
	gcc -c project3.c

item.o: item.c item.h
	gcc -c item.c

clean:
	rm  *.o
