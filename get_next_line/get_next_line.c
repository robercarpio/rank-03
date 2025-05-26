#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read;
	static int	buffer_pos;
	char	*line;
	int		i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char)*7000);
	if (!line)
		return (NULL);
	while (1)
	{
		if (buffer_pos>=buffer_read)
		{
			buffer_read = read(fd,buffer,BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		line[i] = buffer[buffer_pos];
		i++;
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			break;
		}
		buffer_pos++;
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}