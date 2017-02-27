#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct 		s_blob
{
	size_t	size;
	char	*raw;
}			t_blop;

int	ft_strchr(char *str, char c)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

char	hextobyte(char *hex)
{
	const char	*base = "0123456789abdcdef";
	unsigned int	index[2];
	char		res;
	
	if ((int)(index[0] = ft_strchr(base, hex[0])) < 0 || (int)(index[1] = ft_strchr(base, hex[1])) < 0)
		return (NULL);
	res = index[0] << 4 | (char)index[1];
	printf("%c%c - %hhx\n", hex[0], hex[1], res);
	return res;
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		;
	return (i);
}

t_blop	*hex_to_blop(char *str)
{
	t_blop	*blop;
	size_t	len;
	uint8_t i;

	len = ft_strlen(str);
	if (len % 2)
		return (NULL);
	len /= 2;
	if (!(blop = (t_blop *)malloc(sizeof(t_blop))))
		return (NULL);
	if (!(blop->raw = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	blop->size = len;
	for (i = 0 ; i < len ; i++)
		blop->raw[i] = hextobyte(&str[i * 2]);
	return (blop);
}

int	print_blop(t_blop *blop)
{
	if (!blop)
		return (-1);
	return (write(1, blop->raw, blop->size));
}

int main (int ac, char **av)
{
	t_blop	*blop;

	if (ac == 1)
		return (0);
	blop = hex_to_blop(av[1]);
	print_blop(blop);
	return (0);
}
