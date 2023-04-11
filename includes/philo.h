/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/11 16:54:57 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_params
{
	size_t	numbr_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_slp;
	_Bool	binge_party;
	size_t	number_eats;
}	t_params;

typedef struct s_shared_data
{
	_Bool	someone_died;
	size_t	hungry_philos;
}	t_shared_data;

//shared data lock also acts as a print lock
typedef struct s_philo
{
	const t_params	*params;
	size_t			philo_id;
	size_t			number_eats;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*shared_data_lock;
	t_shared_data	*shared_data;
}	t_philo;

#endif
