*This project has been created as part of the 42 curriculum by beciftci.*

# Minishell

An interactive Unix shell in C, built with Koray Mullaoglu. It reads a command line with GNU Readline, parses it, and runs built-ins or external commands.

## Features

- Pipelines, input and output redirection, and heredocs
- Single and double quotes and environment variable expansion
- Built-ins for `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`
- Signal handling for interactive command execution

## Build and run

Use a Linux terminal with a C compiler, Make, and the GNU Readline development headers (on Debian and Ubuntu, `libreadline-dev`).

```sh
make
./minishell
```

In the shell, try `echo hello | wc -c`, then type `exit`.

## Source layout

[parsing](./parsing) reads the command line. [execution](./execution) starts commands and manages pipes, redirections, and signals. [builtins](./builtins) implements commands that belong to the shell itself.
