/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlow <jlow@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:34:11 by jlow              #+#    #+#             */
/*   Updated: 2023/08/11 16:36:08 by jlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bytes_read = return value of read() function 
//            = no. of bytes read from file
// if backup_bufffer is NULL > initialize it to an empty string

#include "get_next_line_bonus.h"

char	*read_file_into_buffer(int fd, char *backup_buffer)
{
	int		bytes_read;
	char	*read_buffer;

	bytes_read = 0;
	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	while (!(ft_strchr(backup_buffer, '\n')))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		read_buffer[bytes_read] = '\0';
		backup_buffer = ft_strjoin(backup_buffer, read_buffer);
	}
	free(read_buffer);
	if (bytes_read == -1)
	{
		free(backup_buffer);
		return (NULL);
	}
	return (backup_buffer);
}

char	*split_lines_before(char *backup_buffer)
{
	char	*before_nl_buffer;
	int		i;

	i = 0;
	if (!backup_buffer || !backup_buffer[i])
		return (NULL);
	while (backup_buffer[i] != '\n' && backup_buffer[i])
		i++;
	before_nl_buffer = malloc(sizeof(char) * (i + 2));
	if (!before_nl_buffer)
		return (NULL);
	i = 0;
	while (backup_buffer[i] != '\n' && backup_buffer[i])
	{
		before_nl_buffer[i] = backup_buffer[i];
		i++;
	}
	if (backup_buffer[i] == '\n')
		before_nl_buffer[i++] = '\n';
	before_nl_buffer[i] = '\0';
	return (before_nl_buffer);
}

char	*split_lines_after(char *backup_buffer)
{
	char	*after_nl_buffer;
	int		i;

	if (!backup_buffer)
		return (NULL);
	i = 0;
	while (backup_buffer[i] != '\n' && backup_buffer[i])
		i++;
	if (!backup_buffer[i])
	{
		free(backup_buffer);
		return (NULL);
	}
	after_nl_buffer = malloc(sizeof(char) * (ft_strlen(&backup_buffer[i]) + 1));
	if (!after_nl_buffer)
	{
		free(backup_buffer);
		return (NULL);
	}
	if (backup_buffer[i] == '\n')
		i++;
	ft_strcpy(after_nl_buffer, &backup_buffer[i]);
	free(backup_buffer);
	return (after_nl_buffer);
}

char	*get_next_line(int fd)
{
	static char	*backup_buffer[1024];
	char		*result_buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!backup_buffer[fd])
	{
		backup_buffer[fd] = malloc(sizeof(char));
		if (!backup_buffer[fd])
			return (NULL);
		*backup_buffer[fd] = '\0';
	}
	backup_buffer[fd] = read_file_into_buffer(fd, backup_buffer[fd]);
	result_buffer = split_lines_before(backup_buffer[fd]);
	backup_buffer[fd] = split_lines_after(backup_buffer[fd]);
	return (result_buffer);
}
