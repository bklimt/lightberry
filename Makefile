
LIBS=-lstdc++ -lgflags -lglog -lasound `curl-config --libs`

all: bin/midi bin/json_test

test: bin/json_test
	bin/json_test

clean:
	rm obj/*.o || true
	rm bin/midi || true
	rm bin/json_test || true

bin/json_test: obj/json_test.o obj/json.o
	mkdir -p bin && gcc -o $@ $^ $(LIBS) -lgtest -lgtest_main

bin/midi: obj/midi.o
	mkdir -p bin && gcc -o $@ $^ $(LIBS)

obj/json.o: src/json.cc src/json.h
	mkdir -p obj && gcc -o $@ -c $<

obj/json_test.o: src/json_test.cc src/json.h
	mkdir -p obj && gcc -o $@ -c $<

obj/midi.o: src/midi.cc
	mkdir -p obj && gcc -o $@ -c $<
