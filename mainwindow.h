#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSettings>
#include <QElapsedTimer>
#include <QDebug>
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
    void LoadSettings();
    void StoreSettings();

    void AddTxBytes(qint64 bytes);
    void AddRxBytes(qint64 bytes);

    void SendData();

private slots:

    void on_BtnConnect_clicked();

    void on_BtnSend_clicked();

    void ReadData(QByteArray data);

    void on_LineEditTx_returnPressed();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    SerialPort _port;

    QElapsedTimer _timer;
};
#endif // MAINWINDOW_H
