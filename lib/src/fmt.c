#include "../include/fmt.h"

const char hex_digits[] = "0123456789ABCDEF";

char * fmt_llong(long long int val, struct FMT * fmt) {
	unsigned long long int copy = val;
	int len = 1, is_neg = val < 0;
	if (is_neg) {
		val = -val;
		copy = val;
	}
	while (copy /= 10) ++len;
	char * buf = malloc(sizeof(char) * (len + 1));
	if (is_neg) { buf[0] = '-'; ++len;}
	for (unsigned int i = len; i-- != is_neg; val /= 10) {
		buf[i] = '0' + (val % 10);
	}
	buf[len] = 0;
	fmt->str_len = len;
	printf("%s\n", buf);
	return buf;
}

char * fmt_ullong(unsigned  long long int val, struct FMT * fmt) {
	long long unsigned int copy = val;
	unsigned int len = 1, i = 0;

	while (copy /= 10) ++len;	
	char * buf = malloc(sizeof(char) * (len + 1));
	for (unsigned int i = len; i--; val /= 10) {
		buf[i] = '0' + (val % 10);
	}
	buf[len] = 0;
	fmt->str_len = len;
	return buf;
}

char * fmt_hex(int val, struct FMT * fmt) {
	unsigned int copy = val, len = 3, is_neg = 0;
	if (val < 0) {
		is_neg = 1;
		val = -val;
	}
	while (copy >>= 4) ++len;
	char * buf = malloc(sizeof(char) * (1 + (is_neg ? ++len : len)));
	if (is_neg) buf[0] = '-', buf[1] = '0', buf[2] = 'x';
	else buf[0] = '0', buf[1] = 'x';
	buf[len] = 0;
	fmt->str_len = len;
	do {
		buf[--len] = hex_digits[val & 15];
		val >>= 4;
	} while (val);	
	return buf;
} 
char * fmt_double(double val, struct FMT *) {  }
char * fmt_ldouble(long double val, struct FMT *) {  }

char * fmt_ptr(void * val, struct FMT * fmt) { 
	if (val == NULL) {
		return "(NULL)";
	} else {
		return fmt_hex(*((long int*)val), fmt);
	}
}

char * f(struct FMT * fmt) {
	switch (fmt->type) {
		case CHAR: {
						char * buf = malloc(2);
						buf[0] = fmt->i; buf[1] = 0;
						fmt->str_len = 1;
						return buf;
				   }
		case BOOL: {
					   if (fmt->i) {
						   fmt->str_len = 4;
						   return "true";
					   } else {
						   fmt->str_len = 5;
						   return "false";
					   }
				   }

		case INT:
		case LONG: 
		case LLONG: {
						println("{i}", fmt->i);
						return fmt_llong(fmt->i, fmt);
					}

		case UINT:
		case ULONG: 
		case ULLONG: return fmt_ullong((unsigned long long int)fmt->i, fmt);

		case HEX: return fmt_hex(fmt->i, fmt);

		// case DOUBLE:
		// case LDOUBLE:

		case PTR: return fmt_ptr(fmt->ptr, fmt);
		case STR: {
					  while (((char *)fmt->ptr)[fmt->str_len++]);
					  return fmt->ptr;
				  }
		default: {
					 println("\n[FMT Error]: '{s}' is not a valid type", type_to_str(fmt->type));
					 return "";
				 }
	}
}

void p_ullong(unsigned long long int val, struct FMT * fmt) {
	char * buf = fmt_ullong(val, fmt);
	p_str(buf);
	free(buf);
}

void p_llong(long long int val, struct FMT * fmt) {
	if (val < 0) {
		putc('-', stdout);
		val = -val;
	}
	p_ullong(val, fmt);
}

void p_hex(unsigned int val, struct FMT * fmt) {
	char * buf = fmt_hex(val, fmt);
	p_str(buf);
	free(buf);
}

void p_str(char * val) {
	while (*val) putc(*val++, stdout);	
}

void p_ptr(void * val, struct FMT * fmt) {
	if (val == NULL) {
		p_str("(NULL)");
	} else {
		p_hex(*((long int*)val), fmt);
	}

}

void p(struct FMT * fmt) {	
	switch (fmt->type) {
		case CHAR:		putc(fmt->i, stdout); break;
		case BOOL:		p_str(fmt->i ? "true" : "false"); break;

		case INT:
		case LONG:
		case LLONG:		p_llong(fmt->i, fmt); break;
		
		case UINT:
		case ULONG:
		case ULLONG:	p_ullong(fmt->i, fmt); break;
		
		case HEX:		p_hex((unsigned int)fmt->i, fmt); break;
			
		// case DOUBLE:	p_double(fmt->f); break;
		// case LDOUBLE:	p_ldouble(fmt->f); break;
					
		case PTR:		p_ptr(fmt->ptr, fmt); break;
		case STR:		p_str(fmt->ptr); break;
		default: println("\n[FMT Error]: '{s}' is not a valid type", type_to_str(fmt->type));
	}
}

unsigned int parse_uint(const char * format, unsigned int * i) {
	char c;
	unsigned int num = 0;
	while ((c = format[*i++]) != 0) {
		if ('0' <= c && c <= '9') {
			num = 10 * num + c - '0';
		}
		return num;
	}
	return 0;
}

void pop_arg(struct FMT * fmt, va_list * list) {
	
	switch (fmt->type) {
		case CHAR:		fmt->i = (char) va_arg(*list, int); break;
		case BOOL:		fmt->i = (char) va_arg(*list, int); break;
		
		case INT:		fmt->i =		va_arg(*list, int); break;
		case LONG:		fmt->i =		va_arg(*list, long int); break;
		case LLONG:		fmt->i =		va_arg(*list, long long int); break;
		
		case UINT:		fmt->i =		va_arg(*list, unsigned int); break;
		case ULONG:		fmt->i =		va_arg(*list, unsigned long int); break;
		case ULLONG:	fmt->i =		va_arg(*list, unsigned long long int); break;

		case HEX:		fmt->i =		va_arg(*list, unsigned int); break;
		
		case DOUBLE:	fmt->d =		va_arg(*list, double); break;
		case LDOUBLE:	fmt->d =		va_arg(*list, long double); break;
		
		case PTR:		fmt->ptr =		va_arg(*list, void *); break;
		case STR:		fmt->ptr =		va_arg(*list, char *); break;
	}

	// printf("\nARG:\n I='%lld', D='%Lf', PTR='%p'\n\n", fmt->i, fmt->d, fmt->ptr);

}

int parse(const char * format, unsigned int * i, struct FMT * fmt) {
	char c;
	while((c = format[(*i)++]) != '}') {
		if(c == EOF) {
			println("\n[FMT Error]: While parsing '{s}' encountered EOF", format);
			return 0;
		}
		switch(c) {
			case 'c': fmt->type = CHAR; break; // char
			case 's': fmt->type = STR; break; // char *
			case 'i': fmt->type = INT; break; // int
			case 'u': fmt->type = UINT; break; // unsigned int
			case 'x': fmt->type = HEX; break; // hexadecimal
			case 'p': fmt->type = PTR; break; // memory address
			case 'I': fmt->type = LONG; break; // long int
			case 'U': fmt->type = ULONG; break; // unsigned long int
			case 'd': fmt->type = DOUBLE; break; // double
			case 'D': fmt->type = LDOUBLE; break; // long double
			case 'b': fmt->type = BOOL; break; // boolean (char converted to 'true' or 'false')
			case 'r': fmt->repeat = 1; break; // repeat argument
			case 'q': fmt->var_len = 1; break; // use unsigned int variable for count
			case 'l': {
						int ret = parse(format, i, fmt);
						fmt->type++;
						return ret;
					  }
			case 'L': {
						int ret = parse(format, i, fmt);
						fmt->type += 2;
						return ret;
					  }
			case '*': { // list
						fmt->pointer = 1;
						fmt->count = 0;
						int ret = parse(format, i, fmt);
						if (!fmt->count || !fmt->var_len) {
							println("\n[FMT Error]: A pointer specifier must be followed by a length");
							return 0;
						} else if (fmt->count) fmt->pointer = fmt->count;
						return ret;
					}
			default:
					fmt->count = parse_uint(format, i);
		}
	}
	return 1;
}

int _print(const char * format, va_list * list) {
	
	unsigned int size = len(format), i = 0;
	char c;
	while ((c = format[i++]) != 0) {	
		if (c != '{') {
			putc(c, stdout);
			continue;
		}

		struct FMT * fmt = init_fmt();
		if (!parse(format, &i, fmt)) {
			return 0;
		}

		if (fmt->var_len) {
			if (fmt->pointer) fmt->pointer = va_arg(*list, unsigned int);
			else fmt->count = va_arg(*list, unsigned int);
		}

		if (fmt->repeat) {
			pop_arg(fmt, list);
			for (unsigned int i = 0; i < fmt->count; ++i) {
				p(fmt);
			}
		} else if (fmt->pointer) {
			fmt->ptr = va_arg(*list, void *);
			while (fmt->pointer--) {
				p(fmt);
			}
		} else {
			for (unsigned int i = 0; i < fmt->count; ++i) {
				pop_arg(fmt, list);
				p(fmt);
			}
		}
		// printf("\n%s\n\n", fmt_to_str(fmt));
	}	
	return 1;
}

int print(const char * format, ...) {

	va_list list, copy;
	va_start(list, format);
	va_copy(copy, list);
	int ret = _print(format, &list);
	va_end(copy);
	va_end(list);
	return ret;
}

int println(const char * format, ...) {

	va_list list, copy;
	va_start(list, format);
	va_copy(copy, list);
	int ret = _print(format, &copy);
	va_end(copy);
	va_end(list);
	putc(10, stdout);
	return ret;

}

char * format(const char * format, ...) {

	unsigned int size = len(format), buf_index = 0;
	char * buf = malloc(size * sizeof(char));
	char c;
	va_list list, copy;
	va_start(list, format);
	va_copy(copy, list);
	for (unsigned int i = 0; (c = format[i++]);) {	
		if (c != '{') {
			buf[buf_index++] = c;
			continue;
		}

		struct FMT * fmt = init_fmt();
		if (!parse(format, &i, fmt)) {
			return 0;
		}

		if (fmt->var_len) {
			if (fmt->pointer) fmt->pointer = va_arg(copy, unsigned int);
			else fmt->count = va_arg(copy, unsigned int);
		}

		if (fmt->repeat) {
			pop_arg(fmt, &copy);
			for (unsigned int i = 0; i < fmt->count; ++i) {
				char * src = f(fmt);
				size += fmt->str_len;
				buf = realloc(buf, size);
				buf_index += concat(buf, src, buf_index);
			}
		} else if (fmt->pointer) {
			fmt->ptr = va_arg(copy, void *);
			while (fmt->pointer--) {
				char * src = f(fmt);
				size += fmt->str_len;
				buf = realloc(buf, size);
				buf_index += concat(buf, src, buf_index);
			}
		} else {
			for (unsigned int i = 0; i < fmt->count; ++i) {
				pop_arg(fmt, &copy);
				char * src = f(fmt);
				size += fmt->str_len;
				buf = realloc(buf, size);
				buf_index += concat(buf, src, buf_index);
			}
		}
		// printf("\n%s\n\n", fmt_to_str(fmt));
	}
	va_end(copy);
	va_end(list);
	return buf;

}

void error(const char * str, ...) {

}

struct FMT * init_fmt() {

	struct FMT * fmt = calloc(1, sizeof(struct FMT));
	fmt->count = 1;

	return fmt;
}

int len(const char * str) {
	int len = 0;
	while (str[len++] != 0);
	return len;
}

int concat(char * dest, char * src, unsigned int dest_len) {
	unsigned int i = 0;
	while (src[i]) {
		dest[dest_len++] = src[i++];
	}
	return i;
}

const char * type_to_str(unsigned int type) {
	switch (type) {
		case INT: return "INT";
		case LONG: return "LONG INT"; 
		case LLONG: return "LONG LONG INT";
		case UINT: return "UNSIGNED INT";
		case ULONG: return "UNSIGNED LONG INT";
		case ULLONG: return "UNSIGNED LONG LONG INT";
		case CHAR: return "CHARACTHER";
		case BOOL: return "BOOLEAN";
		case HEX: return "HEXADECIMAL";
		case DOUBLE: return "DOUBLE";
		case LDOUBLE: return "LONG DOUBLE";
		case PTR: return "PTR";
		case STR: return "STRING";
		default: return "UNDEFINED";
	}
}

// char * fmt_to_str(struct FMT * fmt) {
//
// 	const char * template = "<i='%li', d='%Lf', ptr='%p', count='%i', type='%s', hex='%d', repeat='%d', var_len='%d', pointer='%d'>\n";
// 	const char * type = type_to_str(fmt->type);
// 	unsigned int size = len(template) + len(type) + 64;
// 	char * buf = calloc(size, sizeof(char));
// 	snprintf(buf, size, template, fmt->i, fmt->d, (int*)fmt->ptr, fmt->count, type, fmt->hex, fmt->repeat, fmt->var_len, fmt->ptr);
// 	return buf;
// }
