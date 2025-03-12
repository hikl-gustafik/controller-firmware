# Apps

This directory contains layers as different apps that can be pushed
to the runtime.

**These files are meant to be included as `.cpp` files and they are separated
purely for readability! Treat them as if they were a part of `main.cpp`.**

Apps should not have/need include guards as they should only be included
into `main.cpp` and **DEFINITELY NOT** between each other. If you need
multiple layers to cooperate as one app, have them in a single file.
