#include "../includes/ft_ping.h"

void	sig_quit(int param)
{
	(void)param;

}

void	sig_int(int param)
{
	(void)param;

}

void	signals_func(void)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
}