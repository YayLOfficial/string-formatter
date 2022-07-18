#include <stdlib.h>
#include "fmt.h"

int main() {
	println("Test 1:");
	println("{i} | Hello, World!", 123);
	
	println("\nTest 2:");
	int i_2 = 123124;
	println("yup here {i}", i_2);

	println("\nTest 3:");
	println("<Number='{i}', String='{s}', Double_String='{2s}>", 101, "Hej", "Hello, ", "World!");	

	println("\nTest 4:");
	int * ptr = malloc(sizeof(int));
	ptr[0] = 12;
	println("{p} -> {i}", ptr, *ptr);
	free(ptr);

	println("\nTest 5:");
	char * str = 0;
	println("Value: {s}", str);
		
}
