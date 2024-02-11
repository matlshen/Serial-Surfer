#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadPorts();

    connect(&_port, &SerialPort::DataReceived, this, &MainWindow::ReadData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadPorts() {
    ui->ComboBoxPort->clear();
    for (auto &info : QSerialPortInfo::availablePorts()) {
        ui->ComboBoxPort->addItem(info.portName());
    }
}

void MainWindow::SendData() {
    bool is_written;
    QString text_data = ui->LineEditTx->text();

    if (ui->RadioHex->isChecked()) {
        QString cleaned_string = text_data.remove(' ');
        is_written = _port.Write(QByteArray::fromHex(cleaned_string.toUtf8()));
    } else {
        is_written = _port.Write(text_data.toUtf8());
    }

    if (!is_written) {
        QMessageBox::critical(this, "Error", "Cannot write to serial port");
    }
}

void MainWindow::on_BtnConnect_clicked()
{
    bool is_connected;

    // Connect to currently selected serial port
    is_connected = _port.Connect(ui->ComboBoxPort->currentText(),
                                 ui->ComboBoxBaudrate->currentText(),
                                 ui->ComboBoxDataBits->currentText(),
                                 ui->ComboBoxParity->currentText(),
                                 ui->ComboBoxStopBits->currentText(),
                                 ui->ComboBoxFlowControl->currentText());


    if (!is_connected) {
        QMessageBox::critical(this, "Error", "Cannot connect to serial port");
    }
}


void MainWindow::on_BtnSend_clicked()
{
    // Same as when return pressed
    SendData();
    ui->LineEditTx->AddToHistory();
}

void MainWindow::ReadData(QByteArray data) {
    ui->TextEditRx->insertPlainText(QString::fromUtf8(data));
}

void MainWindow::on_LineEditTx_returnPressed()
{
    // Same as when send button pressed
    SendData();
    ui->LineEditTx->AddToHistory();
}

