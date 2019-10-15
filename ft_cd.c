#include "sh.h"

void            save_pwd(t_params *params, char *pwd)    //   /we work here inchaa allah 
{
    t_list      *envs;
	t_environnement	*env;
    char **old;
    int is;

	envs = params->environnement;
    is = 0;
    while (envs)
    {
        env = envs->content;
        if (!ft_strcmp(env->key, pwd))
        {
            is = 1;
            env->value ? free(env->value) : 0;
            env->value = getcwd(NULL, 0);
            break ;
        }
        envs = envs->next;
    }
    if (!is)
    {
        old = (char **)malloc(sizeof(char *) * 3);
        old[0] = NULL;
        old[1] = pwd;
        old[2] = getcwd(NULL, 0);
        old[3] = NULL;
        ft_setenv(old, params);
    }
}

int				stats_dir(char *path)
{
	struct stat fstat;

	stat(path, &fstat);
	if ((S_ISDIR(fstat.st_mode)) && ((access(path, X_OK) == -1)))
	{
		ft_putstr(path);
		ft_putendl(": Permission denied.");
		return (0);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(path);
		return (0);
	}
	if ((!access(path, F_OK)) && !(S_ISDIR(fstat.st_mode)))
	{
		ft_putstr(path);
		ft_putendl(": Not a directory.");
		return (0);
	}
	return (1);
}

void            old_dir(t_params *params)
{
    t_list *envs;
    t_environnement *env;
    char *tmp;
    int is;

    is = 1;
    envs = params->environnement;
    while (envs)
    {
        env = envs->content;
        if (!ft_strcmp(env->key, "OLDPWD"))
        {
            is = 0;
            tmp = getcwd(NULL, 0);
            chdir(env->value);
            free(env->value);
            env->value = ft_strdup(tmp);
            free(tmp);
            break ;
        }
        envs = envs->next;
    }
    if (is)
        ft_putendl(": No such file or directory.");
}

void			change_dir(char **read, t_params *params)
{
	static char	*pwd;
	char		*last_pwd;
    t_list      *envs;
	t_environnement	*env;

	envs = params->environnement;

	if (read[1] && !ft_strcmp(read[1], "-"))
		old_dir(params);
    
	else if (!read[1])
	{   
       // pwd = getcwd(NULL, 0);
        while(envs)
        {
            env = envs->content;
            if (!ft_strcmp(env->key, "HOME"))
            {
                //last_pwd = env->value;
                save_pwd(params, ft_strdup("OLDPWD"));
                chdir(env->value);
                save_pwd(params, ft_strdup("PWD"));
            }
            envs = envs->next;
        }
	}
	else if (stats_dir(read[1]))
	{
        save_pwd(params, ft_strdup("OLDPWD"));
		chdir(read[1]);
        save_pwd(params, ft_strdup("PWD"));
	}
  //  new_pwd(params);
}