static size_t	get_worst_score(t_lemin *lemin)
{
	t_list	*link;
	t_room	*room;
	size_t	score;

	score = 0;
	if (lemin->end_room->nb_links > lemin->start_room->nb_links)
		link = lemin->start_room->links;
	else
		link = lemin->end_room->links;
	while (link != NULL)
	{
		room = (t_room *)link->content;
		if (room->mark != DEAD && (score == 0 || score < room->score))
			score = room->score;
		link = link->next;
	}
	ft_printf("worst score:%ld \n", score);
	return (score);
}

static void		set_distance_from_start(void *room, void *lemin, unsigned long distance)
{
	void *links;
	void *cur_room;

	if (distance != 0 && room /*== start_room*/)
		return ;
	/*room->distance_start = distance; set la distance de la salle en question from start*/
	ft_printf("[%s] ", room->name);
	ft_printf("distance:%ld ", distance);
	ft_printf("d_start:%ld\n", room->d_start);
	if (room == lemin->end_room)
		return ;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark != DEAD
			&& (cur_room->d_start == 0 || cur_room->d_start > distance))
			set_distance_from_start(cur_room, lemin, distance + 1);
		links = links->next;
	}
	if (room->nb_links < 2 && room != lemin->start_room)
		room->mark = DEAD;
}

static void		set_distance_from_end(void *room, void *lemin, unsigned long distance)
{
	t_list *links;
	t_room *cur_room;

	if (distance != 0 && room == end_room)
		return ;
	room->d_end = distance;
	room->score = room->d_end + room->d_start;
	ft_printf("[%s] ", room->name);
	ft_printf("distance:%ld ", distance);
	ft_printf("d_start:%ld ", room->d_start);
	ft_printf("d_end:%ld ", room->d_end);
	ft_printf("score:%ld \n", room->score);
	if (room == lemin->start_room)
		return ;
	links = room->links;
	while (links != NULL)
	{
		cur_room = (t_room *)links->content;
		if (cur_room->mark != DEAD && (cur_room->d_end == 0 || cur_room->d_end > distance))
			set_distance_from_end(cur_room, lemin, distance + 1);
		links = links->next;
	}
	if (room->nb_links < 2 && room != lemin->end_room)
		room->mark = DEAD;
}

void			set_distance(t_lemin *lemin)
{
	/**
	 * set distance set sur toute les salles
	 * voir si on adapte la matrix directement
	 * ou on crée un autre tableau
	 */
	set_distance_from_start(lemin->start_room, lemin, 0);
	set_distance_from_end(lemin->end_room, lemin, 0);
	lemin->nb_max_ways = get_nb_max_ways(lemin);
	lemin->max_score = get_worst_score(lemin);
	out_node(lemin->main_list_room, lemin);
}
