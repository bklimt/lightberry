
#include <fnctl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/soundcard.h>
#include <unistd.h>

#define MIDI_INPUT_PATH "/dev/sequencer"  // TODO: Change this to a flag.

int seq_fd;
pthread_t midi_input_thread;

int main(int argc, char **argv) {
  printf("Hello world!");
  return 0;
}

