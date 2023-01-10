/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaner- <msander-@student.42sp.org.br>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:58:19 by msaner-           #+#    #+#             */
/*   Updated: 2022/11/26 18:29:32 by msaner-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_fd(char *err, int fd)
{
	if (!err)
		return ;
	while (*err)
	{
		write (fd, err, 1);
		err++;
	}
	exit(EXIT_FAILURE);
}

void	invalid_command(void)
{
	exit(127);
}
