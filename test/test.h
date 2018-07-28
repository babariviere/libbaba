#ifndef TEST_H
# define TEST_H

// TODO: proper test formattin
# define TEST(x) {\
	printf("%s...", #x);\
	if (x() == OK) \
		printf(" OK\n");\
	else\
		printf(" ERR\n");\
}

#endif
