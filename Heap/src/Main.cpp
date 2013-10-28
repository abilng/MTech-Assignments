
#include <iostream>
#include "FibonacciHeap.h"

using namespace std;

int main()
{
	FibonacciHeap* fibonacciHeap = new FibonacciHeap;
	fibonacciHeap->insertKey(12);
	fibonacciHeap->insertKey(5);
	fibonacciHeap->insertKey(15);
	fibonacciHeap->insertKey(2);

	cout << "Minimum element: " << fibonacciHeap->findMin() << endl;
	fibonacciHeap->displayHeap("dummy");

	return 0;

}

