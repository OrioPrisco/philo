/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:38:00 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/11 17:16:19 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "philo.h"
#include "debug.h"
#include "parse.h"

int	main(int argc, char **argv)
{
	t_params		params;
	t_shared_data	shared;
	pthread_mutex_t	*mutexes;

	if (parse_args(&params, argc, argv))
		return (1);
	shared = (t_shared_data){0, params.numbr_philo};
	mutexes = ft_calloc(sizeof(*mutexes), params.numbr_philo + 1);
	dump_params(&params);
}
