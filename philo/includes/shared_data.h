/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:45:22 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 18:46:15 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_DATA_H
# define SHARED_DATA_H

# include <stddef.h>
# include <pthread.h>

// reasons for should stop can be :
// someone died
// error in initialization
// all philos ate
// program start should never be written to after launching threads
typedef struct s_shared_data
{
	_Bool			should_stop;
	size_t			hungry_philos;
	pthread_mutex_t	*lock;
}	t_shared_data;

#endif
