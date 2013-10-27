#ifndef __STACK_H
#define __STACK_H

template<typename T>
class Stack {
public:
	T* stackArray;
	int topLevel;
	int capacity;
	

	// Constructor
	Stack() {
		topLevel = -1;
	}
	
	// Destructor
	~Stack() {}
	
	// Get the sum of the elements in stack
	int Sum() {
		int sum = 0;
		int i;
		for(i=0; i<=topLevel; i++) {
			sum += stackArray[i];
		}
		return sum;
	}
	
	// Deplenigh the stack
	void Clear() {
		topLevel = -1;
	}
	
	// Alocate memory for the stack
	void initialize(int nr_elem) {
		capacity = nr_elem;
		stackArray = new T[capacity];
	}
	
	void push(T x) {
		if (topLevel == capacity-1) {
			fprintf(stderr, "\tError 13: Stack is full!\n");
			return;
		}
		else { // Stack is not full.
			topLevel++;
			stackArray[topLevel] = x;
		}
	}
	
	T pop() {
		if (topLevel == -1) {
			fprintf(stderr, "\tError 118: Stack is empty!\n");
			T x;
			return x;
		}
		else { // Stack is not empty.
			T x = stackArray[topLevel];
			topLevel--;
			return x;
		}
	}
	
	T peek() {
		if (topLevel == -1) {
			fprintf(stderr, "\tError 118: Stack is empty!\n");
			T x;
			return x;
		}
		else { // Stack is not empty.
			T x = stackArray[topLevel];
			return x;
		}
	}
	
	int isEmpty() {
		if (topLevel == -1) {
			return 1; // 1 - empty
		}
		else {
			return 0; // 0 - not empty
		}
	}
	
	void dump() { // Works only for int
 		int aux = topLevel;
 		while (aux >= 0) {
 			printf("%d", stackArray[aux]);
 			if(aux != 0) {
 				printf(", ");
 			}
 			aux--;
 		}
 		printf("\n");
 	}
};

#endif //__STACK_H
	
