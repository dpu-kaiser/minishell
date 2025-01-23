/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuhlig <chuhlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:37:33 by chuhlig           #+#    #+#             */
/*   Updated: 2025/01/23 17:37:13 by chuhlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Code Review
init.c
This file initializes the terminal settings and signal handling. It looks correct, but consider checking if tcgetattr and tcsetattr return errors and handle them appropriately.

C

static void init_terminal(void) {
    struct termios term;

    if (tcgetattr(0, &term) == -1) {
        perror("tcgetattr failed");
        exit(EXIT_FAILURE);
    }
    term.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, TCSANOW, &term) == -1) {
        perror("tcsetattr failed");
        exit(EXIT_FAILURE);
    }
}
env.c
In the getenvlst function, modifying the environment variable string directly can lead to undefined behavior. Instead, consider using strdup to make a copy of the string.

C

void getenvlst(t_env **env, char **en) {
    char *tmp;
    int i;
    t_env *current;

    i = 0;
    while (en[i] != NULL) {
        tmp = ft_strchr(en[i], '=');
        if (!tmp) continue;
        *tmp = '\0';
        current = malloc(sizeof(t_env));
        if (!current) exit(EXIT_FAILURE); // Handle malloc failure
        current->name = ft_strdup(en[i]);
        current->value = ft_strdup(tmp + 1);
        current->next = *env;
        *env = current;
        i++;
    }
}
repl.c
The repl function looks good, but consider checking the readline return value for NULL and handling memory allocation errors.

error.c
The command_not_found_error function should ensure correct file descriptors:

C

void command_not_found_error(char *cmd) {
    ft_printf("%s:", cmd);
    ft_putstr_fd(" command not found", 2); // file descriptor 2 for stderr
    ft_printf("\n");
}
new_node.c
The new_cmd_node function calls free(redirs) but then returns NULL without freeing the allocated node.

C

t_node *new_cmd_node(char **args, t_redirection redirs[2], t_list *create_files) {
    t_node *node = new_node(CMD_NODE);
    if (!node) return NULL;
    node->content.cmd.args = args;
    if (redirs) {
        node->content.cmd.redirs[0] = redirs[0];
        node->content.cmd.redirs[1] = redirs[1];
        node->content.cmd.create_files = create_files;
        free(redirs);
        redirs = NULL;
        return node;
    }
    free(node); // Free the allocated node
    return NULL;
}
free_node.c
In free_cmd_node, ensure you free both redirections correctly.

C

static void free_cmd_node(t_node *node) {
    int i = 0;
    while (node->content.cmd.args && node->content.cmd.args[i]) {
        free(node->content.cmd.args[i]);
        i++;
    }
    free(node->content.cmd.args);
    if (node->content.cmd.redirs[0].type && node->content.cmd.redirs[0].specifier)
        free(node->content.cmd.redirs[0].specifier);
    if (node->content.cmd.redirs[1].type && node->content.cmd.redirs[1].specifier)
        free(node->content.cmd.redirs[1].specifier);
}
Summary
The provided code generally looks well-structured, but there are some areas where error checking and memory management could be improved. Implementing these suggestions will help make the code more robust and easier to maintain. If you have any specific concerns or files you would like to focus on, please let me know!


anything else?
The initial analysis covered some key areas and potential improvements in the provided Makefile and source files. Here are a few more specific suggestions for certain files to ensure robustness and maintainability:

Additional Suggestions
env.c (Handling Environment Variables):
Error Handling: Add error handling for ft_strdup and malloc to ensure memory allocation was successful.
Environment String Handling: Avoid modifying the original environment strings directly.
C

void getenvlst(t_env **env, char **en) {
    char *tmp;
    int i;
    t_env *current;

    i = 0;
    while (en[i] != NULL) {
        tmp = ft_strchr(en[i], '=');
        if (!tmp) continue;
        *tmp = '\0';
        current = malloc(sizeof(t_env));
        if (!current || !(current->name = ft_strdup(en[i])) || !(current->value = ft_strdup(tmp + 1))) {
            perror("malloc or strdup failed");
            exit(EXIT_FAILURE);
        }
        current->next = *env;
        *env = current;
        *tmp = '='; // Restore the original string
        i++;
    }
}
repl.c (Read-Evaluate-Print Loop):
Memory Management: Ensure all allocated memory is freed.
Error Handling: Handle potential errors from functions like readline.
C

void repl(const char *prompt, t_env **env, int *promptflag) {
    char *input;
    t_token *token_list;
    t_list *lines;

    (*promptflag)++;
    while (1) {
        input = readline(prompt);
        if (input == NULL) {
            if (*promptflag > 1)
                (*promptflag)--;
            printf("exit\n");
            break;
        }
        if (input[0] == '\0') {
            free(input);
            continue;
        }
        add_history(input);
        token_list = NULL;
        tokenizer(input, &token_list, '\0');
        lines = parse(token_list, env);
        if (lines)
            set_return_code(eval(lines->content, env), env);
        free(input);
        free_tokens(token_list);
        ft_lstclear(&lines, (void (*)(void *))free_node);
    }
}
1 vulnerability detected
get_cmd_path.c (Command Path Resolution):
Error Handling: Ensure errors are correctly handled and resources are freed.
C

static char *get_absolute_cmd_path(char *cmd, t_env *env, int *return_code) {
    char *cur_dir;
    char *result;

    cur_dir = ft_strjoin(env_get(env, "PWD"), "/");
    if (!cur_dir) {
        return error(ENOMEM, cmd, 127, return_code);
    }
    result = ft_strjoin(cur_dir, cmd);
    free(cur_dir);
    if (!result) {
        return error(ENOENT, cmd, 127, return_code);
    }
    if (access(result, F_OK) == -1) {
        free(result);
        return error(ENOENT, cmd, 127, return_code);
    }
    if (access(result, X_OK) == -1) {
        free(result);
        return error(EACCES, cmd, 126, return_code);
    }
    if (is_directory(result)) {
        free(result);
        return error(EISDIR, cmd, 126, return_code);
    }
    return result;
}
General Best Practices:
Consistent Error Handling: Ensure all functions consistently handle errors and free resources appropriately.
Code Comments: Add comments to explain complex logic and improve code readability.
Memory Management: Regularly check for potential memory leaks and ensure all allocated memory is freed.
If you have any specific files or sections you want to dive deeper into, feel free to let me know!


ok ill look over it: now after your analyze it seem tokens are not freed properly what i mean with that we are missing it seems on more free but im not sure where to place it especial when the input is invalid and cant be used properly
It looks like you may need to ensure that tokens are properly freed, especially in cases where the input is invalid. Let's take a look at the relevant parts of the code that handle tokens and ensure that memory is managed correctly.

Token Freeing Logic
To help ensure that tokens are freed properly, let's review the primary functions that deal with token management and identify where additional freeing might be needed.

Tokenizer Function
The tokenizer function creates tokens. If the input is invalid, we should ensure we free any partially created tokens.

C

void tokenizer(char *s, t_token **token_list, char quote_check) {
    int pos = 0;
    int i = -1;
    int f = 0;
    while (s[++i]) {
        if (!f && ft_strchr("|<>\n", s[i]))
            handle_special_chars(s, &i, &pos, token_list);
        else if (f && s[i] == quote_check)
            f = 0;
        else if (!f && ft_strchr("\'\"", s[i])) {
            f = 1;
            quote_check = s[i];
        }
        if ((!f && (ft_isspace(s[i + 1]))) || i == ft_strlen(s) - 1) {
            snap_string_token(s, pos, i, token_list);
            pos = i + 1;
        }
    }
    *token_list = reverse_token_list(*token_list);
}
Free Tokens Function
The free_tokens function should be used to free the entire token list:

C

void free_tokens(t_token *tokens) {
    while (tokens != NULL) {
        t_token *next = tokens->next;
        if (tokens->type == STRING_TOKEN)
            free(tokens->content.string);
        free(tokens);
        tokens = next;
    }
}
Parsing Logic
In the parsing logic, ensure that tokens are freed if an error occurs:

C

t_list *parse(t_token *tokens, t_env **env) {
    t_node *result;

    if (tokens->type == PIPE_TOKEN) {
        free_tokens(tokens); // Free tokens if the first token is invalid
        return NULL;
    } else {
        result = parse_statement(tokens, env);
    }
    if (result == NULL) {
        printf("Parsing error.\n");
        free_tokens(tokens); // Free tokens if parsing fails
    }
    return ft_lstnew(result);
}
Example Fix
Here is a more comprehensive example of how you can ensure tokens are freed correctly in the parse function and the collect_redirs function:

C

t_list *parse(t_token *tokens, t_env **env) {
    t_node *result;

    if (tokens == NULL || tokens->type == PIPE_TOKEN) {
        if (tokens) free_tokens(tokens); // Free tokens if the first token is invalid or NULL
        return NULL;
    }
    result = parse_statement(tokens, env);
    if (result == NULL) {
        printf("Parsing error.\n");
        free_tokens(tokens); // Free tokens if parsing fails
    }
    return ft_lstnew(result);
}

t_redirection *collect_redirs(t_token **tokens, t_env *env, t_list **create_files) {
    t_redirection *result;
    t_token *cur;
    t_minidata data;

    cur = *tokens;
    result = malloc(sizeof(t_redirection) * 2);
    if (result == NULL)
        return free_tokens(*tokens), NULL;
    set_redir(&result[0], 0, NULL, env);
    set_redir(&result[1], 0, NULL, env);
    data.create_files = create_files;
    data.env = env;
    while (cur != NULL) {
        if (cur->type == REDIR_TOKEN && cur->next->type == STRING_TOKEN)
            collect_and_check_redir(result, &cur, &data, tokens);
        else if (cur->type == REDIR_TOKEN)
            return free(result), free_tokens(*tokens), NULL;
        else
            cur = cur->next;
    }
    if (cur && cur->type == REDIR_TOKEN)
        return free(result), free_tokens(*tokens), NULL;
    return result;
}
Summary
By ensuring that tokens are always freed when an error occurs or when they are no longer needed, you can avoid memory leaks and improve the robustness of your shell. If you have specific cases where you suspect tokens are not being freed correctly, please share those, and I can provide more targeted advice!


tokens are never NULL except when i press enter but this is handle in repl and to your free token the problem is with our aproach is that parts of the token will be updated while running like in parser.c
Thank you for the clarification. It seems like the tokens are being updated during parsing, which complicates the token freeing process. Let's ensure that we handle token freeing correctly in all cases, especially when errors occur during parsing.

Reviewing the Token Management
Since tokens are updated during parsing, we need to be careful to free tokens correctly without disrupting the parsing logic. We'll focus on ensuring that tokens are freed appropriately in various scenarios, including error cases.

Parsing Logic and Freeing Tokens
Parser Function: Ensure that tokens are freed if parsing fails.
Free Tokens Helper Function: Improve the free_tokens function to handle partial frees.
Example Fixes
Free Tokens Function
First, let's have a robust free_tokens function that can handle the complete or partial token lists:'

C

void free_tokens(t_token *tokens) {
    t_token *next;
    while (tokens != NULL) {
        next = tokens->next;
        if (tokens->type == STRING_TOKEN && tokens->content.string != NULL) {
            free(tokens->content.string);
        }
        free(tokens);
        tokens = next;
    }
}
Parsing Functions
Next, ensure that the parsing logic properly frees tokens if an error occurs:

parse Function:
C

t_list *parse(t_token *tokens, t_env **env) {
    t_node *result;

    if (tokens == NULL || tokens->type == PIPE_TOKEN) {
        if (tokens) free_tokens(tokens); // Free tokens if the first token is invalid or NULL
        return NULL;
    }
    result = parse_statement(tokens, env);
    if (result == NULL) {
        printf("Parsing error.\n");
        free_tokens(tokens); // Free tokens if parsing fails
    }
    return ft_lstnew(result);
}
parse_statement Function:
C

static t_node *parse_statement(t_token *tokens, t_env **env) {
    t_token *left_side_tokens;

    left_side_tokens = split_at_first(&tokens, PIPE_TOKEN);
    if (left_side_tokens == NULL) {
        free_tokens(tokens); // Free remaining tokens if split fails
        return NULL;
    }
    if (tokens != NULL) {
        t_node *left_node = parse_cmd(left_side_tokens, env);
        t_node *right_node = parse_statement(tokens, env);
        if (left_node == NULL || right_node == NULL) {
            free_tokens(left_side_tokens);
            free_tokens(tokens);
            return NULL;
        }
        return new_pipe_node(left_node, right_node);
    }
    return parse_cmd(left_side_tokens, env);
}
Handling Token Updates
When tokens are updated, ensure that the old parts are freed correctly before being replaced. For example:

C

void update_token(t_token *token, int new_type, char *new_content) {
    if (token->type == STRING_TOKEN && token->content.string != NULL) {
        free(token->content.string);
    }
    token->type = new_type;
    token->content.string = new_content;
}
Summary
By ensuring that tokens are properly freed in all scenarios, including when parsing errors occur and when tokens are updated, you can avoid memory leaks and ensure robust memory management. If you have any specific cases or additional concerns, please let me know!


i never update tokens static char **collect_args(t_token **tokens, t_env **env) { t_token *cur; char **result; int i; t_token *next; cur = *tokens; i = 0; while (cur != NULL && ++i) cur = cur->next; result = malloc(sizeof(char *) * (i + 1)); if (result == NULL) return (free_tokens(*tokens), NULL); cur = *tokens; i = 0; while (cur != NULL && cur->type == STRING_TOKEN) { next = cur->next; if (cur->previous) free_token(cur->previous); result[i] = format_string(cur->content.string, *env, ft_atoi("0")); i++; if (cur->next == NULL) free_token(cur); cur = next; } result[i] = NULL; return (result); } any suggestions for this? static char **collect_args(t_token **tokens, t_env **env) { t_token *cur; char **result; int i; t_token *next; cur = *tokens; i = 0; while (cur != NULL && ++i) cur = cur->next; result = malloc(sizeof(char *) * (i + 1)); if (result == NULL) return (free_tokens(*tokens), NULL); cur = *tokens; i = 0; while (cur != NULL && cur->type == STRING_TOKEN) { next = cur->next; if (cur->previous) free_token(cur->previous); result[i] = format_string(cur->content.string, *env, ft_atoi("0")); i++; if (cur->next == NULL) free_token(cur); cur = next; } result[i] = NULL; return (result); } just take as example input : a and check the hole code for yourself
Let's take a closer look at the collect_args function to ensure that tokens are freed properly and memory is managed correctly. The goal is to collect arguments from tokens, format them, and ensure that all tokens are freed without causing memory leaks or dangling pointers.

Review of collect_args
The function collect_args traverses the token list, collects string tokens, and formats them into an array of arguments. It also attempts to free tokens as it processes them.

Here’s the function with comments and suggestions for improvement:'

C

static char **collect_args(t_token **tokens, t_env **env) {
    t_token *cur;
    char **result;
    int i;
    t_token *next;

    // Count the number of tokens
    cur = *tokens;
    i = 0;
    while (cur != NULL && ++i)
        cur = cur->next;

    // Allocate memory for the result array
    result = malloc(sizeof(char *) * (i + 1));
    if (result == NULL) {
        free_tokens(*tokens); // Free tokens if memory allocation fails
        return NULL;
    }

    // Collect and format string tokens
    cur = *tokens;
    i = 0;
    while (cur != NULL && cur->type == STRING_TOKEN) {
        next = cur->next;
        if (cur->previous)
            free_token(cur->previous); // Free the previous token

        result[i] = format_string(cur->content.string, *env, 0);
        if (result[i] == NULL) { // Check if format_string failed
            free_tokens(next); // Free remaining tokens
            while (i > 0) {
                free(result[--i]);
            }
            free(result);
            return NULL;
        }

        i++;
        if (cur->next == NULL)
            free_token(cur); // Free the current token if it's the last one
        cur = next;
    }
    result[i] = NULL;
    return result;
}
Improvements and Error Handling
Error Handling: Improved error handling by checking if format_string failed and freeing the remaining tokens and allocated memory.
Memory Allocation Check: Ensured that memory allocation failures for result and format_string are handled.
Freeing Tokens: Ensured that tokens are properly freed, including the current token if it's the last one.
Example Input: "a"
For the input "a", the function should create a single argument "a" and ensure that all tokens are freed.

Updated Function
Here’s the updated function with the improvements:

C'

static char **collect_args(t_token **tokens, t_env **env) {
    t_token *cur;
    char **result;
    int i;
    t_token *next;

    // Count the number of tokens
    cur = *tokens;
    i = 0;
    while (cur != NULL && ++i)
        cur = cur->next;

    // Allocate memory for the result array
    result = malloc(sizeof(char *) * (i + 1));
    if (result == NULL) {
        free_tokens(*tokens); // Free tokens if memory allocation fails
        return NULL;
    }

    // Collect and format string tokens
    cur = *tokens;
    i = 0;
    while (cur != NULL && cur->type == STRING_TOKEN) {
        next = cur->next;
        if (cur->previous)
            free_token(cur->previous); // Free the previous token

        result[i] = format_string(cur->content.string, *env, 0);
        if (result[i] == NULL) { // Check if format_string failed
            free_tokens(next); // Free remaining tokens
            while (i > 0) {
                free(result[--i]);
            }
            free(result);
            return NULL;
        }

        i++;
        if (cur->next == NULL)
            free_token(cur); // Free the current token if it's the last one
        cur = next;
    }
    result[i] = NULL;
    return result;
}


tendenziel sollte in collect arg free token until

parse ist das erste was nach token passiert und da wird token zu node umgewandelt