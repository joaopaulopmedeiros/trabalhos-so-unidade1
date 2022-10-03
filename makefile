CC := gcc

app: message auxiliar sequential run

message:
	@echo Hello, we're making things ready for ya...

auxiliar: src/auxiliar.c
	$(CC) $^ -o $@

sequential: src/sequential.c
	$(CC) $^ -o $@

run: 
	./auxiliar 3 3 3 3
	./sequential ./assets/M1.txt ./assets/M2.txt

reload: app
