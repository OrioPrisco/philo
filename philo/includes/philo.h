/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/17 18:32:32 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include "philo_time.h"

typedef struct s_params
{
	size_t	numbr_philo;
	t_ms	time_to_die;
	t_ms	time_to_eat;
	t_ms	time_to_slp;
	_Bool	binge_party;
	size_t	number_eats;
	t_ms	program_start;
}	t_params;

#endif
