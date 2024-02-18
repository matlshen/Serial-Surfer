#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "OptionsDialog.h"
#include "SettingsManager.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SettingsManager::LoadSettings();


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

    // Write data to RxTextEdit
    ui->RxTextEdit->moveCursor(QTextCursor::End);
    ui->RxTextEdit->insertPlainText(QString::fromUtf8(data));

    // Update rx bytes
    //AddRxBytes(data.size());
}

void MainWindow::SendData() {
    bool is_written;
    QString text_data = ui->TxLineEdit->text();

    // TODO: Handle formatting
    QByteArray write_data = text_data.toUtf8();

    is_written = _port.Write(write_data);

    // Handle errors
    if (!is_written)
        QMessageBox::critical(this, "Error", "Cannot write to serial port");

    // Start timer
    _timer.start();

    // If echo is enabled, write to text edit
    if (SettingsManager::GetLocalEcho()) {
        // Set text color to blue
        ui->RxTextEdit->moveCursor(QTextCursor::End);
        ui->RxTextEdit->setTextColor(Qt::blue);

        // Write contents of LineEditTx to RxTextEdit
        ui->RxTextEdit->insertPlainText(ui->TxLineEdit->text());

        // Set text color back to black
        ui->RxTextEdit->setTextColor(Qt::black);
    }

    // Update tx bytes
    //AddTxBytes(write_data.size());
}

void MainWindow::on_actionConnect_triggered()
{
    // If not currently connected
    if (ui->actionConnect->isChecked()) {
        bool is_connected;

        // Connect to currently selected serial port
        is_connected = _port.Connect(SettingsManager::GetPort(),
                                     SettingsManager::GetBaudrate(),
                                     SettingsManager::GetDataBits(),
                                     SettingsManager::GetParity(),
                                     SettingsManager::GetStopBits(),
                                     SettingsManager::GetFlowControl());

        // If connection failed
        if (!is_connected) {
            // Uncheck connect action
            ui->actionConnect->setChecked(false);
            QMessageBox::critical(this, "Error", "Cannot connect to serial port");
        }
    }
    // If currently connected
    else {
        _port.Disconnect();
    }
}

void MainWindow::on_actionOptions_triggered()
{
    // Open options dialog
    OptionsDialog optionsDialog;
    optionsDialog.exec();
}


void MainWindow::on_actionScroll_Lock_triggered()
{
    // Scroll lock on
    if (ui->actionScroll_Lock->isChecked()) {
    }
    // Scroll lock off
    else {
    }
}

void MainWindow::on_actionClear_triggered()
{
    // Clear RxTextEdit
    ui->RxTextEdit->clear();

    // TODO: Reset Tx, Rx bytes and latency
}



void MainWindow::on_sendButton_clicked()
{
    // Same as when return pressed
    SendData();
    ui->TxLineEdit->AddToHistory();
}


void MainWindow::on_TxLineEdit_returnPressed()
{
    // Same as when send button pressed
    SendData();
    ui->TxLineEdit->AddToHistory();
}



