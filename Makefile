help:
	@echo "Usage: docker compose run --rm [make|clean|env]"
	@echo "This Makefile need to be run inside a Docker container."

ifndef DOCKER_ENV
%:
	@$(MAKE) help
	@exit 1
else

.DEFAULT_GOAL := build

build:
	@echo "> Compiling : OK"

clean:
	rm -f *.o *.elf
	@echo "> Cleaning : OK"

endif