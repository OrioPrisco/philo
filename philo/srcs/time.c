/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:19:18 by orio              #+#    #+#             */
/*   Updated: 2023/05/11 11:50:34 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_time.h"
#include <sys/time.h>
#include <unistd.h>

t_ms	get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, (void *)0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_ms	get_ms_since(t_ms time)
{
	return (get_ms() - time);
}

void	wait_ms(t_ms ms)
{
	t_ms	begin;
	t_ms	waited;
	t_ms	diff;

	begin = get_ms();
	while (1)
	{
		waited = get_ms_since(begin);
		if (waited >= ms)
			return ;
		diff = ms - waited;
		usleep(diff * 500);
	}
}
