#include "baba.h"
#include "buf.h"
#include <stdio.h>

// TODO: create a file for test

#define TEST(x) {\
	printf("%s...", #x);\
	if (x() == OK) \
		printf(" OK\n");\
	else\
		printf(" ERR\n");\
}
	

int		test_basic() {
	s_buf	*buf;
	int		a = 10;
	int		b = 20;
	int		c = 30;

	buf = buf_new(sizeof(int));
	if (!buf)
		return ERR;
	buf_push(buf, &a);
	buf_push(buf, &b);
	buf_push(buf, &c);
	if (*(int*)buf_pop(buf) != c) // TODO: free values
		return ERR;
	if (*(int*)buf_pop(buf) != b)
		return ERR;
	if (*(int*)buf_pop(buf) != a)
		return ERR;
	return OK;
}

int		main() {
	TEST(test_basic);
	return 0;
}
