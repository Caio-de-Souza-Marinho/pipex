*This project has been created as part of the 42 curriculum by caide-so, lsilva-x.*

# pipex

## Description

**pipex** is a C project from the 42 school curriculum that reproduces the behavior of Unix shell pipes. The goal is to understand and implement the mechanism behind the `|` (pipe) operator by using system calls such as `fork`, `pipe`, `dup2`, and `execve`.

The mandatory part replicates the following shell behavior:

```sh
< file1 cmd1 | cmd2 > file2
```

The bonus part extends this to support **multiple pipes** and **here_doc** (`<<` / `>>`):

```sh
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
cmd << LIMITER | cmd1 >> file
```

### How it works

The program forks one child process per command. Each child sets up its stdin/stdout using `dup2` — reading from the previous pipe and writing to the next — then executes the command via `execve`. The parent process manages pipe file descriptors and waits for all children to finish.

---

## Instructions

### Requirements

- GCC or compatible C compiler
- `make`
- A Unix-based system (Linux / macOS)

### Compilation

Clone the repository and build with `make`:

```sh
git clone <your-repo-url> pipex
cd pipex
make        # builds the mandatory part
make bonus  # builds the bonus part (multiple pipes + here_doc)
```

To remove object files:
```sh
make clean
```

To remove everything including the binary:
```sh
make fclean
```

To recompile from scratch:
```sh
make re
```

### Usage

**Mandatory:**
```sh
./pipex file1 "cmd1" "cmd2" file2
```

**Examples:**
```sh
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
```

**Bonus — multiple pipes:**
```sh
./pipex file1 "cmd1" "cmd2" "cmd3" file2
```

**Bonus — here_doc:**
```sh
./pipex here_doc LIMITER "cmd1" "cmd2" file
```
In here_doc mode, the program reads from stdin until the `LIMITER` string is entered, and appends the output to `file` instead of truncating it.

### Memory check

A `leakfull` Makefile rule is available to run the program under Valgrind:

```sh
make leakfull
```

---

## Project Structure

```
pipex/
├── main.c              # Entry point (mandatory)
├── main_bonus.c        # Entry point (bonus)
├── init.c              # Struct initialization and command parsing
├── forks.c             # Pipeline execution and process forking
├── find_path.c         # Command path resolution via PATH env
├── parse_args.c        # Command string tokenizer (handles quotes)
├── errors.c            # Error handling and cleanup
├── close.c             # Memory freeing utilities
├── heredoc_bonus.c     # here_doc input handling (bonus)
├── pipex.h             # Shared header (mandatory)
├── pipex_bonus.h       # Shared header (bonus)
├── Makefile
└── libft/              # Personal C library
```

---

## Resources

### Documentation & References

- [`pipe(2)` — Linux man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [`fork(2)` — Linux man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [`execve(2)` — Linux man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [`dup2(2)` — Linux man page](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [`waitpid(2)` — Linux man page](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [Unix Processes in C — CodeVault (YouTube playlist)](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
- [File Descriptors & Redirection — GNU libc manual](https://www.gnu.org/software/libc/manual/html_node/Redirecting-I_002fO.html)

### AI Usage

AI (Claude) was used in the following ways during this project:

- **Understanding concepts**: asking for plain-language explanations of `pipe`, `fork`, `dup2`, and process synchronization to complement the man pages.
- **Debugging**: describing unexpected behavior (e.g., processes hanging, output not appearing) and getting suggestions on where to look — all fixes were understood and applied manually.
- **Code review**: asking for feedback on function structure and potential edge cases (e.g., unclosed file descriptors, leaks in error paths).
- **README**: drafting the initial structure of this file.

All AI-generated suggestions were reviewed, tested, and rewritten as needed. No code was copy-pasted without full understanding.
