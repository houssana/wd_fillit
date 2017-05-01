/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbullain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:58:30 by rbullain          #+#    #+#             */
/*   Updated: 2017/04/30 15:46:27 by houssana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

/*
** description:
*/

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
		{
			cur->map[new_i][new_j] = '.';
			cur->square_tab[ft_mathmax(new_i, new_j)]--;
		}
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
		cur->square_tab[ft_mathmax(new_i, new_j)]++;
		k++;
	}
	return (1);
}

static int	count_points(t_board *cur, int x, int y, int s)
{
	static int	counter = 0;
	int		i;
	int		j;

	i = x;
	if (s == 0)
		counter = 0;
	else
		while (++i < cur->square && counter < 3)
		{
			j = y - 1;
			if (cur->map[i][j + 1] != '.')
				break;
			ft_putnbr(i);
			ft_putstr(" i\n");
			while ((j += s) < cur->square && counter < 3)
			{
				if (cur->map[i][j] == '.' && j >= 0)
					counter++;
				else
					break ;
				ft_putnbr(j);
				ft_putstr(" j\n");
			}
		}
	return (counter);
}

static void	update_start(t_board *cur)
{
	int 		i;
	int 		j;
	int 		counter;

	if (cur->start->x == cur->square)
		if (cur->start->y == cur->square)
			return ;
		else
		{
			cur->start->x = 0;
			(cur->start->y)++;
		}
	ft_putnbr(cur->start->x);
	ft_putstr(" ");
	ft_putnbr(cur->start->y);
	ft_putstr("\n");
	counter = count_points(cur, cur->start->y, cur->start->x, 1);
	ft_putnbr(counter);
	ft_putstr(": counter\n");
	counter = count_points(cur, cur->start->x, cur->start->y, 1);
	ft_putnbr(counter);
	ft_putstr(": counter\n");
	counter = count_points(cur, cur->start->x, cur->start->y, -1);
	ft_putnbr(counter);
	ft_putstr(": counter\n");
	count_points(cur, 0, 0, 0);
	if (counter == 3)
		return ;
	else
	{
		(cur->start->x)++;
		ft_putstr("ok\n");
		update_start(cur);
	}
}

/*
** description:
*/
int counter = 0;
static int	fillit_rcs(t_board *cur, t_board *sol, t_tetrim **tetrims, int pos)
{
	int i;
	int j;

	ft_putnbr(counter);
	ft_putstr("\n");
	update_start(cur);
	ft_putnbr(cur->start->x);
	ft_putstr(" ");
	ft_putnbr(cur->start->y);
	ft_putstr("\n");
	if (pos == (cur->size / 2) - 1)
	{
		if ((cur->square = calc_square(cur)) < sol->square)
			clone_board(sol, cur);
		return (1);
	}
	i = ft_mathmax(cur->start->x - 3, -1);
	while (++i < cur->square)
	{
		j = ft_mathmax(cur->start->y - 3, -1);
		while (++j < cur->square)
		{
			if (counter == 3)
				return 0;
			if(is_valid(cur, i, j, tetrims[pos]))
			{
				counter++;
				print_board(cur);
				ft_putstr("\n");
				if (calc_square(cur) < sol->square)
					if (fillit_rcs(cur, sol, tetrims, pos + 1) && sol->square == sol->optimal)
						return (1);
				quit_tetrim(cur, i, j, tetrims[pos]);
			}
		}
	}
	return (0);
}

/*
** description:
*/

void		fillit(t_board *solution, t_tetrim **tetrims)
{
	t_board *current;
	
	current = create_board(solution->size);
	fillit_rcs(current, solution, tetrims, 0);
	free_board(current);
}
