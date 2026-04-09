#include "microphone.hh"

Microphone::Microphone(int32_t pin_sck, int32_t pin_ws, int32_t pin_sd, i2s_channel_fmt_t channel) {
  i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = channel,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };
  i2s_mic_pins = {
    .bck_io_num = pin_sck,
    .ws_io_num = pin_ws,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = pin_sd
  };
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
  Serial.begin(SERIAL_BAUD);
}

int32_t Microphone::get_rms(uint8_t shift) {
  int64_t sum = 0;
  for (int32_t i = 0; i < last_sample; ++i) {
    int32_t sample = buffer[i] >> shift;
    sum += sample * sample;
  }
  return static_cast<int32_t>(std::sqrt(sum/last_sample));
}

int32_t Microphone::read_raw_data_to_buffer() {
  size_t bytes_read = 0;
  esp_err_t err = i2s_read(I2S_NUM_0, buffer, sizeof(int32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY); 
  if (err != ESP_OK) {
    Serial.printf("I2S: read_raw: %s\n", esp_err_to_name(err));
    last_sample = 0;
    return -1;
  }
  last_sample = static_cast<int32_t>(bytes_read / sizeof(int32_t));
  return last_sample;
}
