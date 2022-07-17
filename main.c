#include <stdlib.h>
#include "lib/include/fmt.h"

int main() {
	println("Test 1:");
	println("{i} | Hello, World!", 123);
	
	println("\nTest 2:");
	int i_2 = 123124;
	println("yup here {i}", i_2);
	
	println("\nTest 3:");
	struct FMT * fmt = init_fmt();
	fmt->i = 1343;
	fmt->hex = 16;
	const char * type = type_to_str(fmt->type);
	
	const char * str = format("<i='{Li}', ptr='{p}', count='{u}', type='{s}', hex='{ix}', repeat='{b}', var_len='{b}', pointer='{b}'>", fmt->i, fmt->ptr, fmt->count, type, fmt->hex, fmt->repeat, fmt->var_len, fmt->ptr);

	puts(str);

	println("<i='{Li}', ptr='{p}', count='{u}', type='{s}', hex='{ix}', repeat='{b}', var_len='{b}', pointer='{b}'>", fmt->i, fmt->ptr, fmt->count, type, fmt->hex, fmt->repeat, fmt->var_len, fmt->ptr);
		
}
