
#ifndef LUPPP_BUFFERS_H
#define LUPPP_BUFFERS_H

#include <cstring>
#include <jack/transport.h>

class Buffers
{
  public:
    Buffers()
    {
      memset( audio, 0, sizeof(float*)*32);
      memset( midi , 0, sizeof(void *)*32);
    }
    float* audio[32];
    void*  midi [32];
    
    enum BUFFER {
      MASTER_OUTPUT = 0,
      MASTER_INPUT,
      MASTER_MIDI_INPUT,
      APC_INPUT,
      APC_OUTPUT,
      
      // track buffers: they are the "working" buffers per track:
      // the end result is mixed into the master output, while each
      // stage along the way the amplitude etc can be analysed
      TRACK_0,
      TRACK_1,
      TRACK_2,
      TRACK_3,
      TRACK_4,
      TRACK_5,
      TRACK_6,
      TRACK_7,
    };
    
    // Jack details
    jack_nframes_t         nframes;
    jack_nframes_t         samplerate;
    
    jack_nframes_t          transportFrame;
    jack_position_t*        transportPosition;
    jack_transport_state_t* transportState;
    
};

#endif // LUPPP_BUFFERS_H

