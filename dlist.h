

template <typename T>
class DList{

	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{}, Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};

	//data members of DList
	Node* front_;
	Node* back_;

public:
	//creates an instance of the DList
	DList(); 
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	void print() const;
};

template <typename T>
DList<T>::DList(){
	front_=nullptr;
	back_=nullptr;
}

template <typename T>
void DList<T>::push_front(const T& data){

	Node* nn=new Node(data);
	front_ = nn;
	back_ = nn;

}
