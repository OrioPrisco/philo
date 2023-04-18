/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:19:18 by orio              #+#    #+#             */
/*   Updated: 2023/04/18 14:31:14 by orio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_time.h"
#include <sys/time.h>

t_ms	get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, (void *)0);
	return (time.tv_sec + time.tv_usec / 1000);
}

t_ms	get_ms_since(t_ms time)
{
	return (get_ms() - time);
}
