
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <alsa/asoundlib.h>
#include <curl/curl.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  LOG(INFO) << "Opening default sequencer...";
  snd_seq_t *seq_handle;
  CHECK_EQ(0, snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0));

  LOG(INFO) << "Setting client name...";
  CHECK_EQ(0, snd_seq_set_client_name(seq_handle, "Lightberry Client"));
  
  LOG(INFO) << "Creating port...";
  int in_port = snd_seq_create_simple_port(seq_handle, "listen:in",
      SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
      SND_SEQ_PORT_TYPE_APPLICATION);
  CHECK_GE(in_port, 0);

  //{
  //  CURL *curl = curl_easy_init();

  LOG(INFO) << "Listening for midi events...";

  while (1) {
    snd_seq_event_t *event = NULL;
    snd_seq_event_input(seq_handle, &event);

    LOG(INFO) << "Event type: " << event->type;
    if (event->type == SND_SEQ_EVENT_CONTROLLER) {
      LOG(INFO) << "Controller event: " << event->data.control.param << " "
                << event->data.control.value;
    }
  }

  return 0;
}

