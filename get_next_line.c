#include "get_next_line.h"

int	write_rest(char **rdstr, char **line, char *s)
{
	int		len;
	char	*rest;
	char	*ptr_n;

	len = 0;
	while (s[len] != '\n' && s[len] > 0)
		len++;
	rest = (char *)malloc((len + 1) * sizeof(char));
	if (!rest)
		return (-1);
	rest[len] = '\0';
	while (--len >= 0)
		rest[len] = s[len];
	*line = ft_strjoin(*rdstr, rest);
	free(rest);
	if (*rdstr)
	{
		free(*rdstr);
		*rdstr = NULL;
	}
	ptr_n = ft_strchr(s, '\n');
	*rdstr = ft_strdup(++ptr_n);
	return (1);
}

int	check_nl_in_static(char **rdstr, char **line)
{
	char	*s;
	int		res;

	s = ft_strdup(*rdstr);
	if (*rdstr)
	{
		free(*rdstr);
		*rdstr = NULL;
	}
	res = write_rest(rdstr, line, s);
	free(s);
	s = NULL;
	return (res);
}

int	check_nl_or_eof(char **s1, size_t *readlen1, char **rdstr, char **line)
{
	int	res;

	if (ft_strchr(*s1, '\n') && *readlen1 > 0)
	{
		res = write_rest(rdstr, line, *s1);
		free(*s1);
		*s1 = NULL;
		return (res);
	}
	else
	{
		*line = ft_strjoin(*rdstr, *s1);
		free(*s1);
		return (0);
	}
}

int	write_line(char **rdstr, int fd, char **line)
{
	char	*s;
	char	*tmp;
	size_t	readlen;

	if (ft_strchr(*rdstr, '\n'))
		return (check_nl_in_static(rdstr, line));
	s = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!s)
		return (-1);
	s[0] = 0;
	readlen = read(fd, s, BUFFER_SIZE);
	s[readlen] = '\0';
	while ((int)readlen == BUFFER_SIZE && !ft_strchr(s, '\n'))
	{
		tmp = ft_strjoin(*rdstr, s);
		if (*rdstr)
			free(*rdstr);
		*rdstr = tmp;
		readlen = read(fd, s, BUFFER_SIZE);
		s[readlen] = '\0';
	}
	return (check_nl_or_eof(&s, &readlen, rdstr, line));
}

int	get_next_line(int fd, char **line)
{
	static char	*rdstr = NULL;
	char		*check_buf;
	int			ret;

	check_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!check_buf)
		return (-1);
	free(check_buf);
	if (line == NULL || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	ret = write_line(&rdstr, fd, line);
	if (ret <= 0)
	{
		free(rdstr);
		rdstr = NULL;
	}
	return (ret);
}
