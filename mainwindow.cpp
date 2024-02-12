#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoadPorts();
    LoadSettings();

    connect(&_port, &SerialPort::DataReceived, this, &MainWindow::ReadData);
}

MainWindow::~MainWindow()
{
    StoreSettings();
    delete ui;
}

void MainWindow::LoadPorts() {
    ui->ComboBoxPort->clear();
    for (auto &info : QSerialPortInfo::availablePorts()) {
        ui->ComboBoxPort->addItem(info.portName());
    }
}

void MainWindow::LoadSettings() {
    QSettings settings("SerialSurfer.ini", QSettings::Format::IniFormat);


    // Check if Port is stored in settings
    // If it is, and port is available, select it
    QString settings_port = settings.value("SerialParameters/Port").toString();
    int index = ui->ComboBoxPort->findText(settings_port);
    if (index != -1) {
        ui->ComboBoxPort->setCurrentIndex(index);
    } else {
        ui->ComboBoxPort->setCurrentText(settings_port);
    }

    if (settings.contains("SerialParameters/Baudrate")) {
        ui->ComboBoxBaudrate->setCurrentText(settings.value("SerialParameters/Baudrate").toString());
    } else {
        settings.setValue("SerialParameters/Baudrate", ui->ComboBoxBaudrate->currentText());
    }

    if (settings.contains("SerialParameters/DataBits")) {
        ui->ComboBoxDataBits->setCurrentText(settings.value("SerialParameters/DataBits").toString());
    } else {
        settings.setValue("SerialParameters/DataBits", ui->ComboBoxDataBits->currentText());
    }

    if (settings.contains("SerialParameters/Parity")) {
        ui->ComboBoxParity->setCurrentText(settings.value("SerialParameters/Parity").toString());
    } else {
        settings.setValue("SerialParameters/Parity", ui->ComboBoxParity->currentText());
    }

    if (settings.contains("SerialParameters/StopBits")) {
        ui->ComboBoxStopBits->setCurrentText(settings.value("SerialParameters/StopBits").toString());
    } else {
        settings.setValue("SerialParameters/StopBits", ui->ComboBoxStopBits->currentText());
    }

    if (settings.contains("SerialParameters/FlowControl")) {
        ui->ComboBoxFlowControl->setCurrentText(settings.value("SerialParameters/FlowControl").toString());
    } else {
        settings.setValue("SerialParameters/FlowControl", ui->ComboBoxFlowControl->currentText());
    }

    if (settings.contains("TxOptions/Echo")) {
        ui->checkEchoTx->setChecked(settings.value("TxOptions/Echo").toBool());
    } else {
        settings.setValue("TxOptions/Echo", ui->checkEchoTx->isChecked());
    }
}

void MainWindow::StoreSettings() {
    QSettings settings("SerialSurfer.ini", QSettings::Format::IniFormat);

    settings.setValue("SerialParameters/Port", ui->ComboBoxPort->currentText());
    settings.setValue("SerialParameters/Baudrate", ui->ComboBoxBaudrate->currentText());
    settings.setValue("SerialParameters/DataBits", ui->ComboBoxDataBits->currentText());
    settings.setValue("SerialParameters/Parity", ui->ComboBoxParity->currentText());
    settings.setValue("SerialParameters/StopBits", ui->ComboBoxStopBits->currentText());
    settings.setValue("SerialParameters/FlowControl", ui->ComboBoxFlowControl->currentText());

    settings.setValue("TxOptions/Echo", ui->checkEchoTx->isChecked());
}

void MainWindow::AddTxBytes(qint64 bytes) {
    qint64 current_bytes = ui->txBytesVal->text().toLongLong();
    current_bytes += bytes;
    ui->txBytesVal->setText(QString::number(current_bytes));
}

void MainWindow::AddRxBytes(qint64 bytes) {
    qint64 current_bytes = ui->rxBytesVal->text().toLongLong();
    current_bytes += bytes;
    ui->rxBytesVal->setText(QString::number(current_bytes));
}

void MainWindow::SendData() {
    bool is_written;
    QString text_data = ui->LineEditTx->text();

    // Check format selection
    QByteArray write_data;
    if (ui->RadioHex->isChecked()) {
        text_data.remove(' ');
        write_data = QByteArray::fromHex(text_data.toUtf8());
    } else {
        write_data = text_data.toUtf8();
    }
    is_written = _port.Write(write_data);

    // Handle errors
    if (!is_written) {
        QMessageBox::critical(this, "Error", "Cannot write to serial port");
    }

    // Start timer
    _timer.start();

    // If echo is enabled, write to text edit
    if (ui->checkEchoTx->isChecked()) {
        // Set text color to blue
        ui->TextEditRx->moveCursor(QTextCursor::End);
        ui->TextEditRx->setTextColor(Qt::blue);

        // Write contents of LineEditTx to TextEditRx
        ui->TextEditRx->insertPlainText(ui->LineEditTx->text());

        // Set text color back to black
        ui->TextEditRx->setTextColor(Qt::black);
    }

    // Update tx bytes
    AddTxBytes(write_data.size());
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
    // Stop timer if it is started
    qint64 elapsed = _timer.elapsed();
    if (elapsed > 0) {
        _timer.invalidate();
        QString elapsed_str = QString::number(elapsed);
        elapsed_str.append(" ms");
        ui->rxLatencyVal->setText(elapsed_str);
    }

    // Write data to TextEditRx
    ui->TextEditRx->moveCursor(QTextCursor::End);
    ui->TextEditRx->insertPlainText(QString::fromUtf8(data));

    // Update rx bytes
    AddRxBytes(data.size());
}

void MainWindow::on_LineEditTx_returnPressed()
{
    // Same as when send button pressed
    SendData();
    ui->LineEditTx->AddToHistory();
}


void MainWindow::on_btnClear_clicked()
{
    // Clear TextEditRx
    ui->TextEditRx->clear();

    // Reset tx and rx bytes
    ui->txBytesVal->setText("0");
    ui->rxBytesVal->setText("0");

    // Reset latency
    ui->rxLatencyVal->setText("0 ms");
}

