CC := gcc

build: message compile	

message:
	@echo "Hello, we're making things ready for ya..."

compile: src/main.c
	$(CC) $^ -o $@

reload: build
