


template <typename T>
class Stack{
	T* theStack_;
	int capacity_;
	int used_;
	void grow(){
		T* newStack_=new T[capacity_*2];
		for(int i=0;i<used_;i++){
			newStack_[i]=theStack_[i];
		}
		delete [] theStack_;
		capacity_=capacity_*2;
		theStack_=newStack_;
	}
public:
	Stack(int max=10){
		theStack_=new T[max];
		capacity_=max;
		used_=0;
	}
	void push(const T& data){
		if(used_ == capacity_){
			grow();
		}
		theStack_[used_++]=data;
	}
	void pop(){
		if(used_>0)
			used_--;
	}
	const T& top() const{
		return theStack_[used_-1];
	}
	bool isEmpty() const{
		return used_==0;
	}
};







