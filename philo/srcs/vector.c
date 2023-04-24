/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:19 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 13:26:30 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vector	*vector_init(t_vector *vector)
{
	ft_bzero(vector, sizeof(*vector));
	return (vector);
}

bool	vector_allocate(t_vector *vector, size_t size)
{
	if (size == 0)
		size = 1;
	vector->size = 0;
	vector->data = malloc(size * sizeof(*vector->data));
	if (!vector->data)
		return (1);
	vector->capacity = size;
	return (0);
}

bool	vector_append(t_vector *vector, t_vector_data data)
{
	if (vector_ensure_capacity(vector, 1))
		return (1);
	vector->data[vector->size] = data;
	vector->size++;
	return (0);
}

t_vector	*vector_clear(t_vector *vector)
{
	if (!vector)
		return (NULL);
	free(vector->data);
	vector->data = 0;
	vector->size = 0;
	vector->capacity = 0;
	return (vector);
}

bool	vector_ensure_capacity(t_vector *vector, size_t size)
{
	t_vector_data	*new_data;
	size_t			new_capacity;

	if (vector->capacity == 0 && size < DEFAULT_VECTOR_SIZE)
		return (vector_allocate(vector, DEFAULT_VECTOR_SIZE));
	if (vector->capacity == 0)
		return (vector_allocate(vector, size));
	if (vector->size + size < vector->capacity)
		return (0);
	new_capacity = vector->capacity * 2;
	while (vector->size + size > new_capacity)
		new_capacity *= 2;
	new_data = malloc(new_capacity * sizeof(*vector->data));
	if (!new_data)
		return (1);
	ft_memcpy(new_data, vector->data, vector->size * sizeof(*vector->data));
	free(vector->data);
	vector->data = new_data;
	vector->capacity = new_capacity;
	return (0);
}
