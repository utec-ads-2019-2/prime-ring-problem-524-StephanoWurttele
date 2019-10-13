#include <iostream>
#include <vector>

using namespace std;

int primes[11]={2,3,5,7,11,13,17,19,23,29,31};


struct Node{
	int data;
	Node* next;
	Node* prev;
	bool used=0;
	Node(int value) : next(nullptr), prev(nullptr), data(value){};
	Node(): next(nullptr),prev(nullptr),data(-1){};
  	void killSelf() {
        	if(this->next!=nullptr)
            	this->next->killSelf();
        	this->next=nullptr;
       		delete this;
    	}
};


class CircularLinked{
	Node* tail;
	int nodes;
	public:
	Node* head;
        CircularLinked() : head(nullptr), nodes(0) {};
        void push_back(int value) {
            Node* temp=new Node(value);
            temp->next=this->head;
            if(this->head==nullptr){
                temp->prev=temp;
                this->head=temp;
                this->tail=temp;
            }
            else{
                temp->prev=this->tail;
                this->tail->next=temp;
                this->tail=temp;
            }
            this->nodes++;
            this->head->prev=temp;
        }
};

bool isPrime(int x){
	if(x%2)
		return 0;
	for(int i=0;i<12;i++){
		if(x==primes[i]){
			return 1;
		}
	}
	return 0;
}

bool fill(Node* &actual, vector<Node*> &nodes,int x,vector<vector<int>> &answers){
	for(int i=1;i<nodes.size();i++){
		if(nodes[i]->used==0 && actual->data!=nodes[i]->data){
			if(isPrime(nodes[i]->data+actual->prev->data)){
				actual->data=nodes[i]->data;
				nodes[i]->used=1;
				if(!fill(actual->next,nodes,x+1,answers)){
					nodes[i]->used=0;
					actual->data=-1;
					continue;
				}
				return 1;	
			}
			else
				continue;
		}
		else{
			if(actual->data==1){
				if(isPrime(1+actual->prev->data)){
					Node* temp=actual;
					int a=0;
					for(int i=0;i<answers.size();i++){
						for(int j=0;j<answers[i].size();j++){
							if(temp->data==answers[i][j]){
								a++;
							}
							temp=temp->next;
						}
						if(a==answers[i].size())
							return 0;
						a=0;

					}
					return 1;
				}
				else
					return 0;
			}
		}
	}
	return 0;
}
int main(){
	int cases=1;
	int casenumber=1;
	while(cases!=0){
		int keep=1;
		vector<vector<int>> answers;
		CircularLinked Circle;
		vector<Node*> nodes;
		cin>>cases;
		for(int i=1;i<cases+1;i++){
			nodes.push_back(new Node(i));
			Circle.push_back(-1);
		}
		while(Circle.head && keep){
			Circle.head->data=nodes[0]->data;
			if(fill(Circle.head->next,nodes,2,answers)){
				Node* temp=Circle.head;
				vector<int> temp2;
				for(int i=0;i<cases;i++){
					nodes[i]->used=0;
					temp2.push_back(temp->data);
					temp->data=-1;
					temp=temp->next;
				}
				answers.push_back(temp2);
			}
			else
				keep=0;
		}
		cout<<"Case "<<casenumber<<":"<<endl;
		for(int j=0;j<answers.size();j++){
			for(int i=0;i<answers[j].size()-1;i++){
				cout<<answers[j][i]<<" ";
			}
			cout<<answers[j][answers[j].size()-1];
			cout<<endl;
		}
		cout<<endl;
		casenumber++;
	}
	return 0;
}
