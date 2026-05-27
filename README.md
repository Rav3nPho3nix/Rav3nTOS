# Rav3nTOS
My own RTOS

# ToDo
- [X] Linker
- [X] Vector table
- [X] Reset Handler
- [X] USART
- [ ] SysTick
- [ ] Task structure
- [ ] Context switching
- [ ] Round robin
- [ ] IPC & Synchronisation
- [ ] Microkernel
- [ ] MPU Isolation
- [ ] Sandboxing
- [ ] Stack canaries
- [ ] EDF Scheduler

# Requirements
- Docker
- Docker compose
- probe-rs
- gdb-multiarch
- Renode (optional : for ARM emulation)

# Software environment

To simplify compilation and deploiement, i use this list of technologies :
- **Docker** : containe to perform compilation
- **make** : compilation
- **probe-rs** : flashing
- **gdb-multiarch** : debugging

# Setting up Docker image

First, you need to build the Dockerfile into a docker image.

<em>I recommand to set the docker image name as `rav3ntos_dev`, however if you really want to apply another name, you will need to also modify the `image` value inside the `compose.yaml` file.</em>

```bash
docker build -t rav3ntos_dev .
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

# ARM targets emulation (optional)
I use **Renode** to emulate ARM targets.

Run the `./bsp/renode_<board>/renode.resc` script file to automatically load the compiled `.elf` file and boot into the RTOS :
```bash
renode -e 'include @bsp/renode_<board>/renode.resc'
```

Then open another terminal and connect to your `1234` port to see outputs :
```bash
nc 127.0.0.1 1234
```