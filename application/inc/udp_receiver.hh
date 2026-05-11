#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QList>

class UdpReceiver : public QObject {
  QUdpSocket *udp_socket;
  Q_OBJECT 
public:
  explicit UdpReceiver(uint16_t port, QObject * parent = nullptr);
signals:
  void audioDataReceived(const QList<int32_t>& samples);

private slots:
  void readPendingDatagrams();
};

#endif
