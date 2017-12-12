# :christmas_tree: Advent of Code 2017 :christmas_tree:

My solutions to the [Advent of Code 2017](http://adventofcode.com/2017) challenges.

This year, I shall be attempting to complete the challenges in C++ using the new [xeus-cling](https://blog.jupyter.org/interactive-workflows-for-c-with-jupyter-fe9b54227d92) C++ kernel for jupyter notebooks. Weekend challenges will be in plain C++ as `xeus-cling` currently only has a linux installer. Where that fails / I run out of time, I will probably fall back to using Python.

Things I've learnt about using `xeus-cling`:
- Once a variable / function / class has been defined, it cannot be redefined without restarting the kernel. So if you make a change to a function, you'll need to restart the kernel to recompile it. This means I have ended up restarting the kernel pretty much constantly.
- Seg faults cause the kernel to die. A dead kernel means there is no chance of getting a backtrace to diagnose these, so I have sometimes resorted to compiling my code in a separate `.cpp` file and using `gdb` to find these bugs.
- `auto` can occasionally be temperamental - it seems to work best to define individual functions in their own cells.
- The notebook is great for playing around with things *as long as* remember not to define variables in global scope (and therefore don't have to keep restarting the kernel).
