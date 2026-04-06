#include <driver/i2s.h>
#include <Arduino.h>

void togglePin(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void setup() {
  Serial.begin(115200);
  // Serial.println("Test mikrofonu");
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = I2S_BUFFER_SIZE,
    .use_apll = false
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  i2s_set_pin(I2S_NUM_0, &pin_config);
  while (!Serial) {
    delay(10);
  }
  digitalWrite(YELLOW_LED, HIGH);
}

void loop() {
  int32_t audio_samples[I2S_BUFFER_SIZE];
  size_t bytes_read;

  i2s_read(I2S_NUM_0, audio_samples, sizeof(audio_samples), &bytes_read,
           portMAX_DELAY);

  int64_t sum = 0;
  for (int i = 0; i < bytes_read / sizeof(int32_t); ++i) {
    sum += abs(audio_samples[i]);
  }
  int32_t average_amplitude = sum / (bytes_read / sizeof(int32_t));

  Serial.println(average_amplitude);
  if (average_amplitude > 500) {
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(YELLOW_LED, LOW);
  }

  delay(10);
}
