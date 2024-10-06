#ifndef FT_SCHED_H
# define FT_SCHED_H

# define CLONE_VM 0x00000100      // Set if VM shared between processes
# define CLONE_FS 0x00000200      // Set if fs info shared between processes
# define CLONE_FILES 0x00000400   // Set if open files shared between processes
# define CLONE_SIGHAND 0x00000800 // Set if signal handlers and blocked signals shared
# define CLONE_SYSVSEM 0x00002000 // Set if System V SEM_UNDO semantics shared
# define CLONE_THREAD 0x00010000  // Set to add to thread group

int	ft_clone(int (*fn)(void *), void *child_stack, int flags, void *arg);

#endif /* FT_SCHED_H */
