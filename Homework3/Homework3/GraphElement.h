#ifndef GRAPH_ELEMENT_H_
#define GRAPH_ELEMENT_H_
#include <iostream>

using namespace std;

template <typename T>
class GraphElement {
private:
	static int counter;
	int id;
	T data;
public:
	GraphElement() {
		data = '*';
		id = -1;
	}
	GraphElement(T data) {
		this->data = data;
		id = counter;
		++counter;
	}
	
	/*GraphElement(const GraphElement& other) {
		data = other.data;
		id = other.id;
	}
	
	GraphElement<T>& operator=(const GraphElement& other) {
		if (this != &other) {
			data = other.data;
			id = other.id;
		}
		return *this;
	}*/
	
	int getId() {
		return id;
	}
	T getData() {
		return data;
	}
	bool operator==(const GraphElement<T>& other) {
		return data = other.data && id == other.id;
	}
	bool operator!=(const GraphElement<T>& other) {
		return !(*this == other);
	}
	//bool compare(const GraphElement<T>& other) {
	//	return data = other.data && id == other.id;
	//}

	friend ostream& operator<< (ostream &output, const GraphElement<T> & elem) {
		output << "data: " << elem.data << " id: " << elem.id << " ";
		return output;
	}
};

template <typename T>
int GraphElement<T>::counter = 0;

#endif