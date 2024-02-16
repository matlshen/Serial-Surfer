#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "SerialPort.h"

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

private slots:
    void ReadData(QByteArray data);
    void on_actionOptions_triggered();
    void on_actionConnect_triggered();

private:
    Ui::MainWindow *ui;

    SerialPort _port;

    // Serial port settings
    QString _port_name;
    int _baud_rate;
    int _data_bits;
    int _parity;
    int _stop_bits;
    int _flow_control;
};
#endif // MAINWINDOW_H
