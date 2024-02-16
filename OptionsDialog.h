#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OptionsDialog *ui;

    void LoadPorts();
};

#endif // OPTIONSDIALOG_H
