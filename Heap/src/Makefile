all: main

main : Main.o BinaryHeap.o BinomialHeap.o FibonacciHeap.o Heap.o 
	g++ -o heap Main.o BinaryHeap.o BinomialHeap.o FibonacciHeap.o Heap.o


clean:
	rm -f *.o heap *.gv *.png
