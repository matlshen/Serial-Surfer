#include "OptionsDialog.h"
#include "ui_optionsdialog.h"
#include "SettingsManager.h"
#include <QSerialPortInfo>

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    SettingsManager::LoadSettings();
    PopulateOptions();
}

OptionsDialog::~OptionsDialog()
{
    SettingsManager::StoreSettings();
    delete ui;
}

void OptionsDialog::PopulateOptions() {
    // Get available serial ports on device
    LoadPorts();

    // Check if port stored in settings is available
    QString settings_port = SettingsManager::GetPort();
    int index = ui->portComboBox->findText(settings_port);
    if (index != -1) {
        ui->portComboBox->setCurrentIndex(index);
    } else {
        ui->portComboBox->setCurrentText(settings_port);
    }

    // Baudrate
    int baudrate = SettingsManager::GetBaudrate();
    if (baudrate != -1)
        ui->baudrateComboBox->setCurrentText(QString::number(baudrate));

    // Data Bits
    int data_bits = SettingsManager::GetDataBits();
    if (data_bits != -1)
        ui->dataBitsComboBox->setCurrentText(QString::number(data_bits));

    // Parity
    int parity = SettingsManager::GetParity();
    if (parity != -1)
        ui->parityComboBox->setCurrentIndex(parity);

    // Stop Bits
    int stop_bits = SettingsManager::GetStopBits();
    if (stop_bits != -1)
        ui->stopBitsComboBox->setCurrentText(QString::number(stop_bits));

    // Flow Control
    int flow_control = SettingsManager::GetFlowControl();
    if (flow_control != -1)
        ui->flowControlComboBox->setCurrentIndex(flow_control);

    // Entery Key
    int enter_key = SettingsManager::GetEnterKey();
    if (enter_key != -1)
        ui->enterKeyComboBox->setCurrentIndex(enter_key);

    // Local Echo
    bool local_echo = SettingsManager::GetLocalEcho();
    ui->localEchoCheckBox->setChecked(local_echo);

    // Continuous
    bool continuous = SettingsManager::GetContinuous();
    ui->continuousCheckBox->setChecked(continuous);
}

void OptionsDialog::LoadPorts() {
    ui->portComboBox->clear();
    for (auto &info : QSerialPortInfo::availablePorts()) {
        ui->portComboBox->addItem(info.portName());
    }
}

void OptionsDialog::on_buttonBox_accepted()
{
    SettingsManager::SetPort(ui->portComboBox->currentText());
    SettingsManager::SetBaudrate(ui->baudrateComboBox->currentText().toInt());
    SettingsManager::SetDataBits(ui->dataBitsComboBox->currentText().toInt());

    switch (ui->parityComboBox->currentText().toLatin1().at(0)) {
        case 'N':
            SettingsManager::SetParity(0);
            break;
        case 'E':
            SettingsManager::SetParity(1);
            break;
        case 'O':
            SettingsManager::SetParity(2);
            break;
    }

    SettingsManager::SetStopBits(ui->stopBitsComboBox->currentText().toInt());

    switch (ui->flowControlComboBox->currentText().toLatin1().at(0)) {
        case 'N':
            SettingsManager::SetFlowControl(0);
            break;
        case 'X':
            SettingsManager::SetFlowControl(1);
            break;
        case 'R':
            SettingsManager::SetFlowControl(2);
            break;
    }

    SettingsManager::SetEnterKey(ui->enterKeyComboBox->currentIndex());
    SettingsManager::SetLocalEcho(ui->localEchoCheckBox->isChecked());
    SettingsManager::SetContinuous(ui->continuousCheckBox->isChecked());
}


void OptionsDialog::on_pushButton_clicked()
{
    // Store current port
    QString current_port = ui->portComboBox->currentText();

    // Reload ports
    LoadPorts();

    // Restore current port if available
    int index = ui->portComboBox->findText(current_port);
    if (index != -1)
        ui->portComboBox->setCurrentText(current_port);
}

