/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stake_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:55:06 by acharik           #+#    #+#             */
/*   Updated: 2024/07/18 03:25:26 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	rotate_or_reverse(int *stake, int size, int search_for)
{
	int	i;
	int	distance_from_top;
	int	distance_from_bot;

	i = 0;
	while (i < size)
	{
		if (stake[i] == search_for)
			break ;
		i++;
	}
	distance_from_bot = i;
	distance_from_top = size - (i + 1);
	if (distance_from_top <= distance_from_bot)
		return (1);
	else
		return (0);
}

void	reverse_the_array(int **stake_a, int len)
{
	int	*new_array;
	int	i;

	new_array = malloc(sizeof(int) * len);
	i = 0;
	len--;
	while (len >= 0)
	{
		new_array[i] = (*stake_a)[len];
		i++;
		len--;
	}
	free(*stake_a);
	*stake_a = new_array;
}

void	build_stake_a(int ***stake_a_b, int *lens, int *buble_sorted)
{
	int	i;
	int	**stake_a;
	int	**stake_b;
	int	rb_or_rrb;

	stake_a = stake_a_b[0];
	stake_b = stake_a_b[1];
	i = lens[0] - 1;
	while (lens[2])
	{
		if ((*stake_b)[lens[2] - 1] == buble_sorted[i])
		{
			pa(stake_a, stake_b, &(lens[1]), &(lens[2]));
			i--;
		}
		else
		{
			rb_or_rrb = rotate_or_reverse(*stake_b, lens[2], buble_sorted[i]);
			if (rb_or_rrb)
				rb(*stake_b, lens[2]);
			else
				rrb(*stake_b, lens[2]);
		}
	}
}

void	build_stake_b(int ***stake_a_b, int *lens, int *buble_sorted,
		int *start_end)
{
	int	status;
	int	**stake_a;
	int	**stake_b;

	stake_a = stake_a_b[0];
	stake_b = stake_a_b[1];
	if (lens[0] <= 5)
	{
		sort_five_args(stake_a, stake_b, lens);
		free(*stake_a);
		free(*stake_b);
		free(buble_sorted);
		exit(1);
	}
	while (lens[1])
	{
		status = begin_checks((*stake_a)[lens[1] - 1], buble_sorted, start_end,
				lens[0]);
		dispatcher(status, stake_a_b, start_end, lens);
	}
}

int	*create_stake_a(char **argv, int len)
{
	int		*stake_a;
	char	**numbers;
	int		i[3];

	if (!len)
		return (NULL);
	stake_a = malloc(sizeof(int) * (len));
	if (!stake_a)
		return (NULL);
	ft_bzero(i, sizeof(int) * 3);
	i[0] = 1;
	while (argv[i[0]])
	{
		numbers = ft_split(argv[i[0]], ' ');
		while (numbers[i[2]])
		{
			stake_a[i[1]++] = ft_atoi(numbers[i[2]]);
			i[2]++;
		}
		free_array(numbers);
		i[2] = 0;
		i[0]++;
	}
	return (stake_a);
}
