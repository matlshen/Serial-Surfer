#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QObject>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QLabel>

class StatusBar : public QObject
{
    Q_OBJECT
public:
    explicit StatusBar(QObject *parent = nullptr);

signals:
private:
    QStatusBar *_status_bar;

    QLabel *_com_label;
    QLabel *_tx_bytes_header_label;
    QLabel *_rx_bytes_label;
    QLabel *_rx_latency_label;
};

#endif // STATUSBAR_H
