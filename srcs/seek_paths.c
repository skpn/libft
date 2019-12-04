/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/04 22:33:19 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in"

/*
5 parties principales:
	- trouver les chemins
		- partir de start, lancer get next room, ajouter la room au chemin
		- si on arrive a end on ajoute le chemin
		- si on croise un chemin on l'enleve de la config
	- ajouter un chemin a une config
		- on ajoute le chemin a la liste de chemins de la config via une
			fonction de tri par insertion
	- enlever un chemin a une config
		- on poppe le chemin de la liste de chemins de la config
	- ajouter une config
		- on realise une copie de la derniere config validee et on l'ajoute
			a la liste de configs de lem
	- remplacer une config (si on obtient une config avec le meme nombre de
		chemins, mais un nombre de tours inferieur, on remplace la config
		la plus lente par la nouvelle)
		- on poppe l'ancienne config de la liste de configs de lem, on la
			free, et on ajoute la nouvelle config a la liste de configs
*/

int		copy_config(t_lem *lem, t_config *config)
{
	
}

int		config_do(int opt, t_lem *lem, t_lem *config, t_path *path)
{
	if (opt == ADD_PATH)
		ft_lstadd_new(config->paths, path);
	else if (opt == POP_PATH)
	{
		ft_lstpop(config->paths, path);
		free_path(&path);
	}
	else if (opt == ADD_CONFIG)
		return (copy_config(lem, config));
	else if (opt == DELETE_CONFIG)
	{
		ft_lstpop(lem->config_lst, config);
		free_config(&config);
	}
	return (1);
}
