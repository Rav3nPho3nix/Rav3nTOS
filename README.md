# Rav3nTOS
My own RTOS.
This RTOS can be run in "software" mode or on an STM32 NUCLEO H533RE.

I decided to first implement all "kernel features" (like tasks, scheduling, semaphores, mutexes, IPC) in "software" mode, then implement the other essential parts (context switching) for each board.

My perception of this project is simple : i will use to the "software" mode to prototype features and applications then implement it on real hardware.

This RTOS is also a great way for me to understand deeply each scheduling algorithm (i will try to implement each one the cleanest way possible, it's a promise ;)).

Currently, my RTOS is in a really early stage, so every modification will only be done on the "software" version. It's much simplier since i can use every C standard library.

# ToDo
- [X] Linker
- [X] Vector table
- [X] Reset Handler
- [X] USART
- [X] SysTick
- [X] Task structure
- [X] Context switching
- [X] Round robin (with priorities)
- [X] Struct for task arguments
- [X] Paused task
- [X] Sleeping task
- [X] Task yield
- [X] Critical sections
- [X] Merge all #define in config.h
- [X] Modifying quantum value while running (for a task that yield for example)
- [X] Semaphores
- [ ] Config file with static assertions
- [ ] Mutexes
- [ ] Communication between tasks
- [ ] Random

# Requirements
- Docker
- Docker compose
- probe-rs
- gdb-multiarch

# Software environment

To simplify compilation and deploiement, i use this list of technologies :
- **Docker** : containe to perform compilation
- **make** : compilation
- **probe-rs** : flashing
- **gdb-multiarch** : debugging

# Setting up Docker image

First, you need to build the Dockerfile into a docker image.
You can modify the content of the Dockerfile to remove unecessary packages to drastically reduce the final image size.

<em>I recommand to set the docker image name as `rav3ntos_dev`, however if you really want to apply another name, you will need to also modify the `image` value inside the `compose.yaml` file.</em>

```bash
docker build --file DOCKER_FILE_NAME -t rav3ntos_dev .
```

# Compilation
Rav3nTOS is compiled using **GNU Make** inside a **Docker** container. By using Docker, every computer can cross compile for all supported platforms.

To change the platform target, you need to modify the Dockerfile packages to install your architecture based gcc.

For example, to compile for an `arm` target, i use :
```bash
gcc-arm-none-eabi
binutils-arm-none-eabi
libnewlib-arm-none-eabi
```

Then, you also need to modify the following Makefile parameters to match your installed packages :
```bash
ARCH_DIR    # Architecture directory
BSP_DIR     # Board support package directory
CC          # Cross compiler
LD          # Linker
ADD_CFLAGS  # Added flags depending on target architecture
```

There are 3 ways to interact with the docker container :

- **Compilation** : `docker compose run --rm build` (only execute `make`)
- **Cleaning** : `docker compose run --rm clean` (only execute `make clean`)
- **Entering** : `docker compose run --rm enter` (enter inside the docker container)

**<em>Note : `docker compose` require `root` permissions to run. This means that the generated files from compilation (.elf & .o files) are own by `root`. You can delete the `./build` directory using `docker compose run --rm clean` or doing it 'by hands' using `root rm`.</em>** 

# Flashing

To flash the generated `rav3ntos.elf`, use the probe-rs command below :
```bash
probe-rs download ./build/rav3ntos.elf --chip CHIP_NAME
```

<em>You can find your supported `CHIP_NAME` in probe-rs using `probe-rs chip list`.</em>

# Debugging

To use a debugger with it, type this command :
```bash
probe-rs gdb ./build/rav3ntos.elf --chip CHIP_NAME
```

In another terminal, open `gdb-multiarch` :
```bash
gdb-multiarch build/rav3ntos.elf
```

And run this set of commands :
```bash
target extended-remote localhost:1337
monitor reset halt
break main
continue
```

If you want to reflash the microcontroller, you can use the `load` command inside gdb.

# For STM32 cards with ST Link
```bash
minicom -D /dev/ttyACM0 -b 115200
```

# Documentation 

## `./arch` 

`./arch` first define eveything necessary to the cpu to start, for example the `startup.s` file.

Then, it need to specify `arch.h` file what header file he uses. For my Nucle H533RE, it use `core_cm33.h` header file. Also, it use the `bsp.h` file, specified inside the selectionned `./bsp` board (see more later).

## `./bsp`

`./bsp` embed everything board related.

It also need to define the `bsp.h` file because `arch.h` file include it.

When compiling, you just need to specify wich cpu and board you are using, the Makefile will select the correspondant `arch.h` and `bsp.h` file.