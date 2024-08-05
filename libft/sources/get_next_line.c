/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaintha <shaintha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:36:21 by shaintha          #+#    #+#             */
/*   Updated: 2024/07/31 12:38:20 by shaintha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static char	*ft_strchr2(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static size_t	ft_strlen2(const char *s)
{
	size_t	i = 0;
	
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy2(char *dst, const char *src)
{
	while (*src)	
		*dst++ = *src++;
	*dst = '\0';
}

static char	*ft_strdup2(const char *src)
{
	size_t	len = ft_strlen2(src) + 1;
	char	*dst = malloc(len);
	
	if (dst == NULL)
		return (NULL);
	ft_strcpy2(dst, src);
	return (dst);
}

static char	*ft_strjoin2(char *s1, char const *s2)
{
	size_t	s1_len = ft_strlen2(s1);
	size_t	s2_len = ft_strlen2(s2);
	char	*join = malloc((s1_len + s2_len + 1));

	if (!s1 || !s2)
		return (NULL);
	if (!join)
		return (NULL);
	ft_strcpy2(join, s1);
	ft_strcpy2((join + s1_len), s2);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;
	int			to_copy;

	line = ft_strdup2(buf);
	while (!(newline = ft_strchr2(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf[countread] = '\0';
		line = ft_strjoin2(line, buf);
	}
	if (ft_strlen2(line) == 0)
		return (free(line), NULL);

	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strcpy2(buf, newline + 1);
	}
	else
	{
		to_copy = ft_strlen2(line);
		buf[0] = '\0';
	}
	line[to_copy] = '\0';
	return (line);
}


// char	*read_first_line(int fd, char *line)
// {
// 	char	*temp;
// 	int		bytes_read;

// 	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!temp)
// 		return (free(line), NULL);
// 	bytes_read = 1;
// 	ft_putendl_fd("TEST1: ", 1);
// 	ft_putendl_fd(line, 1);
// 	while (bytes_read > 0 && !(ft_strchr2(line, '\n')))
// 	{
// 		bytes_read = read(fd, temp, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 		{
// 			if (line)
// 				free(line);
// 			line = NULL;
// 			return (free(temp), NULL);
// 		}
// 		temp[bytes_read] = '\0';
// 		line = ft_strjoin_gnl(line, temp);
// 		if (!line)
// 			return (NULL);
// 	}
// 	free(temp);
// 	return (line);
// }

// char	*get_first_line(char *line)
// {
// 	char	*first_line;
// 	int		i;
// 	int		count;

// 	if (!line || !line[0])
// 		return (NULL);
// 	count = 0;
// 	while (line[count] != '\n' && line[count])
// 		count++;
// 	if (line[count] == '\n')
// 		count++;
// 	first_line = (char *)malloc((count + 1) * sizeof(char));
// 	if (!first_line)
// 		return (NULL);
// 	i = 0;
// 	while (line[i] != '\n' && line[i])
// 	{
// 		first_line[i] = line[i];
// 		i++;
// 	}
// 	if ((ft_strchr(line, '\n')))
// 		first_line[i++] = '\n';
// 	first_line[i] = '\0';
// 	return (first_line);
// }

// int	trim_next_line(char **line)
// {
// 	char	*next_line;
// 	int		i;
// 	int		count;

// 	count = 0;
// 	while ((*line)[count] != '\n' && (*line)[count])
// 		count++;
// 	if ((*line)[count] == '\0')
// 		return (free((*line)), (*line) = NULL, 1);
// 	next_line = (char *)malloc((ft_strlen((*line)) - count + 1) * sizeof(char));
// 	if (next_line == NULL)
// 		return (free((*line)), (*line) = NULL, 0);
// 	count++;
// 	i = 0;
// 	while ((*line)[count + i])
// 	{
// 		next_line[i] = (*line)[count + i];
// 		i++;
// 	}
// 	next_line[i] = '\0';
// 	free((*line));
// 	(*line) = next_line;
// 	return (1);
// }

// char	*get_next_line(int fd)
// {
// 	static char		*next_line;
// 	char			*first_line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	next_line = read_first_line(fd, next_line);
// 	if (!next_line)
// 		return (NULL);
// 	first_line = get_first_line(next_line);
// 	if (first_line == NULL)
// 	{
// 		if (next_line)
// 			free(next_line);
// 		next_line = NULL;
// 		return (NULL);
// 	}
// 	if (!trim_next_line(&next_line))
// 		return (free(first_line), NULL);
// 	return (first_line);
// }

// #include <fcntl.h>
// #include <stdio.h>

// int main(void) 
// {
// 	char	*line1 = NULL;
// 	char	*line2;
// 	char	*line3;
// 	char	*line4;
// 	char	*line5;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY); 
// 	if (fd < 0)
// 	{
// 		perror("r1");
// 		exit(1);
// 	}
// 	line1 = get_next_line(fd);
// 	line2 = get_next_line(fd);
// 	line3 = get_next_line(fd);
// 	line4 = get_next_line(fd);
// 	line5 = get_next_line(fd);
// 	close(fd);
// 	printf("fd-Line1: %s\n", line1);
// 	printf("fd-Line2: %s\n", line2);
// 	printf("fd-Line3: %s\n", line3);
// 	printf("fd-Line4: %s\n", line4);
// 	printf("fd-Line5: %s\n", line5);
// 	free(line1);
// 	free(line2);
// 	free(line3);
// 	free(line4);
// 	free(line5);
// 	return (0); 
// }
