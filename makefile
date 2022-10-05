CC := gcc

app: message auxiliar sequential process thread run

message:
	@echo Hello, we're making things ready for ya...

auxiliar: src/auxiliar.c
	$(CC) $^ -o $@

sequential: src/sequential.c
	$(CC) $^ -o $@

process: src/process.c
	$(CC) $^ -o $@

thread: src/thread.c
	$(CC) $^ -o $@

run: 
	./auxiliar 10 10 10 10
	./sequential ./assets/M1.txt ./assets/M2.txt
	./thread ./assets/M1.txt ./assets/M2.txt 10
	./process ./assets/M1.txt ./assets/M2.txt 10

reload: app
