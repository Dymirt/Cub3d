#include "libft.h"

/*
	DESCRIPTION :
	The function ft_putchar_fd writes the given character to the given
	file descriptor.

	RETURN VALUE :
	None.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
