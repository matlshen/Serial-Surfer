#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QMessageBox>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();
    bool Connect(QString port_name,
                 int baudrate,
                 int data_bits,
                 int parity,
                 int stop_bits,
                 int flow_control);
    void Disconnect();
    bool Write(QByteArray data);

signals:
    void DataReceived(QByteArray bytearray);

private slots:
    void ReadyReadHandler();

private:
    QSerialPort *m_serial;


};

#endif // SERIALPORT_H
