# Learn about the `open` system call

Here is how I used BPF and kprobes to learn about the `open` system call.

## Requirements

- You have a ext4 filesystem
- bpftrace is installed
- You're using Linux 5.8 and have the headers installed
- You have [launch-buddies](https://github.com/pmalmgren/launch-buddies) compiled, optionally you can change the PID filter to filter on comm instead

## Following along

Download and install the Linux kernel source. Open the file `fs/open.c` and go to the `do_sys_open` definition.

Compile the `open.c` program which will open a file specified by the first command line argument.

Launch the bpftrace script and open at the same time. You'll either need to grant `CAP_BPF` capabilities to your user, or run the profiler as root with `sudo`.

## Running

```
$ sudo lb "./open /tmp/doesntexist/file" "./open-trace.bt"
...

link_path_walk(filename=/tmp/doesntexist/file)
walk_component(nd->path=/, flags=WALK_MORE)
dcache hit: lookup_fast on tmp
walk_component(nd->path=tmp, flags=WALK_MORE)
dcache hit: lookup_fast on doesntexist
open: No such file or directory
Child finished, killing profiler...

Profiler finished, exiting...
```
