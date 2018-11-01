#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>

template <typename T>
class Queue {
private:

	struct Node {
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;

	void del();
	void copy(const Queue& other);

public:
	Queue();
	Queue(const Queue& other);
	Queue<T>& operator= (const Queue& other);
	~Queue();

	void push(T value);
	T pop();
	T top() const;
	bool isEmpty() const;

};

template<typename T>
inline void Queue<T>::del() {
	while (!isEmpty()) {
		pop();
	}
}

template<typename T>
inline void Queue<T>::copy(const Queue & other) {
	Node* temp = other.head;
	while (temp != NULL) {
		push(temp->data);
		temp = temp->next;
	}
}

template<typename T>
inline Queue<T>::Queue() {
	head = NULL;
	tail = NULL;
}

template<typename T>
inline Queue<T>::Queue(const Queue & other) : head(NULL), tail(NULL) {
	copy(other);
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue & other) {
	if (this != &other) {
		del();
		head = tail = NULL;
		copy(other);
	}

	return *this;
}

template<typename T>
inline Queue<T>::~Queue() {
	del();
}

template<typename T>
inline void Queue<T>::push(T value) {
	if (isEmpty()) {
		head = new Node;
		head->data = value;
		head->next = NULL;
		tail = head;
	}
	else {
		Node* temp = tail;
		tail = new Node;
		tail->next = NULL;
		tail->data = value;
		temp->next = tail;
	}
}

template<typename T>
inline T Queue<T>::pop() {
	if (isEmpty()) {
		std::cerr << "You are trying to pop from an empty queue." << std::endl;
		return T();
	}
	else {
		T value = head->data;
		Node* temp = head;
		head = head->next;
		delete temp;
		return value;
	}
}

template<typename T>
inline T Queue<T>::top() const {
	if (isEmpty()) {
		std::cerr << "You are trying to see the head of an empty queue." << std::endl;
		return T();
	}
	else {
		return head->data;
	}
}

template<typename T>
inline bool Queue<T>::isEmpty() const {
	return head == NULL;
}

#endif