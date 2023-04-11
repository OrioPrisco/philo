/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:53:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/11 18:56:28 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_params			t_params;
typedef struct s_shared_data	t_shared_data;

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

void	populate_philos(t_philo *philos, pthread_mutex_t *mutexes,
			t_shared_data *data, const t_params *params);
size_t	launch_philos(t_philo *philos, pthread_t *threads,
			size_t number_philos);
#endif
