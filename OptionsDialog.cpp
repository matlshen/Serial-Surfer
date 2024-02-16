#include "OptionsDialog.h"
#include "ui_optionsdialog.h"
#include "SettingsManager.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    SettingsManager::LoadSettings();
}

OptionsDialog::~OptionsDialog()
{
    SettingsManager::StoreSettings();
    delete ui;
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
        case 'H':
            SettingsManager::SetFlowControl(1);
            break;
        case 'S':
            SettingsManager::SetFlowControl(2);
            break;
    }
}

