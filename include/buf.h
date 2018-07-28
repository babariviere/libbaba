#ifndef BUF_H
# define BUF_H

# include <strings.h>

typedef struct {
	void	*data;
	size_t	len;
	size_t	allocated;
	size_t	item_size;
}	s_buf;

s_buf	*buf_new(size_t item_size);
// Push an elem, read the content of pointer
int		buf_push(s_buf *buf, const void *elem);
// Pop an elem, this function return an heap allocated value
void	*buf_pop(s_buf *buf);
// Realloc buf size, data will be shrinked if new_size < len
int		buf_realloc(s_buf *buf, size_t new_size);
// Free all buf values
void	buf_del(s_buf *buf);

#endif
