/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbullain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:58:30 by rbullain          #+#    #+#             */
/*   Updated: 2017/04/29 18:30:10 by houssana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

/*
** description:
*/
int			optimal;
int			counter;

static void	quit_tetrim(t_board *cur, int i, int j, t_tetrim *tetrim)
{
	int k;
	int new_i;
	int new_j;

	k = 0;
	while (k < 4)
	{
		new_i = i + (tetrim->points[k]->x - tetrim->root->x);
		new_j = j + (tetrim->points[k]->y - tetrim->root->y);
		if (new_i < cur->square && new_j < cur->square &&
				cur->map[new_i][new_j] == tetrim->name)
			cur->map[new_i][new_j] = '.';
		k++;
	}
}

/*
** description:
*/

static int	is_valid(t_board *cur, int i, int j, t_tetrim *tetrim)
{
	int k;
	int new_i;
	int new_j;

	k = 0;
	while (k < 4)
	{
		new_i = i + (tetrim->points[k]->x - tetrim->root->x);
		new_j = j + (tetrim->points[k]->y - tetrim->root->y);
		if (new_i >= cur->square || new_j >= cur->square ||
				cur->map[new_i][new_j] != '.')
		{
			quit_tetrim(cur, i, j, tetrim);
			return (0);
		}
		cur->map[new_i][new_j] = tetrim->name;
		k++;
	}
	return (1);
}

/*
** description:
*/

static int	is_optimal(t_board *sol)
{
	int		nb_tetri;
	int		sqrt;
	int		i;
	int		j;

	if (optimal)
		return (1);
	i = -1;
	sqrt = 2;
	nb_tetri = sol->size / 2 - 1;
	while (sqrt * sqrt < nb_tetri * 4)
		sqrt++;
	if (sol->square > sqrt)
		return (0);
	while (++i < sol->square)
	{
		j = -1;
		while (++j < sol->square)
		{
			if (sol->map[i][j] == 'A' + nb_tetri - 1)
				return (1);
		}
	}
	return (0);
}

static void	fillit_rcs(t_board *cur, t_board *sol, t_tetrim **tetrims, int pos)
{
	int i;
	int j;

	if (pos == (cur->size / 2) - 1)
	{
		if ((cur->square = calc_square(cur)) < sol->square)
		{
			ft_putstr("found sol\n");
			clone_board(sol, cur);
			ft_putnbr(sol->square);
	ft_putchar(' ');
			ft_putnbr(counter);
			ft_putstr(" found better sol\n");
			optimal = is_optimal(sol);
			return ;
		}
	}
	i = -1;
	while (++i < cur->square)
	{
		j = -1;
		while (++j < cur->square)
		{
			counter++;
			if (optimal)
				return ;
			if (is_valid(cur, i, j, tetrims[pos]) == 1)
			{
				if (calc_square(cur) < sol->square)
					fillit_rcs(cur, sol, tetrims, pos + 1);
				quit_tetrim(cur, i, j, tetrims[pos]);
			}
		}
	}
}

/*
** description:
*/

void		fillit(t_board *solution, t_tetrim **tetrims)
{
	t_board *current;

	counter = 0;
	optimal = 0;
	current = create_board(solution->size);
	fillit_rcs(current, solution, tetrims, 0);
	free_board(current);
	ft_putnbr(counter);
	ft_putchar('\n');
	ft_putnbr(optimal);
	ft_putchar('\n');
}
