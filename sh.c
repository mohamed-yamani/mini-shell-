#include "sh.h"

# define BUF 1

char    *ft_read(char *reads)
{
    char    *buf;
    char    *tmp;

    buf = (char *)malloc(sizeof(char) * (BUF + 1));
    reads = ft_strdup("");
    while (read(0, buf, BUF))
    {
        buf[1] = '\0';
        if (ft_strchr(buf, '\n'))
            break;
        tmp = reads;
        reads = ft_strjoin(reads, buf);
        free(tmp);
    }
    return(reads);
}



char    *del_startend_space(char *delete)
{
    int i;
    char *str;

    int len;
    i = 0;
    int j = 0;
    str = (char *)malloc(sizeof(char) * (len = ft_strlen(delete)));
    while (delete[i])
    {
        if (i == 0 && delete[i] == ' ')
            i++;
        str[j] = delete[i];
        if (i == len && delete[i] == ' ')
            break ;
        i++;
        j++;
    }
    str[j] = '\0';
    return (str);
}

int     ft_calcul_cmd(char *cmd)
{
    int i;
    char **tst;

    tst = ft_strsplit(cmd, ' ');
    while (tst[i])
        i++;
    return (i);
}

int     is_number(char *str)
{
    int i;
    i = 0;

    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int     get_type(char *arg)
{
    int i;
    int type;

    i = 0;
    type = -1;
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
        {
            if (arg[i] == '>' && type == -1)
                type = one;
            else if (arg[i] == '>' && type == one)
                type = two;
            else if (arg[i] == '>' && type == two)
            {
                ft_putstr("21sh: parse error near `>");
                if (arg[i + 1] == '>')
                    ft_putchar(arg[i++]);
                ft_putendl("\'");
                return(-1);
            }
            if (arg[i] == '<')
            {
                if (type == -1)
                    type = (O_RDONLY);    ///////////// here 3
                else if (type == (O_RDONLY))      ///////////// here 3
                    type = 4;
                else
                {
                  ft_putendl("21sh: parse error near `<\'");
                  return (0);
                }
            }
        }
        i++;
    }
    //ft_putnbr(type);
    return (type);
}

char    *del_quotes(char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            i++;
        ret[i] = str[i];
        i++;
        j++;
    }
    ret[i] = '\0';
    free(str);
    return (ret);
}

char    *dollar_value(t_params *params, char *dollar)
{
    t_list *env;
    t_environnement *environnement;
    t_list *head;
    char *value;

    env = params->environnement;
    head = env;
    value = NULL;
    while (head)
    {
        environnement = head->content;
        if (!ft_strcmp(environnement->key, dollar))
        {
            if (environnement->value)
                value = ft_strdup(environnement->value);
            else
                value = NULL;
        }
        head = head->next;
    }
    return(value);
}

// char    *quotes(char *string, t_params *params)
// {
//     return(string);
// }

// char     *double_quotes(char *string, t_params *params, t_dollar *d)
// {
//     int in;
//     if(d->concatenation == NULL)
//         d->concatenation = ft_strdup("");
//     d->dollar = (char *)malloc(sizeof(char) * ft_strlen(string));

//     if(d->str == NULL)
//         d->str = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
//     d->str1 = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
//     d->s = 0;
//     d->env = params->environnement;
//     d->i++;
//     in = 0;

//     while (string[d->i] && string[d->i] != '"')
//     {
//         if (string[d->i] == '$')
//         {
//             in = 0;

//                     ft_putchar(string[d->i]);ft_putendl("in here 1");
//             d->str1[d->s] = 0;
//             d->d = 0;
//             d->s = 0;
//             d->i++;
//             d->i1 = d->i;
//             while (string[d->i] && string[d->i] != ':' && string[d->i] != '/' && string[d->i] != '$' && string[d->i] != '\'' && string[d->i] != '"') 
//             {
//                 d->dollar[d->d] = string[d->i];
//                 d->i++;
//                 d->d++;
//             }
//             if (string[d->i] == '"')
//                 d->i++;
//             d->dollar[d->d] = '\0';
//             d->concatenation = ft_strjoin(d->str1, d->concatenation);
//             d->value = (d->i == d->i1 + 1) ? ft_strdup("$") : dollar_value(params, d->dollar);

//             d->concatenation = ft_strjoin(d->concatenation, d->value ? d->value : "");
//             continue ;
//         }
//         // ft_putchar(string[d->i]);ft_putendl("in here");
//         // sleep(2);
//         d->str1[d->s] = string[d->i];
//         d->i++;
//         d->s++;
//         in = 1;
//     }
//     d->i--;
//     d->str1[d->s] = 0;
//     if (in == 0)
//         d->str1 = NULL;
    
//     // printf("d->value  1 %s\n",  d->concatenation);
//     //         sleep(2);

//     if (d->str1)
//         d->concatenation = ft_strjoin(d->concatenation, d->str1);

//     // printf("d->value  2 %s\n",  d->concatenation);
//     //         sleep(2);
//     return (d->concatenation);
// }

// // char    *checking_dollar(char *string, t_params *params)
// // {
// //     t_dollar d;

// //     d.i = 0;
// //     d.i1 = 0;
// //     d.str = NULL;




// //     while (string[d.i])
// //     {
// //         if(string[d.i] == '"')
// //         {   
// //             d.str = (char *)malloc(sizeof(char));
// //             d.str[0] = '"';
// //             d.str[1] = '\0';
// //             double_quotes(string, params, &d);
// //             printf("d.concatenation is %s\n", d.concatenation);
// //             if (d.concatenation && d.str == NULL)
// //                 d.str = ft_strdup("");
// //             d.str = ft_strjoin(d.str, d.concatenation);
// //             d.str = ft_strjoin(d.str, "\"");
// //             d.concatenation = NULL;
// //             d.i++;
// //         }

// //         if (string[d.i] == '\'')
// //         {
// //             d.s = 0;
// //             d.str1 = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
// //             d.str1[d.s] = '\'';
// //             d.i++;
// //             d.s++;
// //             while(string[d.i] && string[d.i] != '\'')
// //             {
// //                 ft_putnbr(d.i);ft_putstr(" - ");ft_putchar(string[d.i]);ft_putendl("");
// //                 d.str1[d.s] = string[d.i];
// //                 d.s++;
// //                 d.i++;
// //             }
// //             if (string[d.i] == '\'')
// //                 d.str1[d.s] = '\'';
// //             if (d.str == NULL)
// //                 d.str = ft_strdup("");
// //             else
// //                 d.str1[d.s + 1] = '\0';
// //             d.str = ft_strjoin(d.str, d.str1);
// //         }
// //         d.i++;
// //         continue ;
// //     }
// //      ft_putendl("dob  2");
// //             sleep(1);
// //    // printf("d.str is %s \n", d.str);
// //    ft_putendl(d.str);
// //     sleep(1);
// //     return (d.str);
// // }

char    *checking_dollar(char *string, t_params *params)
{
    t_list *env;
    t_environnement *environnement;
    char *dollar;
    int i;
    int d;
    char    *str;
    char    *concatenation;
    int     s;
    char       *value;
    int dq;

    dq = 0;
    concatenation = ft_strdup("");
    dollar = (char *)malloc(sizeof(char) * ft_strlen(string));
    str = (char *)malloc(sizeof(char) * ft_strlen(string));
    i = 0;
    s = 0;
    env = params->environnement;
    // if (ft_strlen(string) == 1)
    //     return(ft_strdup("$"));
    while (string[i])
    {
        if (string[i] == '\'' && !dq)
        {
            str[s++] = string[i++];
            while (string[i] && string[i] != '\'')
               str[s++] = string[i++];   
            str[s] = string[i];
            if (string[i + 1] && (s++) && (i++))
                ;
            else
               str[s] = 0;
        }

        if (string[i] == '$'/* && !dq*/)
        {
            d = 0;
            s = 0;
            int r = 0;
            i++;
            while (string[i] && string[i] != ':' && string[i] != '/' && string[i] != '$' && string[i] != '"' && string[i] != '\'') 
            {
                dollar[d] = string[i];
                i++;
                d++;
            }
            dollar[d] = '\0';

            concatenation = ft_strjoin(concatenation, str);//
            str = ft_strdup("");
            value = dollar_value(params, dollar);
            concatenation = ft_strjoin(concatenation, value ? value : "");
            continue ;
        }
        if (string[i] == '"')
            dq = !dq;
        str[s] = string[i];
        i++;
        s++;
    }
    str[s] = 0;
    concatenation = ft_strjoin(concatenation, str);
    return (concatenation);
}

char    *tabs_to_spaces(char *str) //// d'ont forget '
{
    int i;
    i = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            i++;
            while (str[i] && (str[i] != '"' || str[i] != '\'')) ///// dont forget '
                i++;
        }
        if (str[i] == '\t')
            str[i] = ' ';
        i++;
    }
    return (str);
}

int    get_source_fd(char *src, t_redirection *redirection)
{
    char *source;
    int i;
    int sr;

    i = 0;
    source = (char *)malloc(sizeof(char) * ft_strlen(src));

    if (!ft_strcmp(src, "&>"))
        {
            redirection->source_fd1 = 2;
            return (1);
        }
    if (strchr(src, '>'))
        while (src[i] != '>')
        {
            source[i] = src[i];
            i++;
        }
    else if (strchr(src, '<'))                          ////                for '<'
        while (src[i] != '<')
        {
            source[i] = src[i];
            i++;
        }
    else
        return (1);
    source[i] = '\0';
    sr = ft_atoi(source);
    free(source);
    if (src[0] == '>')
        return(1);
    return (sr);
}

// char      *stop_heredoc(char *buf)
// {
//     char *eof;
//     int i;

//     eof = (char *)malloc(sizeof(char) * 250);
//     i = 0;
//     while(buf[i] != '\n' && buf[i] != '\0')
//     {
//         eof[i] = buf[i];
//         i++;
//     }
//     eof[i] = '\0';
//     return (eof);
// }

// char    *heredoc_end(char *reads)
// {
//     int i;

//     i = 0;
//     while(reads[i])
//     {
//         if (reads[i + 1] == '\0' && reads[i] == '\n')
//             reads[i] = '\0';
//         i++;
//     }
//     return (reads);
// }

int     get_heredoc(t_redirection *redirection, t_cmds *tcmds)
{
    if (redirection->type == 4)
    {
        char    *buf;
        char    *tmp;
        char    *reads;
        char    *tmp1;
        int     len;
    
        if (redirection->file == NULL)
        {
            ft_putendl("21sh: parse error near `\\n'");
            return (0);
        }
        buf = (char *)malloc(sizeof(char) * 351);
        reads = strdup("");
        ft_putstr("heredoc> ");
        while ((len = read(0, buf, 350)))
        {
            buf[len - 1] = 0;
            if (!ft_strcmp(buf, redirection->file))
                break ;
            tmp = reads;
            reads = ft_strjoin(reads, ft_strjoin(buf, "\n"));
            free(tmp);
            ft_putstr("heredoc> ");
            ft_bzero(buf, 350);
        }
        tcmds->heredoc = reads; 
        free(redirection->file);
        redirection->file = NULL;
    }
    return (1);
}

int    ft_getargs(char **pipes, t_list **lst, t_params *params)
{
    int i;
    t_list *list;
    t_cmds *tcmds;
    char **args;
    t_redirection   *redirection;
    t_list          *redirections;
    t_list          *list_redi;
    int             red;


    i = 0;
    int redi = -5;
    int j;
    int k;

    red = 0;
    char **argv;
    int a;
    a = 0;
    // else
    redirections = NULL;

//    ft_putendl("ft_getargs here ");sleep(2);
    while (pipes[i])
    {
        //(*lst) = NULL;
        pipes[i] = tabs_to_spaces(pipes[i]);
        args = quotes_splite(pipes[i], ' ');

        j = 0;
        k = -4;
        argv = (char **)malloc(sizeof(char *) * 10);
        tcmds = (t_cmds *)malloc(sizeof(t_cmds));
        tcmds->heredoc = NULL;

        // redirection = (t_redirection *)malloc(sizeof(t_redirection));
        // ft_initialisation(redirection);

        //printf("/// pipe is -------------- : %s\n" , pipes[i]);
                       // sleep(1);


        red = 0;
        //redirections = NULL;
        //redirection = (t_redirection *)malloc(sizeof(t_redirection));
                                        


        while(args[j])
        {
            //redirection = NULL;
            if (ft_strchr(args[j], '>') || ft_strchr(args[j], '<'))
            {
                redirection = (t_redirection *)malloc(sizeof(t_redirection));
                ft_initialisation(redirection);



                redirection->source_fd = get_source_fd(args[j], redirection);
                if (args[j] && ft_strchr(args[j], '&') && ft_strchr(args[j], '-'))
                {
                    redirection->close = 1;
                }
                else if (ft_strchr(args[j], '&') && args[j + 1] && !is_number(args[j + 1]))
                    redirection->destination_fd = ft_atoi(args[j + 1]);       
                else if (args[j] && args[j + 1])
                    redirection->file = checking_dollar((args[j + 1]) ? args[j + 1] : NULL, params);
                redirection->type = get_type(args[j]);
                if (get_heredoc(redirection, tcmds) == 0)
                    return (0);
                if (args[j + 1])
                    j++;
                k = j;
                list_redi = ft_listnew(redirection);
                ft_lstadd1(&redirections, list_redi);
                redirection = NULL;
                red++;
            }
            if (j != k)
            {
                if (ft_strchr(args[j], '$'))
                    args[j] = checking_dollar(args[j], params);
                argv[a] = args[j];
                a++;
            }
            j++;
        }


        //ft_putendl("je suis ici *** 111 *** 410 sh.c");

       
        argv[a] = NULL;
        tcmds->argv = argv;
        tcmds->i = i;

        tcmds->redirections = redirections;
        //redirection = NULL;
        redirections = NULL;
        
        a = 0;
        list = ft_listnew(tcmds);    
        ft_lstadd1(lst, list);
        i++;
    }
    return (1);
}

int        ft_separation(t_list **lst, char *read, t_params *params)  
{
    char **pipes;

    t_cmds *cmd;
    pipes = quotes_splite(read, '|');


    int i = 0;
    if (ft_getargs(pipes, lst, params) == 0)
        return (0);
    return (1);
}

int        handler_reads(char *read, t_list **lst , t_params *params)
{

    if ((read = ft_add_space(read)))
    {

        if (ft_separation(lst, read, params) == 0)
            return (0);
    }
    return (1);
}

int        splite_semi(char *read, t_list **lst, t_params *params)
{
    int i;
    i = 0;
    char **semicolone = NULL;
    t_list *semicolones = NULL;

    //semicolone = (char **)malloc(sizeof(char *) * 10);
    params->semicolones = NULL;
    semicolone = quotes_splite(read, ';');
    while (semicolone[i])
    {
        if (handler_reads(semicolone[i], lst, params) == 0)
            return (0);
        
        params->lst = *lst;
        manage_sh1(params);
        // semicolones = ft_listnew(lst);
        // ft_lstadd1(&params->semicolones, semicolones);////ft_lstadd_2 
        i++;
    }
    return (1);          
}

void    sh(t_params *params)
{
    char *read;
    t_list *lst;
    t_cmds *cmd = NULL;
   
    lst = NULL;
    params->semicolones = NULL;
    while ("21sh")
    {
        ft_putstr("$> ");
        read = ft_read(read);
        if (splite_semi(read, &lst, params) == 0)
            continue ;
        free(lst);
        lst = NULL;
        //manage_sh(params);
    }
}

int		main(int ac, char **av, char **env)
{
    t_params *params;
    params = (t_params*)malloc(sizeof(t_params));

    params->envs = 0;

    get_environnement(params, env);
    sh(params);
    //ls | cat > file; ls
	//execve_child(exec , env, "/bin/ls");
	return 0;
}
