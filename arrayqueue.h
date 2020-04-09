template <typename T>
class Queue{
	T* theQueue_;
	int capacity_;
	int used_;   //how many items are stored in queue right now
	int front_;  //index of first item
	int back_;   //index of where to put new item
	void grow(){
		T* newQueue_=new T[capacity_*2];
		for(int i=0,j=front_;i<used_;i++,j=(j+1)%capacity_){
			newQueue_[i]=theQueue_[j];

		}
		delete [] theQueue_;
		capacity_=capacity_*2;
		theQueue_=newQueue_;
		front_=0;
		back_=used_;
	}
public:
	Queue(int max=15){
		theQueue_=new T[max];
		capacity_=max;
		used_=0;
		front_=0;
		back_=0;

	}
	void enqueue(const T& data){
		if(used_==capacity_){
			grow();
		}
		theQueue_[back_]=data;
/*method 1:	back_++;
		if(back_==capacity_){
			back_=0;
		}*/
		back_=(back_+1)%capacity_;
		used_++;
	}
	void dequeue(){
		if(used_>0){
			front_=(front_+1)%capacity_;
			used_--;
		}
	}
	const T& front() const{
		return theQueue_[front_];
	}
	bool isEmpty() const{
		return used_==0;
	} 
};
