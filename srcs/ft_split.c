#include "../includes/ft_ping.h"

static int	tab_count_entries(char const *s, char c)
{
	int	i;
	int	count_tab;

	i = 0;
	count_tab = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count_tab++;
		i++;
	}
	return (count_tab);
}

static void	if_countc_1(int *tab_int, char *temp, char **tab)
{
	if (tab_int[2] == 1)
	{
		tab[tab_int[3]] = strdup(temp);
		tab_int[3]++;
		tab_int[2] = 0;
		tab_int[1] = 0;
	}
}

static char	**tab_add_entries(char const *s, char *temp, char **tab, char c)
{
	int	tab_int[4];

	tab_int[0] = 0;
	tab_int[1] = 0;
	tab_int[2] = 0;
	tab_int[3] = 0;
	while (s[tab_int[0]])
	{
		while (s[tab_int[0]] != c)
		{
			temp[tab_int[1]] = s[tab_int[0]];
			tab_int[1]++;
			if (s[tab_int[0] + 1] == c || s[tab_int[0] + 1] == '\0')
			{
				temp[tab_int[1]] = '\0';
				tab_int[2]++;
				break ;
			}
			tab_int[0]++;
		}
		if_countc_1(tab_int, temp, tab);
		tab_int[0]++;
	}
	tab[tab_int[3]] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		count_tab;
	char	temp[256];
	char	**tab;

	if (!s)
		return (NULL);
	count_tab = tab_count_entries(s, c);
	tab = malloc(sizeof(*tab) * (count_tab + 1));
	if (!tab)
		return (NULL);
	count_tab = 0;
	tab = tab_add_entries(s, temp, tab, c);
	return (tab);
}