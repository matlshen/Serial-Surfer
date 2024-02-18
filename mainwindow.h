#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QElapsedTimer>
#include <QLabel>
#include "SerialPort.h"
#include "StatusBar.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SendData();
    void AdTxBytes(qint64 bytes);//TODO
    void AdRxBytes(qint64 bytes);//TODO

private slots:
    void ReadData(QByteArray data);
    void on_actionConnect_triggered();
    void on_actionOptions_triggered();

    void on_actionScroll_Lock_triggered();

    void on_actionClear_triggered();

    void on_sendButton_clicked();

    void on_TxLineEdit_returnPressed();



private:
    Ui::MainWindow *ui;

    SerialPort _port;
    StatusBar _status_bar;

    // Serial port settings
    QString _port_name;
    int _baud_rate;
    int _data_bits;
    int _parity;
    int _stop_bits;
    int _flow_control;

    QElapsedTimer _timer;

    // Status bar labels
    QLabel status_label = QLabel("Status Bar");
};
#endif // MAINWINDOW_H
