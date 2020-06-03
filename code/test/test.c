

#include "syscall.h"

int main()
{
//   int result;
  
//  	result = Add(42, 23);
// 	result = Sub(42, 23);
// 	result = Div(40, 2);
// 	result = Mult(10, 23);
// 	result = Pow(3, 2);
	char *file1= "a.txt";
	char *file2= "bc.txt";
	char *testword[20];

	int filefiled1,filefiled2;
	Create(file2);
	filefiled1=Open(file1,RW);
	filefiled2=Open(file2,RW);
	Read(testword,20,filefiled1);
	Write(testword,10,filefiled2);
	Close(filefiled1);
	Close(filefiled2);
  	Halt();
  /* not reached */
}
