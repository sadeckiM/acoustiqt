#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>

class UdpReceiver : public QObject {
  QUdpSocket *udp_socket;
  uint8_t verifyChecksum(const unsigned char* data, int len,
                                    uint8_t poly, uint8_t init_val);
  Q_OBJECT 
public:
  explicit UdpReceiver(uint16_t port, QObject * parent = nullptr);
signals:
  void audioDataReceived(const QVector<int32_t>& samples);

private slots:
  void readPendingDatagrams();
};

#endif
