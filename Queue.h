#ifndef __QUEUE_H
#define __QUEUE_H

template<typename T>
class Queue {
public:
	int head;
	int tail;
	int size;
	int capacity;
	T* queueArray;
	

	//Construcor
	Queue() {
		head = 0;
		tail = 0;
		size = 0;
		capacity = 10;
		queueArray = new T[capacity];
	}
	
	//Destructor
	~Queue() { 
		delete[] queueArray;
	}
	
	int getCapacity() {
		return capacity;
	}
	
	int getSize() {
		return size;
	}
	
	void enqueue(T elem) {
		if(tail == capacity-1) {
			capacity += 10;
			queueArray = (T*) realloc(queueArray, capacity*sizeof(T));
		}
	
		queueArray[tail] = elem;
		tail = (tail+1)%capacity;
		size++;
	}
	
	T dequeue() {
		if(isEmpty()) {
			printf("\tError 101: Queue is empty!\n");
			T x;
			return x;
		}
		T x = queueArray[head];
		head = (head+1)%capacity;
		size--;
		return x;
	}
	
	int isEmpty() {
		if(size == 0) {
			return 1; //1 = empty
		}
		return 0;
	}

	void dump() {
		int i;
		
		for(i=head; i<tail; i++) {
			printf("(%d, %d)", queueArray[i].PERSONAL_ID, queueArray[i].PACKAGE_WEIGHT);
			if(i != tail-1) {
				printf(", ");
			}
		}
		printf("\n");
	}
	
	void getFirstInRow(int N, struct Person* p) {
		int i;
		for(i=0; i<N; i++) {
			p[i] = dequeue();
		}
	}
};

#endif //__QUEUE_H

