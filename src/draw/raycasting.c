/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:27:15 by mgayout           #+#    #+#             */
/*   Updated: 2024/07/13 13:27:15 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

void	raycasting(t_data *data)
{
	create_tab_walls(data);
	fill_tab_walls(data);
	calcul_len_rayons(data);  // cette fonction a garder absolument, permet de calculer laa longueur de chaque rayon jusqu'au prochain mur
	// le tableau data->len_rayons contient toutes les longueurs des rayons en commencant par 30radians a droite de la direction joueur
}


void	create_tab_walls(t_data *data)
{
	t_map	*tmp;
	int		count;
	int		y;

	tmp = data->parse.map;
	data->tab_walls = malloc(sizeof(int*) * (data->ray.ymax + 1));
	count = 0;
	y = 0;
	if (!data->tab_walls)
		exit (1);
	while (tmp)
	{
		if (y != tmp->y || !tmp->next)  // on passe a la ligne suivante si le y augmente de 1 OU si on est arrive a la fin de la liste
		{
			data->tab_walls[y] = malloc(sizeof(int) * (count + 1));  // on alloue le nombre de murs pour cette ligne
			if (!data->tab_walls[y])
				exit (1);
			count = 0;
			y++;
		}
		if (tmp->content == '1')
			count++;
		tmp = tmp->next;
	}
	data->tab_walls[y] = NULL;
}

void	fill_tab_walls(t_data *data)
{
	t_map	*tmp;
	int		i;
	int		y;
	
	tmp = data->parse.map;
	i = 0;
	y = 0;
	while (tmp)
	{
		if (y != tmp->y || !tmp->next)
		{
			data->tab_walls[y][i] = -1;
			y++;
			i = 0;
		}
		if (tmp->content == '1' && tmp->next)
		{
			data->tab_walls[tmp->y][i] = tmp->x;
			i++;
		}
		tmp = tmp->next;
	}
}

void	calcul_len_rayons(t_data *data)
{
	double	degre_ref;
	double	delta;
	double	my_dirX;
	double	my_dirY;
	int		i;

	degre_ref = -PI / 6;
	delta = (PI / 3) / 60;  // ici delta correspond a 1 degre
	i = 0;
	while (degre_ref <= PI / 6)
	{
		my_dirX = cos(data->ray.rot + degre_ref);
		my_dirY = -sin(data->ray.rot + degre_ref);
		data->len_rayons[i] = len_collision(data, my_dirX, my_dirY);
		degre_ref += delta;
		i++;
	}
	data->len_rayons[i] = -1;
	/*int	j = 0;
	int	k = 0;
	while (data->len_rayons[j] != -1)
	{
		printf("%f -- ", data->len_rayons[j]);
		j++;
		k++;
		if (k == 10)
		{
			printf("\n");
			k = 0;
		}
	}
	printf("\n   ---  \n");*/
}

double	len_collision(t_data *data, double dirX, double dirY)
{
	/* position de depart : x = data->pos.posx + 4
							y = data->pos.posy + 4
		pente = dirY / dirX en regle generale
		si dirX > 0 , le rayon va vers la droite donc on augmente sur x
		si dirX < 0 , le rayon va vers la gauche donc on diminue sur x
	*/
	double	len_rayon;
	double	pente;
	double	x;
	double	y;
	int		xref;  // x actuel qui parcourt la droite du rayon
	int		yref;  // y actuel qui parcourt la droite du rayon
	int		i;  // va permettre de decaler d'une colonne a chaque incrementation jusqu'a croiser un mur si il y en a un

	xref = (int)((data->ray.posx + 4) / data->ray.width);
	yref = (int)((data->ray.posy + 4) / data->ray.height);
	len_rayon = 100000;
	if (dirX < 0.0001 && dirX > -0.0001)
		pente = 9999;
	else
		pente = dirY / dirX;
	if (dirX > 0)
	{
		i = 1;
		while (1)
		{
			y = (((xref + i) * data->ray.width) - (data->ray.posx + 4)) * pente;  // y correspond a la valeur en ordonnee (- position du joueur) ou il y a intersection de la droite du rayon avec l'abscisse exacte xref + i * width
			y += (data->ray.posy + 4);
			if (y > 0 && (int)y / data->ray.height < data->ray.ymax && xref + i < data->ray.xmax)  // on verifie si ce y est bien compris entre 0 et ymax
			{
				if (wall_here(data, xref + i, (int)(y / data->ray.height)))  // -> mur cote West (WE)
				{
					len_rayon = sqrt(pow((y - (data->ray.posy + 4)), 2) + pow(((xref + i) * data->ray.width) - (data->ray.posx + 4), 2));
					break;
				}
			}
			else  // cas ou je suis sorti de la map (peut se produire quand la pente est trop inclinee [correspond a un rayon quasi vertical])
				break;
			i++;
		}
		i = 1;
		if (dirY > 0)  // on est entre 0 et -PI / 2
		{
			while (1)
			{
				x = (((yref + i) * data->ray.height) - (data->ray.posy + 4)) / pente;
				x += (data->ray.posx + 4);
				if (x > 0 && (int)x / data->ray.width < data->ray.xmax && yref + i < data->ray.ymax)
				{
					if (wall_here(data, (int)x / data->ray.width, yref + i))  // -> mur cote Nord (NO)
					{
						if (sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref + i) * data->ray.height) - (data->ray.posy + 4), 2)) < len_rayon)
							len_rayon = sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref + i) * data->ray.height) - (data->ray.posy + 4), 2));
						break;
					}
				}
				else
					break;
				i++;
			}
		}
		else if (dirY < 0)  // on est entre 0 et +PI / 2
		{
			while (1)
			{
				x = (((yref - i + 1) * data->ray.height) - (data->ray.posy + 4)) / pente;
				x += (data->ray.posx + 4);
				if (x > 0 && (int)x / data->ray.width < data->ray.xmax && yref - i >= 0)
				{
					if (wall_here(data, (int)x / data->ray.width, yref - i))  // -> mur cote Sud (SO)
					{
						if (sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref - i + 1) * data->ray.height) - (data->ray.posy + 4), 2)) < len_rayon)
							len_rayon = sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref - i + 1) * data->ray.height) - (data->ray.posy + 4), 2));
						break;
					}
				}
				else
					break;
				i++;
			}
		}
	}
	else if (dirX < 0)
	{
		i = 1;
		while (1)
		{
			y = (((xref - i + 1) * data->ray.width) - (data->ray.posx + 4)) * pente;  // y correspond a la valeur en ordonnee (- position du joueur) ou il y a intersection de la droite du rayon avec l'abscisse exacte xref + i * width
			y += (data->ray.posy + 4);
			if (y > 0 && (int)y / data->ray.height < data->ray.ymax && xref - i >= 0)  // on verifie si ce y est bien compris entre 0 et ymax
			{
				if (wall_here(data, xref - i, (int)(y / data->ray.height)))  // -> mur cote Est (E)
				{
					len_rayon = sqrt(pow((y - (data->ray.posy + 4)), 2) + pow(((xref - i + 1) * data->ray.width) - (data->ray.posx + 4), 2));
					break;
				}
			}
			else  // cas ou je suis sorti de la map (peut se produire quand la pente est trop inclinee [correspond a un rayon quasi vertical])
				break;
			i++;
		}
		i = 1;
		if (dirY > 0)  // on est entre -PI / 2 et -PI
		{
			while (1)
			{
				x = (((yref + i) * data->ray.height) - (data->ray.posy + 4)) / pente;
				x += (data->ray.posx + 4);
				if (x > 0 && (int)x / data->ray.width < data->ray.xmax && yref + i < data->ray.ymax)
				{
					if (wall_here(data, (int)x / data->ray.width, yref + i))  // -> mur cote Nord (NO)
					{
						if (sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref + i) * data->ray.height) - (data->ray.posy + 4), 2)) < len_rayon)
							len_rayon = sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref + i) * data->ray.height) - (data->ray.posy + 4), 2));
						break;
					}
				}
				else
					break;
				i++;
			}
		}
		else if (dirY < 0)  // on est entre +PI / 2 et +PI
		{
			while (1)
			{
				x = (((yref - i + 1) * data->ray.height) - (data->ray.posy + 4)) / pente;
				x += (data->ray.posx + 4);
				if (x > 0 && (int)x / data->ray.width < data->ray.xmax && yref - i >= 0)
				{
					if (wall_here(data, (int)x / data->ray.width, yref - i))  // -> mur cote Sud (SO)
					{
						if (sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref - i + 1) * data->ray.height) - (data->ray.posy + 4), 2)) < len_rayon)
							len_rayon = sqrt(pow((x - (data->ray.posx + 4)), 2) + pow(((yref - i + 1) * data->ray.height) - (data->ray.posy + 4), 2));
						break;
					}
				}
				else
					break;
				i++;
			}
		}
	}
	else
		len_rayon = 50;
	// dernier cas particulier ou dirX = 0
	return (len_rayon);
}

int	wall_here(t_data *data, int x, int y)
{
	int	xref;

	xref = 0;
	while (data->tab_walls[y][xref] != -1)
	{
		if (data->tab_walls[y][xref] == x)
			return (1);
		xref++;
	}
	return (0);
}
