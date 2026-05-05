# Rav3nTOS
My own RTOS

## Docker to cross compile
By using **Docker**, you can compile Rav3nTOS on any computer.
<br>
There are 3 ways to interact with the docker container :
<br>
- **Compilation** : `docker compose run --rm make` (only execute `make`)
- **Cleaning** : `docker compose run --rm clean` (only execute `make clean`)
- **Entering** : `docker compose run --rm env`
<br>
The last option let you run any specific make target :
```
# Compile
make

# Clean
make clean

# etc
make your_target
```

***Note : All the make commands (except help) must be ran inside the docker container***

## Renode to emulate on PC (optionnal)
