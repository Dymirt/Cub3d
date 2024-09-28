
/*
	DESCRIPTION :
	The function ft_isalpha checks whether c is alphabetic or not.

	RETURN VALUE :
	Non-zero if c is alphabetic, zero if not.
*/

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (c);
	return (0);
}
