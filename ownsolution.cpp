#include <iostream>
#include <fstream>
using namespace std;

bool primes[] = {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0};
bool freenum[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int size = 1;
int solution[17]={0};

void fill(int last,int pos){
	if(pos==size+1){
		if(primes[1+last]){
			for(int i=1;i<pos-1;i++){
				cout<<solution[i]<<" ";
			}
			cout<<solution[pos-1]<<endl;
		}
		return;
	}
	else{
		for(int i=2;i<=size;i++){
			if(freenum[i] && primes[last+i]){
				solution[pos]=i;
				freenum[i]=0;
				fill(i,pos+1);
				freenum[i]=1;
			}
		}
	}
}


int main(){
	int numbercase=1;
	while(cin>>size){
		if(numbercase!=1)
			cout<<endl;
		cout<<"Case "<<numbercase<<":"<<endl;
		if(size==1)
			cout<<"1"<<endl;
		else{
			solution[1]=1;
			fill(1,2);
		}
		numbercase++;
	}
	return 0;
}

