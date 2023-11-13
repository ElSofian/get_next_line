/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:25:42 by soelalou          #+#    #+#             */
/*   Updated: 2023/11/13 17:45:47 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *line, char **save)
{
	int	i;
	int	j;
	
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i++;
	j = 0;
	*save = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	while (j < i)
	{
		(*save)[j] = line[j];
		j++;
	}
	(*save)[j] = '\0';
	line[i] = '\0';
	printf("line: %s\n", line);
	printf("save: %s\n", *save);
	return (line);
}

char	*initialize(int fd, char **save)
{
	int		ret;
	char	*line;
	char	*buf;

	ret = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = NULL;
	while (!ft_strchr(buf, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((*save == NULL && ret == 0) || ret < 0)
			return (NULL);
		buf[ret] = '\0';
		if (line == NULL)
			line = ft_strdup(buf);
		else
			line = ft_strjoin(line, buf);
		line = extract_line(line, save);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	// char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &save, 0))
		return (NULL);
	// tmp = 0;
	save = initialize(fd, &save);
	if (!save)
		return (NULL);
	else
	{
		// int	i = 0;
		// while (tmp[i])
		// {
		// 	printf("%c (%d)\n", tmp[i], tmp[i]);
		// 	i++;
		// }
	}
	return (NULL);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("return: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
