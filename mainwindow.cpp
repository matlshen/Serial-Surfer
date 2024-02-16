#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "OptionsDialog.h"
#include "SettingsManager.h"
#include "SerialPort.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //SettingsManager::LoadSettings();

    connect(&_port, &SerialPort::DataReceived, this, &MainWindow::ReadData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadData(QByteArray data) {
    // Stop timer if it is started
    // qint64 elapsed = _timer.elapsed();
    // if (elapsed > 0) {
    //     _timer.invalidate();
    //     QString elapsed_str = QString::number(elapsed);
    //     elapsed_str.append(" ms");
    //     ui->rxLatencyVal->setText(elapsed_str);
    // }

    // Write data to TextEditRx
    ui->RxTextEdit->moveCursor(QTextCursor::End);
    ui->RxTextEdit->insertPlainText(QString::fromUtf8(data));

    // Update rx bytes
    //AddRxBytes(data.size());
}

void MainWindow::on_actionOptions_triggered()
{
    // Open options dialog
    OptionsDialog optionsDialog;
    optionsDialog.exec();
}


void MainWindow::on_actionConnect_triggered()
{
    // If not currently connected
    if (ui->actionConnect->isChecked()) {
        qDebug() << "Connecting";
    }
    // If currently connected
    else {
        qDebug() << "Disconnecting";
    }

}

