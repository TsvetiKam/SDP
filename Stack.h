#ifndef STACK_H_
#define STACK_H_
#include <iostream>

template <typename T>
class Stack {
private:
	
	struct Node {
		T data;
		Node* next;
	};

	Node *topElement;

	void del();
	void copy(const Stack<T>& other);
	void copyStack(const Node *elem);

public:

	Stack();
	Stack(const Stack<T>& other);
	Stack<T>& operator= (const Stack<T>& other);
	~Stack();
	bool isEmpty() const;
	void push( T value );
	T pop();
	T top()const;





};

template<typename T>
inline void Stack<T>::del() {
	while (!isEmpty()) {
		Node* temp = topElement;
		topElement = topElement->next;
		delete temp;
	}
}

template<typename T>
inline void Stack<T>::copyStack(const Node* elem) {
	if (elem == NULL) {
		return;
	}
	copyStack(elem->next);
	push(elem->data);
}

template<typename T>
inline void Stack<T>::copy(const Stack<T>& other) {
	topElement = NULL;
	copyStack(other.topElement);
}

template<typename T>
inline Stack<T>::Stack() {
	topElement = NULL;
}

template<typename T>
inline Stack<T>::Stack(const Stack<T>& other) {
	copy(other);
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	if (this != &other) {
		del();
		copy(other);
	}
		return *this;
}

template<typename T>
inline Stack<T>::~Stack() {
	del();
}

template<typename T>
inline bool Stack<T>::isEmpty() const{
	return topElement == NULL;
}

template<typename T>
inline void Stack<T>::push(T value) {
	Node* temp = topElement;
	topElement = new Node;
	topElement->data = value;
	topElement->next = temp;
}

template<typename T>
inline T Stack<T>::pop() {
	if (isEmpty()) {
		std::cerr << "You are trying to pop from an empty stack" << std::endl;
		return T();
	}
	else {
		Node* temp = topElement;
		T tempData = temp->data;
		topElement = topElement->next;
		delete temp;
		return tempData;
	}

}

template<typename T>
inline T Stack<T>::top() const {
	if (isEmpty()) {
		std::cerr << "You are trying to see the top element of an empty stack" << std::endl;
		return T();
	}
	else {
		return topElement->data;
	}
}









#endif