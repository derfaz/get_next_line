#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len ++;
	return (len);
}

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(s);
	if (n == 0)
		return (NULL);
	while (i < n && ((unsigned char *)s)[i] != (unsigned char)c)
		i++;
	if (((unsigned char *)s)[i] == '\0' && c == 0)
		return (s + i);
	if (i == n)
		return (NULL);
	else
		return (s + i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i1;
	int		i2;

	if (!s1)
		return (ft_strdup(s2));
	new_str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	i1 = 0;
	i2 = 0;
	while (s1[i1])
	{
		new_str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] && s2[i2] >= 0 && s2[i2] <= 127)
	{
		new_str[i1 + i2] = s2[i2];
		i2++;
	}
	new_str[i1 + i2] = '\0';
	return (new_str);
}
