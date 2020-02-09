template <typename T>
class Queue{
	SinglyList<T> theQueue_;
public:
	Queue();
	void enqueue(const T& data){
		theQueue_.push_back(data);
	}
	void dequeue(){
		theQueue_.pop_front();
	}
	const T& front() const{
		return *(theQueue_.begin());

	}
	bool isEmpty() const{
		return theQueue_.begin() == theQueue_.end();		
	} 
};
