
bin/lightberry: obj/main.o
	mkdir bin && gcc -o $@ $<

obj/main.o: src/main.c
	mkdir obj && gcc -o $@ -c $<

