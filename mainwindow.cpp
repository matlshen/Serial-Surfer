#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "OptionsDialog.h"
#include "SettingsManager.h"
#include <QRegularExpression>
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
    ui->RxTextEdit->Input(data);

    // Update rx bytes
    //AddRxBytes(data.size());
}

void MainWindow::SendData() {
    bool is_written;
    QString text_data = ui->TxLineEdit->text();

    // Turn text_data into a QByteArray
    // If input matches hex pattern (hXX), convert to hex
    QByteArray write_data;
    static QRegularExpression hex_pattern("h([0-9a-fA-F]{2})");

    bool contains_hex = hex_pattern.match(text_data).hasMatch();

    int pos = 0;
    while (pos < text_data.length()) {
        QRegularExpressionMatch match = hex_pattern.match(text_data, pos);
        if (match.hasMatch() && match.capturedStart(0) == pos) {
            // Convert the hex sequence to a byte
            bool ok;
            int hexValue = match.captured(1).toInt(&ok, 16);
            if (ok) {
                write_data.append(static_cast<char>(hexValue));
                pos += match.captured(0).length(); // Move past this hex sequence

                // If the next character is a space and it's followed by another hex pattern, skip the space
                if (pos < text_data.length() && text_data[pos] == ' ' && hex_pattern.match(text_data, pos + 1).hasMatch()) {
                    pos += 1; // Skip the space
                }
            } else {
                pos += 1; // This should never be reached with a valid hex pattern match
            }
        } else {
            // Append this character as its ASCII representation
            write_data.append(text_data.at(pos).toLatin1());
            pos += 1;
        }
    }

    // Send enter key if no hex characters
    if (!contains_hex) {
        switch (SettingsManager::GetEnterKey()) {
            case 0:
                // Append carriage return and line feed
                write_data.append('\r');
                write_data.append('\n');
                break;
            case 1:
                // Append carriage return
                write_data.append('\r');
                break;
            case 2:
                // Append line feed
                write_data.append('\n');
                break;
            default:
                // Do nothing
                break;
        }
    }

    is_written = _port.Write(write_data);

    // Handle errors
    if (!is_written)
        QMessageBox::critical(this, "Error", "Cannot write to serial port");

    // If data is written successfully
    else {
        // Start timer
        _timer.start();

        // If echo is enabled, write to text edit
        if (SettingsManager::GetLocalEcho()) {
            // Set text color to blue
            ui->RxTextEdit->moveCursor(QTextCursor::End);
            ui->RxTextEdit->setTextColor(Qt::blue);

            // Write contents of LineEditTx to RxTextEdit
            ui->RxTextEdit->Input(write_data);

            // Set text color back to black
            ui->RxTextEdit->setTextColor(Qt::black);
        }
    }

    // Clear the line edit
    ui->TxLineEdit->clear();
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

void MainWindow::on_actionView_Hex_triggered()
{
    ui->RxTextEdit->SetHexFormat(ui->actionView_Hex->isChecked());
}



void MainWindow::on_actionScroll_Lock_triggered()
{
    // Scroll lock on
    if (ui->actionScroll_Lock->isChecked()) {
        ui->RxTextEdit->SetScrollLock(true);
    }
    // Scroll lock off
    else {
        ui->RxTextEdit->SetScrollLock(false);
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





