/**
 * @file audio_config.hh
 * @author Michał Sadecki (michal.sadecki@proton.me)
 * @brief Definicje stałych konfiguracyjnych dla modułu przetwarzania dźwięku.
 * 
 * Plik zawiera parametry dotyczące próbkowania, normalizacji sygnału
 * oraz ustawienia wizualizacji widma.
 * @version 0.5
 * @date 2026-05-12
 *
 * @copyright Copyright (c) 2026 Michał Sadecki
 */

#ifndef AUDIO_CONFIG_HH__
#define AUDIO_CONFIG_HH__

#include <cstdint>
#include <limits>
#include "protocol.hh"

/**
 * @namespace AudioConfig
 * @brief Przestrzeń nazw grupująca stałe parametry systemu audio.
 */
namespace AudioConfig {
  /// Częstotliwość próbkowania sygnału audio wyrażona w Hz.
  static constexpr uint16_t SAMPLE_RATE = 16000;
  /// Liczba próbek w jednym oknie analizy (paczce danych).
  static constexpr uint16_t N = Protocol::SAMPLES_PER_PACKET;
  /// Maksymalna wartość dla typu int32_t używana do normalizacji próbek.
  static constexpr double max_int32_t = std::numeric_limits<int32_t>::max();
  /// Mnożnik wzmocnienia głośności sygnału wejściowego.
  static constexpr double volume_gain = 1.0;
  /// Maksymalna wartość dla typu uint8_t, używana przy mapowaniu kolorów lub wysokości.
  static constexpr double max_uint8_t = std::numeric_limits<uint8_t>::max();
  /** 
   * @brief Wysokość wyświetlanego widma (liczba prążków).
   * Wynika z symetrii FFT (N/2).
   */
  static constexpr uint8_t height = Protocol::SAMPLES_PER_PACKET / 2;
  /// Liczba historycznych ramek przechowywanych dla spektrogramu.
  static constexpr uint16_t history_len = 200; 
  /// Mała wartość zapobiegająca dzieleniu przez zero w obliczeniach logarytmicznych.
  static constexpr double epsilon = 1e-6;
  /// Próg odcięcia szumu wyrażony w decybelach [dB].
  static constexpr double noise_treshold = 60.0;
};

#endif 
