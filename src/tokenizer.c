/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:55:50 by chuhlig           #+#    #+#             */
/*   Updated: 2024/07/22 14:18:02 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

// char	*ft_strncpy(char *dst, const char *src, size_t n)
// {
// 	char	*start;

// 	start = dst;
// 	while (n-- > 0 && *src)
// 		*dst++ = *src++;
// 	while (n-- > 0)
// 		*dst++ = '\0';
// 	return (start);
// }
char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

void	print_token(t_token *token)
{
	if (token->type == STRING_TOKEN)
	{
		printf("STRING_TOKEN: %s\n", token->content.string);
	}
	else if (token->type == REDIR_TOKEN)
	{
		printf("REDIR_TOKEN: %d\n", token->content.redir_type);
	}
	else if (token->type == PIPE_TOKEN)
	{
		printf("PIPE_TOKEN\n");
	}
	else if (token->type == NEWLINE_TOKEN)
	{
		printf("NEWLINE_TOKEN\n");
	}
}

//s[i] should be right bc i wanna start at specific pos
void	conditional_print(char *string, int start_of_string, int i, int offset, t_token **token_list)
{
	char	*line;
	int		len;

	len = i + offset - start_of_string + 1;
	if (len > 0)
	{
		line = (char *)malloc(len);
		if (!line)
		{
			exit(EXIT_FAILURE);
		}
		ft_strncpy(line, string + start_of_string, len);
		line[len] = '\0';
		while (*line == ' ' || *line == '\t' || *line == '\0')
			line++;
		if (*line != '\0')
		{
			*token_list = new_str_token(line, *token_list, NULL);
			print_token(*token_list);
		}
		// free(line);
	}
}

void	tokenizer(char *s, t_token **token_list)
{
	char	*quotes;
	char	quote_check;
	// char	c;
	int		start_of_string;
	int		ignore_space;
	int		i;

	quotes = "\"\'";
	quote_check = '\0';
	start_of_string = 0;
	ignore_space = 0;
	i = 0;
	if (!s || !*s)
		return ;
	while (s[i] && s)
	{
		// c = s[i];
		// if (!ignore_space && (c == '|' || c == '\n' || c == '<' || c == '>'))
		if (!ignore_space && (s[i] == '|' || s[i] == '\n' || s[i] == '<' || s[i] == '>'))
		{
			conditional_print(s, start_of_string, i, 0, token_list);
			// if ((c == '<' || c == '>') && s[i + 1] == c)
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
			{
				// if (c == '<')
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_LIMITER,
							*token_list, NULL);
				else
					*token_list = new_redir_token(OUTPUT_APPEND,
							*token_list, NULL);
				print_token(*token_list);
				i++;
			}
			else
			{
				// if (c == '<')
				if (s[i] == '<')
					*token_list = new_redir_token(INPUT_FILE,
							*token_list, NULL);
				// else if (c == '|')
				else if (s[i] == '|')
					*token_list = new_token(PIPE_TOKEN, *token_list, NULL);
				// else if (c == '\n')
				else if (s[i] == '\n')
					*token_list = new_token(NEWLINE_TOKEN, *token_list, NULL);
				else
					*token_list = new_redir_token(OUTPUT_OVERRIDE,
							*token_list, NULL);
				print_token(*token_list);
				// i++;
			}
			start_of_string = i + 1;
		}
		// else if (ignore_space && c == quote_check)
		// mew update for the sting part 18.07
		else if (ignore_space && s[i] == quote_check)
		{
			quote_check = '\0';
			ignore_space = 0;
		}
		// else if (!ignore_space && ft_strchr(quotes, c))
		else if (!ignore_space && ft_strchr(quotes, s[i]))
		{
			quote_check = s[i];
			ignore_space = 1;
		}
		// else if ((!ignore_space && (c == '\0' || c == ' ' || c == '\t')) || i == ft_strlen(s) - 1)
		if ((!ignore_space && (s[i] == '\0' || s[i] == ' ' || s[i] == '\t')) || i == ft_strlen(s) - 1)
		{
			if (s[i + 1] == '\0')
				i++;
			conditional_print(s, start_of_string, i, 0, token_list);
			start_of_string = i + 1;
		}
		// else if (!ignore_space && ft_strchr(quotes, c))
		// else if (!ignore_space)
		// {
		// 	if(ft_strchr(quotes, s[i]))
		// 	{
		// 		quote_check = s[i];
		// 		ignore_space = 1;
		// 	}
		// 	else if (s[i] == '\0' || s[i] == ' ' || s[i] == '\t' || i == ft_strlen(s) - 1)
		// 	{
		// 		if (s[i + 1] == '\0')
		// 			i++;
		// 		conditional_print(s, start_of_string, i, 0, token_list);
		// 		start_of_string = i + 1;
		// 	}
		// }
		// else if (ignore_space && (s[i] == quote_check || s[i + 1] == '\0'))// secon part out of while loop?
		// {
		// 	quote_check = '\0';
		// 	ignore_space = 0;
		// 	conditional_print(s, start_of_string, i, 0, token_list);
		// 	start_of_string = i + 1;
		// }
		i++;
	}
}

///s[i] != ' '
//mazbe remove c
// why handle space?
//readline delete mazbe?

// errors today if i change the con print cond removing *line == '\0'
// ./minishell 
// Minishell $ test
// Minishell $ idk
// Minishell $ why you idiot a re doing nothing
// zsh: segmentation fault  ./minishell
// chuhlig@1-E-9 minishell % ./minishell
// Minishell $ a
// Minishell $ aaa
// Minishell $ aaaaaaaaaaaaaa
// Minishell $ aa aa
// zsh: segmentation fault  ./minishell

// also some space reconizing is wrong
//also the part with cond &s[i] or just s seem f up
//tested different strncpy still errors
// removed anoying brackets to short it
//added pipe and  \n token
// string still not works fine mazybe readline and input understanding

// error with extra condition:
// ./minishell
// Minishell $ test
// STRING_TOKEN: �
// =================================================================
// ==66482==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000002835 at pc 0x00010bb02c68 bp 0x7ffee41034b0 sp 0x7ffee41034a8
// READ of size 1 at 0x602000002835 thread T0
//     #0 0x10bb02c67 in tokenizer tokenizer.c:91
//     #1 0x10bb00c66 in repl repl.c:30
//     #2 0x10bb00684 in main main.c:19
//     #3 0x7fff733a7cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

// 0x602000002835 is located 0 bytes to the right of 5-byte region [0x602000002830,0x602000002835)
// allocated by thread T0 here:
//     #0 0x10bba517d in wrap_malloc+0x9d (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4917d)
//     #1 0x10bb38c44 in xmalloc+0x8 (libreadline.8.dylib:x86_64+0x25c44)
//     #2 0x10bb16096 in readline_internal_teardown+0xfa (libreadline.8.dylib:x86_64+0x3096)
//     #3 0x10bb15bb4 in readline+0x5b (libreadline.8.dylib:x86_64+0x2bb4)
//     #4 0x10bb00ba3 in repl repl.c:25
//     #5 0x10bb00684 in main main.c:19
//     #6 0x7fff733a7cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

// SUMMARY: AddressSanitizer: heap-buffer-overflow tokenizer.c:91 in tokenizer
// Shadow bytes around the buggy address:
//   0x1c04000004b0: fa fa fd fa fa fa fd fa fa fa fd fa fa fa fd fa
//   0x1c04000004c0: fa fa fd fa fa fa fd fa fa fa fd fd fa fa fd fd
//   0x1c04000004d0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
//   0x1c04000004e0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
//   0x1c04000004f0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
// =>0x1c0400000500: fa fa 00 00 fa fa[05]fa fa fa 00 04 fa fa 05 fa
//   0x1c0400000510: fa fa 05 fa fa fa fa fa fa fa fa fa fa fa fa fa
//   0x1c0400000520: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
//   0x1c0400000530: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
//   0x1c0400000540: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
//   0x1c0400000550: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
// Shadow byte legend (one shadow byte represents 8 application bytes):
//   Addressable:           00
//   Partially addressable: 01 02 03 04 05 06 07 
//   Heap left redzone:       fa
//   Freed heap region:       fd
//   Stack left redzone:      f1
//   Stack mid redzone:       f2
//   Stack right redzone:     f3
//   Stack after return:      f5
//   Stack use after scope:   f8
//   Global redzone:          f9
//   Global init order:       f6
//   Poisoned by user:        f7
//   Container overflow:      fc
//   Array cookie:            ac
//   Intra object redzone:    bb
//   ASan internal:           fe
//   Left alloca redzone:     ca
//   Right alloca redzone:    cb
//   Shadow gap:              cc
// ==66482==ABORTING

// othere error currently
//  test
// STRING_TOKEN: 
// minishell(86892,0x111ae2dc0) malloc: *** error for object 0x7fedf3200014: pointer being freed was not allocated
// minishell(86892,0x111ae2dc0) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./minishell
// chuhlig@1-E-9 minishell % ./minishell
// Minishell $ "test"
// Minishell $ "testtest"
// Minishell $ "test           test"
// Minishell $ te
// STRING_TOKEN: `
// minishell(86928,0x114a76dc0) malloc: *** error for object 0x7fcaa8d04f27: pointer being freed was not allocated
// minishell(86928,0x114a76dc0) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./minishell
// chuhlig@1-E-9 minishell % ./minishell
// Minishell $ a
// STRING_TOKEN: 
// Minishell $ a
// zsh: segmentation fault  ./minishell
// chuhlig@1-E-9 minishell % ./minishell
// Minishell $ a
// STRING_TOKEN: ^
// minishell(86958,0x11c50adc0) malloc: *** error for object 0x7fb24a800011: pointer being freed was not allocated
// minishell(86958,0x11c50adc0) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./minishell
// chuhlig@1-E-9 minishell % ./minishell
// Minishell $ a
// zsh: segmentation fault  ./minishell

///do i need to update after cont print i?
// end quote not works atm and have to check the lenth
// how to handle not in quote text command
// space generell need to be fixed

/// 1425 2207
// Minishell $ test test "ters"
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters"
// Minishell $ test test "ters
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters
// Minishell $ test test "ters " "a
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a
// Minishell $ |||| <><> <><> <<< >>>> |||
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: 
// STRING_TOKEN: <
// REDIR_TOKEN: 0
// STRING_TOKEN: >
// REDIR_TOKEN: 2
// STRING_TOKEN: <
// REDIR_TOKEN: 0
// STRING_TOKEN: >
// REDIR_TOKEN: 2
// STRING_TOKEN: ^
// STRING_TOKEN: <
// REDIR_TOKEN: 0
// STRING_TOKEN: >
// REDIR_TOKEN: 2
// STRING_TOKEN: <
// REDIR_TOKEN: 0
// STRING_TOKEN: >
// REDIR_TOKEN: 2
// STRING_TOKEN: ^
// STRING_TOKEN: <
// REDIR_TOKEN: 1
// STRING_TOKEN: <
// REDIR_TOKEN: 0
// STRING_TOKEN: �
// STRING_TOKEN: >
// REDIR_TOKEN: 3
// STRING_TOKEN: >
// REDIR_TOKEN: 3
// STRING_TOKEN: 
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: |
// PIPE_TOKEN
// STRING_TOKEN: 
// Minishell $ test test "ters " "a asddddsa asdss
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss
// Minishell $ test test "ters " "a asddddsa asdss ' test
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss ' test
// Minishell $ test test "ters " "a asddddsa asdss ' test"
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss ' test"
// Minishell $ test test "ters " "a asddddsa asdss ' test
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss ' test
// Minishell $ test test "ters " "a asddddsa asdss ' te'
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss ' te'
// Minishell $ test test "ters " "a asddddsa asdss ' te'" 'tes
// STRING_TOKEN: test 
// STRING_TOKEN: test 
// STRING_TOKEN: "ters " 
// STRING_TOKEN: "a asddddsa asdss ' te'" 
// STRING_TOKEN: 'tes
// Minishell $   
// STRING_TOKEN: �
// STRING_TOKEN: ��D�
// minishell(95695,0x10c1addc0) malloc: *** error for object 0x7f844c004407: pointer being freed was not allocated
// minishell(95695,0x10c1addc0) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./minishell
// chuhlig@1-E-11 minishell % ./minishell
// Minishell $   
// STRING_TOKEN: �
// STRING_TOKEN: �
// minishell(95853,0x118e33dc0) malloc: *** error for object 0x7fe72b405977: pointer being freed was not allocated
// minishell(95853,0x118e33dc0) malloc: *** set a breakpoint in malloc_error_break to debug
// zsh: abort      ./minishell
// chuhlig@1-E-11 minishell %   test
// chuhlig@1-E-11 minishell %   pwd 
// /Users/chuhlig/Desktop/minishell
// chuhlig@1-E-11 minishell % ./minishell
// Minishell $  test
// STRING_TOKEN: 
// STRING_TOKEN: test
// Minishell $   test
// STRING_TOKEN: `
// STRING_TOKEN: 
// STRING_TOKEN: test
// Minishell $ 