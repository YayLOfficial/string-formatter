#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

enum {
	INT, LONG, LLONG,
	UINT, ULONG, ULLONG,
	CHAR, BOOL,
	HEX,
	DOUBLE, LDOUBLE,
	PTR, STR
};

struct FMT {
	long long int i;
	long double d;
	void * ptr;	
	int hex;

	char repeat;
	char var_len;
	unsigned int pointer; // size of array
	
	unsigned int count;
	unsigned int type;

	char * delim;
	unsigned int str_len;
};

struct FMT * init_fmt();

/*		FORMAT FUNCTIONS	*/

extern char * fmt_llong(long long int, struct FMT *);
extern char * fmt_ullong(unsigned long long int, struct FMT *);

extern char * fmt_hex(int, struct FMT *);
extern char * fmt_double(double, struct FMT *);
extern char * fmt_ldouble(long double, struct FMT *);
extern char * fmt_ptr(void *, struct FMT *);

extern char * fmt_str(char *);

extern char * f(struct FMT *);

/*		PRINT FUNCTIONS		*/

extern void p_llong(long long int, struct FMT *);
extern void p_ullong(unsigned long long int, struct FMT *);

extern void p_hex(unsigned int, struct FMT *);
extern void p_double(double, struct FMT *);
extern void p_ldouble(long double, struct FMT *);
extern void p_str(char *);
extern void p_ptr(void *, struct FMT *);

extern void p(struct FMT *);

/*		OTHER		*/

extern int parse(const char *, unsigned int *, struct FMT *);
extern unsigned int parse_uint(const char *, unsigned int *);

extern void pop_arg(struct FMT *, va_list *);
extern int _print(const char *, va_list *);

extern int print(const char *, ...);
extern int println(const char *, ...);

extern char * format(const char *, ...);

extern int len(const char *);
extern int concat(char *, char *, unsigned int);

extern const char * type_to_str(unsigned int);
// char * fmt_to_str(struct FMT *);
