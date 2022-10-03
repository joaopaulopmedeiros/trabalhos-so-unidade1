CC := gcc

app: message build run

message:
	@echo Hello, we're making things ready for ya...

build: src/main.c
	$(CC) $^ -o $@

run: 
	./build 3 3 3 3

reload: app
