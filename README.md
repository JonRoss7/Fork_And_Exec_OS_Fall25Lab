# Fork_And_Exec_OS_Fall25Lab

This project implements several demo programs to practice UNIX process management concepts using `fork`, `exec`, `pipe`, and `wait`.

## Contents
- `fork_demo.c` — demonstrates process creation with `fork()`.
- `exec_demo.c` — demonstrates replacing a process image with `execvp()`.
- `pipe_demo.c` — demonstrates one-way communication using a pipe (`parent → child`).
- `pipeline_demo.c` — demonstrates a two-process pipeline (`ls | grep .c`).
- `zombie_demo.c` — demonstrates zombie processes when a parent delays `wait()`.

All programs are built with CMake.

---

## Challenges Faced
1. Missing `main` error — forgot to define `main` in one of the demo files during compilation.
2. Output confusion with pipes — debug messages from child1 were redirected into the pipe instead of the terminal.
3. Double-fork issue — both parent and child1 were calling the second `fork()` in `pipeline_demo`, breaking the process tree.
4. Zombie visibility — zombies disappeared too quickly to observe with `ps`, requiring adjusted timing or internal `system("ps -l")`.
5. File descriptor handling — forgetting to close the unused ends of pipes led to hangs or incomplete output.
6. CMake setup — errors from not adding executables correctly, later fixed by keeping `set(SOURCES ...)` and individual `add_executable` calls.

---

## Known Issues
- Exact order of messages may vary due to process scheduling (this is expected behavior in concurrent programs).
- Programs assume standard UNIX environment with `ls`, `grep`, and `wc` available in `PATH`.
