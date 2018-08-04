#include "baba.h"
#include "buf.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

struct ab {
	int		a;
	int		b;
};

int		test_basic() {
	s_buf	*buf;
	int		val[] = {10, 20, 30};

	buf = buf_new(sizeof(int));
	if (!buf)
		return ERR;
	for (int i = 0; i < LEN(val); i++) {
		if (buf_push(buf, val + i) == ERR)
			return ERR;
	}
	for (int i = 0; i < LEN(val); i++) {
		int *poped = buf_pop(buf);
		if (!poped)
			return ERR;
		if (*poped != val[LEN(val) - i - 1])
			return ERR;
		free(poped);
	}
	buf_del(buf);
	free(buf);
	return OK;
}

int		test_extend() {
	s_buf	*buf1;
	s_buf	*buf2;

	int		a[] = {10, 20, 30};
	int		b[] = {40, 50, 60};

	buf1 = buf_new(sizeof(int));
	buf2 = buf_new(sizeof(int));
	for (int i = 0; i < LEN(a); i++)
		buf_push(buf1, a + i);
	for (int i = 0; i < LEN(b); i++)
		buf_push(buf2, b + i);
	buf_extend(buf1, buf2);
	if (buf2->len > 0)
		return ERR;
	if (buf1->len != (LEN(a) + LEN(b)))
		return ERR;
	buf_del(buf1);
	buf_del(buf2);
	free(buf1);
	free(buf2);
	return OK;
}

int		test_setsize() {
	s_buf	*buf;
	struct ab ab = {.a = 10, .b = 20};

	buf = buf_new(sizeof(struct ab));
	if (!buf)
		return ERR;
	buf_push(buf, &ab);
	buf_setsize(buf, sizeof(int));
	if (buf->len != 2)
		return ERR;
	int *b = buf_pop(buf);
	int *a = buf_pop(buf);
	if (!a || !b)
		return ERR;
	if (*b != 20)
		return ERR;
	if (*a != 10)
		return ERR;
	buf_del(buf);;
	free(buf);
	free(a);
	free(b);
	return OK;
}

int		main() {
	TEST(test_basic);
	TEST(test_extend);
	TEST(test_setsize);
	return 0;
}
