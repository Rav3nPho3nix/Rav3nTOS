# Rav3nTOS
My own RTOS

# ToDo
- [X] Linker
- [X] Vector table
- [X] Reset Handler
- [ ] UART
- [ ] SysTick
- [ ] Task structure
- [ ] Context switching
- [ ] Round robin
- [ ] IPC & Synchronisation
- [ ] Separation between kernel & arch & bsp
- [ ] Microkernel
- [ ] MPU Isolation
- [ ] Sandboxing
- [ ] Stack canaries
- [ ] EDF Scheduler
- [ ] Post quantum crypto

# Requirements
- Docker
- Docker compose
- Renode (optional : for ARM emulation)

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

# ARM targets emulation (optional)
I use **Renode** to emulate ARM targets.

Run the `./bsp/renode_<board>/renode.resc` script file to automatically load the compiled `.elf` file and boot into the RTOS :
```bash
renode -e 'include @bsp/renode_<board>/renode.resc'
```