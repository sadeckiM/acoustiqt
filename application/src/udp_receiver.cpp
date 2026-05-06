#include "udp_receiver.hh"
#include "protocol.hh"
#include <QNetworkDatagram>
#include <QDebug>

UdpReceiver::UdpReceiver(uint16_t port, QObject * parent) : QObject(parent) {
  udp_socket = new QUdpSocket(this);

  if (udp_socket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress |
                       QUdpSocket::ReuseAddressHint)) {
    qDebug() << "Listening UDP on port: " << port;
  } else {
    qCritical() << "UdpReceiver: error in binding port.";
  }

  connect(udp_socket, &QUdpSocket::readyRead, this,
          &UdpReceiver::readPendingDatagrams);
}

void UdpReceiver::readPendingDatagrams() {
  while (udp_socket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(static_cast<int>(udp_socket->pendingDatagramSize()));

    udp_socket->readDatagram(datagram.data(), datagram.size());

    if (datagram.size() != sizeof(AudioFrame)) {
      qWarning() << "Bad frame size. Received:" << datagram.size() <<
        "Expect:" << sizeof(AudioFrame);
      continue;
    }

    const AudioFrame* frame = reinterpret_cast<const
      AudioFrame*>(datagram.constData());

    if (frame->start != Protocol::START_BYTES) {
      qWarning() << "Bad start byte.";
      continue;
    }

    uint8_t expected_crc = verifyChecksum(reinterpret_cast<const unsigned
                                          char*>(frame), sizeof(AudioFrame) - 1,
                                          Protocol::POLYNOMIAL, Protocol::INIT_VAL);

    if (expected_crc != frame->crc) {
      qWarning() << "Bad CRC. Received:" << Qt::hex << frame->crc << "Calculated:"
        << expected_crc;
      continue;
    }

    QVector<int32_t> samples_vec;
    samples_vec.resize(Protocol::SAMPLES_PER_PACKED);
    std::copy(std::begin(frame->samples), std::end(frame->samples),
              samples_vec.begin());
    emit audioDataReceived(samples_vec);
  }
}


uint8_t UdpReceiver::verifyChecksum(const unsigned char* data, int len,
                                    uint8_t poly, uint8_t init_val) {
  uint8_t res_crc = init_val;

  while (--len >= 0) {
    res_crc ^= *data++;
    for (uint8_t i = 0 ; i < 8; ++i)
      res_crc = res_crc & 0x80 ? (res_crc << 1) ^ poly : res_crc << 1;
  }
  return res_crc;
}
