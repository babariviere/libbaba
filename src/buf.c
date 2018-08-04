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
		if (!buf_realloc(buf, (buf->allocated == 0 ? BUF_ALLOC : buf->allocated * 2)))
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

void	buf_setsize(s_buf *buf, size_t new_size) {
	size_t	new_len = (buf->item_size * buf->len) / new_size;
	buf->len = new_len;
	buf->item_size = new_size;
}

int		buf_extend(s_buf *buf1, s_buf *buf2) {
	size_t	total_len = buf1->len + buf2->len;
	size_t	new_allocated = buf1->allocated == 0 ? BUF_ALLOC : buf1->allocated;
	while (new_allocated < total_len)
		new_allocated *= 2;
	if (new_allocated != buf1->allocated) {
		 if (buf_realloc(buf1, new_allocated) == ERR)
			 return ERR;
	}
	memcpy(buf1->data + (buf1->len * buf1->item_size), buf2->data, (buf2->len * buf2->item_size));
	buf1->len = total_len;
	buf_del(buf2);
	return OK;
}

int		buf_realloc(s_buf *buf, size_t new_size) {
	buf->data = realloc(buf->data, new_size * buf->item_size);
	buf->allocated = new_size;
	return buf->data != 0;
}

void	buf_del(s_buf *buf) {
	free(buf->data);
	buf->data = 0;
	buf->allocated = 0;
	buf->len = 0;
}
