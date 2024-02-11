#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPortInfo>
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

    void LoadPorts();
    void SendData();

private slots:

    void on_BtnConnect_clicked();

    void on_BtnSend_clicked();

    void ReadData(QByteArray data);

    void on_LineEditTx_returnPressed();

private:
    Ui::MainWindow *ui;
    SerialPort _port;


};
#endif // MAINWINDOW_H
