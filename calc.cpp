#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <typeinfo>

using namespace std;

//Global var for (Un)Displaying Debug 
bool debug = false;
float ans = 0.0;


class logger{
public:
    template <typename T>
    friend logger& operator <<(logger& log, T& value);
};
template <typename T>
logger& operator <<(logger& log, T  & value) {
    
    if(::debug){
    	cout << value;
	}
    return log;
}
// End Class

//Declare logger
logger L;


template <class T>
class Stack
{
private:
	T* st;
	int currTop, maxTop;

public:
	Stack(int = 0);
	~Stack();

	int push(T);
	T pop();
	int currentStackPos(){
		return currTop;
	}

};

template <class T>
Stack<T>::Stack(int size){
	maxTop = size;
	currTop = -1;
	st = new T[size];
}

template <class T>
Stack<T>::~Stack(){
	delete []st;
}

template <class T>
int Stack<T>::push(T a){
	if(currTop >= maxTop){
		L<<"[!] Could not push. StackOverflow"<<"\n" ;
		return -2;
	}
	currTop++;
	st[currTop] = a;
	L<<"[-] Pushed "<<a<<" to Stack"<<"\n";
	return 1;
}

template <class T>
T Stack<T>::pop(){
	if(currTop<=-1){
		L<<"[!] Could not pop. Reached the bottom"<<"\n" ;
		return -1;
	}
	currTop--;
	L<<"[-] Popped "<<st[currTop+1]<<" from Stack"<<"\n";
	return st[currTop+1];
}
//End Class

template <class T>
class Queue{
private:
	int front, rear, max;
	T *q;
	
public:
	Queue(int size=0){
		front = rear = 0;
		max = size;
		q = new T[size];
	}
	

	~Queue(){
		delete []q;
	}
	int enqueue(T);
	T dequeue();

	T& getValueFromIndex(int index){
		return q[index];
	}

	const T& getValueFromIndex(int index) const {
		return q[index];
	}

	void printQueueContents(Queue& typeInfo){
		for(int i=rear; i<front;i++){
			if(typeInfo.getValueFromIndex(i)) {
			cout<<q[i]<<" ";
			} else {
				cout<<static_cast<char>(q[i])<<" ";
			}
		}
		cout<<"\n";
	}
	int getRear(){
		return rear;
	}
	int getFront(){
		return front;
	}
	
};


template <class T>
int Queue<T>::enqueue(T elem){
	if(front>=max){
		L<<"[!] Could not enqueue. QueueOverflow"<<"\n" ;
		return -2;
	}
	q[front] = elem; front++;
	L<<"[-] Enqueued "<<elem<<" to Queue"<<"\n";
}

template <class T>
T Queue<T>::dequeue(){
	if(front<=0){
		L<<"[!] Could not dequeue. QueueUnderflow"<<"\n" ;
		return -1;
	}
	T result = q[rear];
	L<<"[-] Dequed "<<result<<" from Queue\n";
	++rear;
	return result;
	
}
//End Class

/*Function Declaration*/
float xeval(float op1, char op, float op2);
int countNonNumerals(char s[]);
int addSpace(char s[], char* a[]);




int countNonNumerals(char s[]){
	int c;
	for(int i=0; i<strlen(s); i++){
		if(s[i]>=30 && s[i]<=39) continue;
		c++;
	}
	return c;
}

void emptyArray(char arr[]){
	for(int i =0; i<40;i++){
		arr[i]='\0';
	}
}

int addSpace(char s[], char *a[]){
	int c = 0;
	int inFlag=0;
	char someArr[40];
	strcat(s,"#");
	
	int newCharPos = 0;
	
	for(int i=0; i<=strlen(s);i++){
		
		if(s[i]==' ') continue;
		if(((s[i]>='0') && (s[i]<='9')) || (s[i]=='.')){
			
			someArr[c] = s[i];
			inFlag = 1;
			
			c++;			
		} else {
			if(inFlag == 1) {
			someArr[c] = '\0';
			a[newCharPos] = new char[c+1];
			strcpy(a[newCharPos], someArr);
			
			newCharPos++;
			emptyArray(someArr);
			} 
			c=0;
			

			if(s[i]=='#') break;
			a[newCharPos] = new char;
			a[newCharPos][c] = s[i];
			
			newCharPos++;
			inFlag = 0;
		
		}
	}
	return newCharPos;


}


int main(int argc, char const *argv[])
{
	
		::debug = false;

	///Code Starts

	char* s;
	
	s =  new char[200];
	cout<<"Welcome to Calculator! Input 'Q' (without quotes) to Quit!\n Brought To You By code-projects.org \n";
	while(1) {
	cout<<"> ";
	cin.getline(s,200);
	if(s[0]=='Q' || s[0] =='q') break;
	
	char* st[200];
	//int size=3;
	int size = addSpace(s, st);
	//int stC =0;

	Stack<float> s1(200);
	Stack<float> s2(200); 
	Queue<float> q1(200);
	Queue<float> q2(200); 
	float o1, o2;
	int i=0;
	for(i=0; i<size;i++) {
		if(isdigit(st[i][0])) {
			
			q1.enqueue(atof(st[i]));
			q2.enqueue(1); //1 = number
		} else {
			
			if(st[i][0]==')'){
				
				int j = 0; 
				for(j=s1.currentStackPos() ; j>=0; j--){
					int item = s1.pop();
					if(item =='(') { 
						break; 
					} else { 
						q1.enqueue(item);
						q2.enqueue(0); 
					}
				}
				if(j<0){
					cout<<"[!] Abort! Errorenous Input"<<"\n";
				}
			} else {
			
			s1.push(st[i][0]);
			}
		}
		

	} 

	for(int k=s1.currentStackPos(); k>=0; k--){
		q1.enqueue(s1.pop());
		q2.enqueue(0);
	}
	
	float op1, op2;
	Stack<float> pfeval(200);
	for(int l=q1.getRear(); l<q1.getFront(); l++){
		if(q2.getValueFromIndex(l)==1){
			
			pfeval.push(q1.getValueFromIndex(l));
		}  else {
			
			if(pfeval.currentStackPos()<1){
				cout<<"[!] Abort! Invalid Postfix Expression. Check the Position of Operator?\n";
				exit(-1);
			}
			
			o2 = pfeval.pop();
			o1 = pfeval.pop();
			pfeval.push(xeval(o1,q1.getValueFromIndex(l),o2));
		}
	}

	float finalResult = pfeval.pop();
	cout<<"ans: "<< finalResult <<"\n";
	::ans = finalResult;
}
	return 0;
}







float xeval(float op1, char op, float op2){
	
	switch(op){

		case '+':
		return op1 + op2;
		break;

		case '-':
		return op1 - op2 ;
		break;

		case '*':
		return op1 * op2;
		break;

		case '/':
		return op1 / op2 ;
		break;

		default:
		L<<"[!] Invalid Operator: "<<op<<"\n";
		return 0;
	}
}
