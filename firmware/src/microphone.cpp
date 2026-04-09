#include "microphone.hh"

Microphone::Microphone(int pin_sck, int pin_ws, int pin_sd, i2s_channel_fmt_t
                       channel, ulong baud_rate) {
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
  Serial.begin(baud_rate);
}

int32_t Microphone::get_amplitude(uint8_t shift) {
  size_t bytes_read = 0;
  int32_t raw_samples[BUFFER_SIZE];
  int64_t sum = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * BUFFER_SIZE, &bytes_read,
           portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  if(samples_read == 0) return 0;

  for (int i = 0; i < samples_read; ++i) {
    sum += std::abs(raw_samples[i] >> shift);
  }
  return static_cast<int32_t>(sum/samples_read);
}
