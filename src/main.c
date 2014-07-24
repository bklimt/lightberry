
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/soundcard.h>
#include <unistd.h>

#define MIDI_INPUT_PATH "/dev/dmmidi1"  // TODO: Change this to a flag.

int seq_fd;
pthread_t midi_input_thread;

void *read_seq(void *data) {
  unsigned char in[4];
  int status;

  while (1) {
    status = read(seq_fd, &in, sizeof(in));
    if (status < 0) {
      fprintf(stderr, "Unable to read from %s\n", MIDI_INPUT_PATH);
      exit(-1);
    }

    if (in[0] == SEQ_MIDIPUTC) {
      printf("Received midi byte: %d\n", in[1]);
    }
  }
}

int main(int argc, char **argv) {
  seq_fd = open(MIDI_INPUT_PATH, O_RDONLY);
  if (seq_fd < 0) {
    fprintf(stderr, "Unable to open %s\n", MIDI_INPUT_PATH);
    exit(-1);
  }

  int status = pthread_create(&midi_input_thread, NULL, read_seq, NULL);
  if (status < 0) {
    fprintf(stderr, "Unable to spawn thread to read sequencer.\n");
    exit(-1);
  }

  while (1) {
  }

  return 0;
}

