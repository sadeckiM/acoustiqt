#include "spectrum_visualizer.hh"
#include <QPainter>
#include "audio_config.hh"

SpectrumVisualizer::SpectrumVisualizer(QWidget *parent) : QWidget(parent) {}

void SpectrumVisualizer::updateSpectrum(const QList<double> &data) {
  spectrum_data = data;
  update();
}

// void SpectrumVisualizer::paintEvent(QPaintEvent *event) {
//   Q_UNUSED(event);
//   if (!this->isVisible() || this->width() <= 0 || this->height() <= 0) return;
//   if (spectrum_data.isEmpty()) return;
//
//   QPainter painter(this);
//
//   if(!painter.isActive()) return;
//
//   painter.fillRect(rect(), Qt::black);
//
//   double width = this->width();
//   double height = this->height();
//   int nbars = spectrum_data.size();
//
//   double bar_width = static_cast<double>(width) / nbars;
//   const double max_db = 0.0;
//   const double min_db = -AudioConfig::NOISE_THRESHOLD;
//
//   for (int i = 0; i < nbars; ++i) {
//     double magnitude = spectrum_data[i];
//     if (std::isnan(magnitude) || magnitude < 0.0)
//       magnitude = 0.0;
//
//     double db = 20.0 * std::log10(magnitude + AudioConfig::EPSILON);
//
//     if (std::isinf(db) || db < min_db)
//       db = min_db;
//
//     double normalized = (db - min_db) / (max_db - min_db);
//     normalized = qBound(0.0, normalized, 1.0);
//
//     double bar_height = normalized * height;
//     double x = i * bar_width;
//     double y = height - bar_height;
//     double draw_width = std::max(1.0, bar_width - 1.0);
//     painter.fillRect(QRectF(x, y, draw_width, bar_height), QColor(0, 255, 150));
//   }
// }
//

void SpectrumVisualizer::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // 1. Uciekamy, jeśli okno nie ma wymiarów
    if (this->width() <= 0 || this->height() <= 0 || spectrum_data.isEmpty()) return;

    // 2. Oddzielamy tworzenie Paintera od jego uruchomienia
    QPainter painter;
    if (!painter.begin(this)) {
        // Jeśli to się wydrukuje, na 100% masz "Widżet Ducha" w MainWindow.cpp!
        qDebug() << "BŁĄD: Widżet nie jest widoczny na ekranie (engine=0)!";
        return; 
    }

    painter.fillRect(rect(), Qt::black);
    painter.setBrush(QColor(0, 255, 150));
    painter.setPen(Qt::NoPen);

    double w = this->width();
    double h = this->height();
    int nbars = spectrum_data.size();
    double bar_width = w / nbars;

    // 3. WPISUJEMY NA SZTYWNO, aby wykluczyć błąd zmiennych konfiguracyjnych
    const double max_db = 0.0;
    const double min_db = -60.0; 

    for (int i = 0; i < nbars; ++i) {
        double magnitude = spectrum_data[i];
        
        // 4. PANCERNA OCHRONA PRZED NaN i INF
        if (std::isnan(magnitude) || std::isinf(magnitude) || magnitude <= 0.0) {
            magnitude = 1e-6; // Zamieniamy błędy i 0 na absolutne minimum
        }

        double db = 20.0 * std::log10(magnitude);
        double normalized = (db - min_db) / (max_db - min_db);

        // Ubezpieczenie wyniku
        if (std::isnan(normalized) || std::isinf(normalized)) {
            normalized = 0.0;
        }

        // Zamykamy słupek bezpiecznie w wymiarach ekranu
        normalized = std::clamp(normalized, 0.0, 1.0);

        double bar_height = normalized * h;
        double x = i * bar_width;
        double y = h - bar_height;
        double draw_width = std::max(1.0, bar_width - 1.0);

        // 5. Rysujemy za pomocą bezpiecznego QRectF
        painter.fillRect(QRectF(x, y, draw_width, bar_height), QColor(0, 255, 150));
    }
    
    // Kończymy rysowanie
    painter.end();
}
