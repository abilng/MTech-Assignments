all: main

main : Main.o Kruskal.o UnionFind.o Sort.o
	g++ -o kruskal Main.o Kruskal.o UnionFind.o Sort.o

clean:
	rm -f *.o kruskal
