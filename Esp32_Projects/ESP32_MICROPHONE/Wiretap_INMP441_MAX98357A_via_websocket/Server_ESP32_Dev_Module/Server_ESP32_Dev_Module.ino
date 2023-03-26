#include <SPI.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "XT_DAC_Audio.h"

//#define I2S_WS_TX  12
//#define I2S_SCK_TX 13
//#define I2S_DATA_OUT_TX  15

//#define I2S_PORT I2S_NUM_0
//#define I2S_SAMPLE_RATE   (16000)
//#define I2S_SAMPLE_BITS   (32)
//#define UPDATE_INTERVAL   (500)

const char* ssid = "ESP_MIC";
const char* password = "12345678";

using namespace websockets;
WebsocketsServer server;
WebsocketsClient client;


const i2s_config_t i2s_config_tx = {
  .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate = I2S_SAMPLE_RATE,
  .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
  .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
  .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
  .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  .dma_buf_count = 32,
  .dma_buf_len = 64
};

const i2s_pin_config_t pin_config_tx = {
  .bck_io_num = I2S_SCK_TX,
  .ws_io_num = I2S_WS_TX,
  .data_out_num = I2S_DATA_OUT_TX,
  .data_in_num = I2S_PIN_NO_CHANGE
};

TaskHandle_t drawGraphTaskHandler = NULL;

unsigned long last_update_sent = 0;
bool isConnected; 
static int sampleValue;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  server.listen(8888);
    IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address : ");
  Serial.println(IP);

 // xTaskCreate(server_task, "server_task", 4096, NULL, 1, NULL);
}

void loop() {
  i2s_write_from_client();
}

void i2s_write_from_client()
{   
  if(client.available()){
    last_update_sent = millis();
    client.poll();
    WebsocketsMessage msg = client.readBlocking();
    char *buf_ptr = (char*)msg.c_str();
    int bytes_written = msg.length();
    i2s_write_bytes(I2S_PORT, buf_ptr, bytes_written, portMAX_DELAY);

    int32_t sample = (int32_t) buf_ptr[3] << 24;
    sample |=  (int32_t) buf_ptr[2] << 16;
    sample |= (int32_t) buf_ptr[1] << 8;
    sample |= (int32_t) buf_ptr[0];   

  }
}

void i2sInit(){
  i2s_driver_install(I2S_PORT, &i2s_config_tx, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config_tx);
}
