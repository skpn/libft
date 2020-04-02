struct list
{
	t_lvl **content;
	int size;
	int max_size;
	int push_size;
}

1) on cree la struct avec une seule ligne
content = (int **)malloc(sizeof(int *) * 2);
content[0] = malloc(sizeof(int) * push_size);
content[1] = NULL;

2) on rajoute push_size int dans la liste
	La premiere ligne est maintenant pleine

3) on veux en rajouter 1 mais y'a plus la place
old_content = content;
content = (int **)malloc(sizeof(int *) * 3);
content[0] = old_content[0]
content[1] = malloc(sizeof(int) * push_size);
content[2] = NULL;

acces ->
nb_line = index / push_size;
nb_elem = (index - nb_ine * push_size) % push_size
