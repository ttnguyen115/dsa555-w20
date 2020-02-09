#include "lab4.h"
template <typename T>
class Stack{
	DList<T> theStack_;
public:
	Stack(){}
	void push(const T& data){
		theStack_.push_front(data);
	}
	void pop(){
		theStack_.pop_front();
	}
	const T& top() const{
		return *(theStack_.begin());
	}
	bool isEmpty() const{
		return theStack_.begin() == theStack_.end();
	} 
}