// New VS Malloc.cpp : Defines the entry point for the application.
//

#include "New VS Malloc.h"

using namespace std;

#include <cstdlib>
#include <iostream>

// Swap function that swaps the values of two integers pointed to by a and b
void swap(int* a, int* b) {
	if (a == nullptr || b == nullptr) { // This check will only catch null
		// pointers, not dangling pointers
		std::cerr << "Error: Null pointer argument to swap." << std::endl;
		return;
	}

	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	// Allocating and initializing memory using new and malloc
	int* pIntNew = new int(20);
	std::cout << "Before swap - Using new: " << *pIntNew << std::endl;

	int* pIntMalloc = (int*)malloc(sizeof(int));
	*pIntMalloc = 10;
	std::cout << "Before freeing - Using malloc: " << *pIntMalloc << std::endl;

	// Freeing pIntMalloc and trying to use it afterward
	free(pIntMalloc);
	// WARNING: Accessing *pIntMalloc after free is undefined behavior. This is
	// for demonstration only.
	std::cout << "After freeing (dangling pointer usage - undefined behavior): "
		<< *pIntMalloc << " -> " << &pIntMalloc << std::endl;

	pIntMalloc = nullptr;

	if (pIntMalloc == nullptr) {
		std::cout << "pIntMalloc is now null." << std::endl;
		std::cout << "After nulling (dangling pointer usage - undefined behavior): "
			//uncommennt to demonstrate exception thrown
			//<< *pIntMalloc
			<< &pIntMalloc << std::endl;
	}

	// Now, let's demonstrate the null check in swap function.
	swap(pIntMalloc, pIntNew);
	// would now exit early due to the null check.

	std::cout << "pIntMalloc set to null after free, preventing further "
		"undefined behavior from dangling usage."
		<< std::endl;

	// Proper cleanup for the other pointer
	delete pIntNew;

	// At this point, pIntNew is a dangling pointer. Uncommenting the next line
	// would demonstrate the issue, but since it's undefined behavior, we won't
	// execute it.
	std::cout << "After deletion (dangling pointer usage - THIS IS UNDEFINED "
		"BEHAVIOR): "
		<< *pIntNew << std::endl;

	// Instead, we immediately nullify the pointer to prevent misuse.
	pIntNew = nullptr;

	// Confirming that pIntNew no longer points to deallocated memory
	if (pIntNew == nullptr) {
		std::cout << "pIntNew is now null, indicating it no longer points to "
			"allocated memory."
			//uncommennt to demonstrate exception thrown
			//<< *pIntNew 
			<< " -> " << &pIntNew << std::endl;
	}

	return 0;
}

