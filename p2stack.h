#include <iostream>
using namespace std;


const int MAXSIZE = 100;
	
template <class T>
struct Stack {
   T   data[MAXSIZE];
   int top;
};
template <class T>	
void initialize(Stack<T>& s){
	s.top=0;
}
template <class T>
void destroy(Stack<T>& s){
	s.top=0;
}
template <class T>
bool isEmpty(Stack<T> s){
	if(s.top==0)
		return true;
	return false;
}
template <class T>
void push(Stack<T>& s, T val){
	s.data[s.top]=val;
	s.top++;
}
template <class T>
T    pop(Stack<T>& s){
	s.top--;
	return s.data[s.top];
}