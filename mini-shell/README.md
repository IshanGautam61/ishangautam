# Mini Shell (msh)

A lightweight UNIX-like shell written in C.  
It supports executing system commands, maintaining history, and tracking process IDs.

#Features
- Execute system commands via `fork`, `execvp`, `waitpid`
- Command history (last 15 commands)
- PID history tracking
- Built-in commands: `cd`, `history`, `pidhistory`, `exit`

#Technologies
- C
- Linux system calls

#Build & Run
```bash
cd mini-shell/src
gcc shell.c -o msh
./msh
