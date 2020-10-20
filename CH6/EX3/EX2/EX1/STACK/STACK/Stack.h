#ifndef _Stack_h_
#define _Stack_h_
#define STACK_MAX 1024
class Stack {

 public:
  
  // Constructor:
  Stack();
  
  //User-defined Copy constructor
  Stack(const Stack& source);

//Overloaded Assignment
  Stack& operator=(const Stack& source);
  
  // Push:
  void push(int i);

  // Pop:
  int pop();

  // How big is the stack?
  unsigned int size() const;

  // Print (to std::cout) 
  void print() const;

  // Test if the stack is empty
  bool isEmpty() const;

//Destructor
~Stack();

 private:

  unsigned int       _count;            // Actual length of stack.
  int                *_data;  // An array to store data.
};
#endif
