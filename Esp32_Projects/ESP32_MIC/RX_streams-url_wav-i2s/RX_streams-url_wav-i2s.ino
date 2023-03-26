#include "AudioTools.h"



// UrlStream -copy-> EncodedAudioStream -> I2S

URLStream url("ESP32_AP01","asdfghjk");
I2SStream i2s;                  // I2S stream 
WAVDecoder decoder(i2s);        // decode wav to pcm and send it to I2S
EncodedAudioStream out(i2s, decoder); // Decoder stream
StreamCopy copier(out, url);    // copy in to out


void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  // setup i2s
  auto config = i2s.defaultConfig(TX_MODE);
  config.i2s_format = I2S_STD_FORMAT;
  config.sample_rate = 22050; 
  config.bits_per_sample = 16;
  config.channels = 2;
  i2s.begin(config);

// rhasspy
  url.begin("http://192.168.1.162:80");
}

void loop(){
  if (decoder) {
    copier.copy();
  } else {
    stop();
  }
}
