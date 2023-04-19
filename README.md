# pipex
### Final Grade: [![kdaniely's 42 pipex Score](https://badge42.vercel.app/api/v2/cldiw2g0k01220fl8ferid3xf/project/3018431)](https://github.com/JaeSeoKim/badge42)

Pipex is a project from 42 School that involves simulating the functionality of the shell command pipeline. The goal of this project is to take two commands and their arguments as input, and then create a pipeline between them by executing one command and redirecting its output to the input of the next command.

## Usage

To use the pipex program, run it with four arguments:

```bash
./pipex file1 cmd1 ... cmdn file2
```
Where file1 is the input file, cmdi is the 'i'-th command and its arguments, and file2 is the output file. The program will then execute cmd1 < file1 and redirect its output to cmdn > file2, effectively creating a pipeline between the two commands.

```bash
./pipex here_doc limiter cmd1 ... cmdn file1
```
Where limiter is delimiter for here_doc, and other is the same as above.

## Features

| Feature | Status |
:-----------: | :-----------: |
| Multiple commands | ✅ |
| Return Value of Last Command | ✅  |
| here_doc | ✅  |

## Algorithm

To implement pipex, we can use the `fork`, `execve`, `pipe`, and `dup2` system calls. We can create multiple child processes, one for each command, and then connect them with a pipe. The first child process will execute **cmd1** and redirect its output to the write end of the pipe. The second child process will execute **cmd2** and read its input from the read end of the pipe and redirect its output to the write end of another pipe. This will continue until all commands are executed. Finally, the parent process will wait for all child processes to complete and then exit.
