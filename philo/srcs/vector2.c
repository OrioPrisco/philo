/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:25:51 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/04/24 13:58:11 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vector_data	vector_pop(t_vector *vector, size_t index)
{
	t_vector_data	data;

	data = vector->data[index];
	ft_memmove(vector->data + index, vector->data + index + 1,
		(vector->size - index - 1) * sizeof(*vector->data));
	vector->size--;
	return (data);
}

//TODO : probably can avoid recopying the end of the data twice
bool	vector_insert(t_vector *vector, size_t index, t_vector_data data)
{
	if (vector_ensure_capacity(vector, 1))
		return (0);
	ft_memmove(vector->data + index + 1, vector->data + index,
		(vector->size - index) * sizeof(*vector->data));
	vector->data[index] = data;
	vector->size++;
	return (0);
}

/*
t_vector	*vector_sort(t_vector *vector)
{
	size_t			i;
	size_t			j;
	t_vector_data	temp;

	i = 0;
	while (i < vector->size)
	{
		j = i + 1;
		while (j < vector->size)
		{
			if (vector->data[i] > vector->data[j])
			{
				temp = *(vector->data + i);
				*(vector->data + i) = *(vector->data + j);
				*(vector->data + j) = temp;
			}
			j++;
		}
		i++;
	}
	return (vector);
}
*/

bool	vector_copy(t_vector *dest, const t_vector *src)
{
	return (vector_copy_n(dest, src->data, src->size));
}

bool	vector_copy_n(t_vector *dest, const t_vector_data *src, size_t n)
{
	if (!n)
		return (vector_init(dest), 0);
	dest->data = malloc(n * sizeof(*src));
	if (!dest->data)
		return (1);
	ft_memcpy(dest->data, src, n * sizeof(*src));
	dest->size = n;
	dest->capacity = n;
	return (0);
}
