

#include "syscall.h"

int
main()
{
  int result;
  
 	result = Add(42, 23);
	result = Sub(42, 23);
	result = Div(40, 2);
	result = Mult(10, 23);
	result = Pow(3, 2);

  Halt();
  /* not reached */
}
