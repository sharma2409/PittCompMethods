#include "STACK/Stack.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

// The constructor is called every time an object is created.
// This insures that the object starts from a well defined state
// ... without requiring further initialization from the client.

// unimplemented!
Stack::Stack(){
  // ==> Insert code here:
   _count=0;
   std::cout<<"Hello from the default constructor"<<std::endl;
}

// The push function increases the length of the stack by one element
// add the value to the end of the stack.  

Stack::Stack(const Stack& source)

{_count=source._count;
std::cout<<"Hello from the copy constructor"<<std::endl;

for (int i=0; i<source._count; i++)
{     	
    _data[i]=source._data[i];

}
 
}
//Overloaded Assignemnt

Stack& Stack::operator=(const Stack& source)
{
std::cout<<"ASSIGN from assignment operator"<<std::endl;
_count=source._count;

for (int i=0; i<source._count; i++)
{	_data[i]=source._data[i];

}
	return *this;
}


// unimplemented!  
void Stack::push(int i) {
  // ==> insert code here
  
  if(_count>STACK_MAX){
  throw std::range_error("Getting ahead of yourself: Stack is full");
  }
  else{
  
  _data[_count]=i;
  _count=_count+1;}
  
}

// The pop function decreases the length of the stack by one element, 
// and returs the value that is popped off

// unimplemented!  
int Stack::pop(){
  //  ==> Change the following line to something sensible...
  _count=_count-1;
  
  int popper= _data[_count];
  
  return popper;
}

Stack::~Stack()
{ //delete []_data;
std::cout<<"Hello from the Destructor"<<std::endl;
}

// The size function returns the size of the stack. The stack does
// not change so this function is "const".

// unimplemented!  
unsigned int Stack::size() const {
  //  ==> Change the following line to something sensible...
  return _count;
}

// The print function dumps the entire stack to std::cout, in a 
// human-readable format.  The stack does not change, so this function
// is "const"

// unimplemented!  
void Stack::print() const {

  if (_count==0){
  std::cout<<"Stack is empty"<<std::endl;
 
  }
  else {
  // ==> insert code here
  for (int j=0; j<_count; j++){
  std::cout<<_data[j]<<std::endl;
  }
  }
}

// The isEmpty() query function returns true or false, depending on 
// whether the stack is empty (length 0).  The stack does not change,
// so this function is "const"

// unimplemented!  
bool Stack::isEmpty() const {
  // Change the following line to something sensible
  if (_count==0){
  return true;
  }
  
  else{ 
  return false;}
  
  
  //return 0;
}

//Destrcutor

