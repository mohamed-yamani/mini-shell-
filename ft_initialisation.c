#include "sh.h"

void    ft_initialisation(t_redirection   *redirection)
{
    redirection->file = NULL;
    redirection->close = 0;
    redirection->destination_fd = 0;
    redirection->source_fd = 1;
    redirection->source_fd1 = 0;
    redirection->type = -1;
}