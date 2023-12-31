/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/05/02 16:46:54 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef DEBUG
#  define DEBUG 0
# endif
# include <stddef.h>
# include "philo_time.h"
# include <pthread.h>
# include "vector.h"

typedef struct s_shared_data
{
	_Bool			should_stop;
	pthread_mutex_t	*lock;
	t_vector		queue;
	pthread_mutex_t	*queue_lock;
}	t_shared_data;

typedef struct s_params
{
	size_t			numbr_philo;
	t_ms			time_to_die;
	t_ms			time_to_eat;
	t_ms			time_to_slp;
	_Bool			binge_party;
	size_t			number_eats;
	t_ms			program_start;
	t_shared_data	*shared;
}	t_params;

#endif
