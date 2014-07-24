
bin/lightberry: obj/main.o
	mkdir -p bin && gcc -o $@ $< -lpthread

obj/main.o: src/main.c
	mkdir -p obj && gcc -o $@ -c $<

