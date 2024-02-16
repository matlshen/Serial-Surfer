#include "OptionsDialog.h"
#include "ui_optionsdialog.h"
#include "SettingsManager.h"

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    //SettingsManager::LoadSettings();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}
