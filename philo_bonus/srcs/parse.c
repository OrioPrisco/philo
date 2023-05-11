/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:58:55 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/11 14:16:51 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "parse.h"
#include <stdio.h>
#include "libft.h"
#include "philo_sem.h"

//TODO : check that results fits in an integer of size return_size
long	ft_strtol_err(const char *str, _Bool *err, size_t return_size,
	size_t arg_num)
{
	char	*endptr;
	long	result;

	(void)return_size;
	result = ft_strtol(str, &endptr, 10);
	if (*endptr || ft_strtol_check_int(str, endptr, result) || result < 0)
	{
		*err = 1;
		printf("Error while parsing argument #%zu : %s\n", arg_num, str);
		return (result);
	}
	return (result);
}

_Bool	init_sems(t_params *params)
{
	return (0
		|| my_sem_init(&params->semaphores.queue_sem, 1)
		|| my_sem_init(&params->semaphores.stop_sem, 1)
		|| my_sem_init(&params->semaphores.forks, params->numbr_philo)
	);
}

_Bool	parse_args(t_params *params, int argc, char **argv)
{
	_Bool	err;

	ft_bzero (params, sizeof(*params));
	err = 0;
	if (argc < 5)
		return (printf("Too few args\n"), 1);
	if (argc > 6)
		return (printf("Too many args\n"), 1);
	params->numbr_philo = ft_strtol_err(argv[1],
			&err, sizeof(params->numbr_philo), 1);
	if (!err && params->numbr_philo == 0)
		printf("Cannot Have 0 philosophers !\n");
	err |= params->numbr_philo == 0;
	params->time_to_die = ft_strtol_err(argv[2],
			&err, sizeof(params->time_to_die), 2);
	params->time_to_eat = ft_strtol_err(argv[3],
			&err, sizeof(params->time_to_eat), 3);
	params->time_to_slp = ft_strtol_err(argv[4],
			&err, sizeof(params->time_to_slp), 4);
	params->binge_party = argc == 5;
	if (!params->binge_party)
		params->number_eats = ft_strtol_err(argv[5],
				&err, sizeof(params->number_eats), 5);
	return (err || init_sems(params));
}
