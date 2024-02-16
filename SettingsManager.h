#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager();

    static void LoadSettings();
    static void StoreSettings();

    static QString GetPort();
    static int GetBaudrate();
    static int GetDataBits();
    static int GetParity();
    static int GetStopBits();
    static int GetFlowControl();

    static void SetPort(QString port);
    static void SetBaudrate(int baudrate);
    static void SetDataBits(int data_bits);
    static void SetParity(int parity);
    static void SetStopBits(int stop_bits);
    static void SetFlowControl(int flow_control);

    // QSettings object
    static QSettings *_settings;

    // Serial port settings
    static QString _port_name;
    static int _baudrate;
    static int _data_bits;
    static int _parity;
    static int _stop_bits;
    static int _flow_control;

signals:
};

#endif // SETTINGSMANAGER_H
