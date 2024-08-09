/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:01:16 by chuhlig           #+#    #+#             */
/*   Updated: 2024/08/09 19:07:31 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	echo(char **av)
{
	int	i;
	int	f;

	i = 1;
	if (av[1][0] == '\0')
	{
		write(1, "\n", 1);
		return (1);
	}
	if (ft_strcmp(av[1], "-n"))
	{
		i++;
		f = 1;
	}
	while (av[i])
	{
		write(1, &av[1], ft_strlen(av[i]));
		i++;
	}
	if (f)
		write(1, "\n", 1);
	return (0);
}
// Und args wären bei
// echo Hello World
// dann
// echo, Hello und World 


// Die Builtins haben bitte int als return type. 0 = Success, 1 = Error usw.
// Als Parameter kann ich dir die das hier geben:
// char **args
// Aufpassen: args[0] ist der Name des Commands.
// t_env *env
// Hier hast du alle Variablen drin.
// Schau dir dafür am besten env.h an.



// 2-G-4:~ chuhlig$ echo -n hello
// hello2-G-4:~ chuhlig$ echo test -n hello
// test -n hello
   


// minishell % echo -n "Das ist"
// echo -n " ein Beispiel"
// echo " für echo -n."

// 2-G-4:~ chuhlig$ echo 'hello world'
// hello world
// 2-G-4:~ chuhlig$ echo hello'world'
// helloworld
// 2-G-4:~ chuhlig$ echo hello""world
// helloworld
// 2-G-4:~ chuhlig$ echo ''

// 2-G-4:~ chuhlig$ echo "$PWD"
// /Users/chuhlig
// 2-G-4:~ chuhlig$ echo '$PWD'
// $PWD
// 2-G-4:~ chuhlig$ echo "aspas ->'"
// aspas ->'
// 2-G-4:~ chuhlig$ echo "aspas -> ' "
// aspas -> ' 
// 2-G-4:~ chuhlig$ echo 'aspas ->"'
// aspas ->"
// 2-G-4:~ chuhlig$ echo 'aspas -> " '
// aspas -> " 
// 2-G-4:~ chuhlig$ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<"
// > >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<
// 2-G-4:~ chuhlig$ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'
// > >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<
// 2-G-4:~ chuhlig$ echo "exit_code ->$? user ->$USER home -> $HOME"
// exit_code ->0 user ->chuhlig home -> /Users/chuhlig
// 2-G-4:~ chuhlig$ echo 'exit_code ->$? user ->$USER home -> $HOME'
// exit_code ->$? user ->$USER home -> $HOME
// 2-G-4:~ chuhlig$ echo "$"
// $
// 2-G-4:~ chuhlig$ echo '$'
// $
// 2-G-4:~ chuhlig$ echo $
// $

// 2-G-4:~ chuhlig$ echo "test" -n hello
// test -n hello
// 2-G-4:~ chuhlig$ echo -n "test" -n hello
// test -n hello2-G-4:~ chuhlig$ echo -n "test" echo -n hello
// test echo -n hello2-G-4:~ chuhlig$ 



// 2-G-4:~ chuhlig$ echo -n "test1 test2" test3
// test1 test2 test32-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n " test1 test2 " 'test3 '
//  test1 test2  test3 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n test1test2
// test1test22-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo test1 -n
// test1 -n
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo "test1 -n"
// test1 -n
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -n test1
// test12-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -n -n -n -n test1
// test12-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -
// -
// 2-G-4:~ chuhlig$ echo --
// --
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo "  -nn "
//   -nn 
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo "-n test1 -n test2"
// -n test1 -n test2
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo "test1 -n test2"
// test1 -n test2
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo ~42
// ~42
// 2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -n -nasd
// -nasd2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -n -n-nnnnn
// -n-nnnnn2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -nnnnnnn -n -nnn -nnnnn -n-n
// -n-n2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain
// feel my pain2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo -n -n -n-n
// -n-n2-G-4:~ chuhlig$ 
// 2-G-4:~ chuhlig$ echo "'totally logical'"
// 'totally logical'
// 2-G-4:~ chuhlig$ echo 'totally logical'
// totally logical
// 2-G-4:~ chuhlig$ echo ''totally logical''
// totally logical
// 2-G-4:~ chuhlig$ echo ""'totally logical'""
// totally logical

// 2-G-4:~ chuhlig$ eCho

// 2-G-4:~ chuhlig$ eChO

// 2-G-4:~ chuhlig$ eCHO

// 2-G-4:~ chuhlig$ ECHO
int	pwd_builtin(void)
{
	char	cwd[1028];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}