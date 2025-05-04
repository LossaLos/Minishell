# Minishell

## Overview

**Minishell** is a project from [42 School](https://42.fr) that consists of creating a simple shell. It aims to replicate the behavior of Bash or Zsh, focusing on the fundamental mechanisms of process management, parsing, and environment manipulation in Unix-like systems.

This project is an excellent introduction to how shells work internally, providing a deeper understanding of how commands are interpreted and executed.

## Features

- Prompt display that awaits user input.
- Execution of executable binaries using relative or absolute paths.
- Support for built-in commands:
  - `echo` with `-n` option
  - `cd` with relative and absolute paths
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variables handling.
- Pipes (`|`) between commands.
- Redirections:
  - Input `<`
  - Output `>`
  - Append `>>`
  - Heredoc `<<`
- Quotes handling (`'`, `"`)
- Proper signal handling (`Ctrl+C`, `Ctrl+\`, `Ctrl+D`)
- Error management (command not found, permission denied, syntax errors, etc.)

### Compilation

```bash
make
