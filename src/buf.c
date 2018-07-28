#include "baba.h"
#include "buf.h"
#include <stdlib.h>
#include <string.h>

s_buf	*buf_new(size_t item_size) {
	s_buf	*buf;

	buf = malloc(sizeof(s_buf));
	if (!buf)
		return 0;
	buf->data = 0;
	buf->len = 0;
	buf->allocated = 0;
	buf->item_size = item_size;
	return buf;
}

int		buf_push(s_buf *buf, const void *elem) {
	if ((buf->len + 1) >= buf->allocated)
		if (!buf_realloc(buf, (buf->allocated == 0 ? 8 : buf->allocated * 2)))
			return ERR;
	memcpy(buf->data + (buf->len * buf->item_size), elem, buf->item_size);
	buf->len += 1;
	return OK;
}

void	*buf_pop(s_buf *buf) {
	void	*res;

	if (!buf->len)
		return 0;
	res = malloc(buf->item_size);
	if (!res)
		return 0;
	buf->len -= 1;
	memcpy(res, buf->data + (buf->len * buf->item_size), buf->item_size);
	return res;
}

int		buf_realloc(s_buf *buf, size_t new_size) {
	buf->data = realloc(buf->data, new_size * buf->item_size);
	return buf->data != 0;
}

void	buf_del(s_buf *buf) {
	free(buf->data);
	buf->data = 0;
	buf->allocated = 0;
	buf->len = 0;
}
