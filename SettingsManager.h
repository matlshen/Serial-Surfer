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
    static int GetEnterKey();
    static bool GetLocalEcho();
    static bool GetContinuous();

    static void SetPort(QString port);
    static void SetBaudrate(int baudrate);
    static void SetDataBits(int data_bits);
    static void SetParity(int parity);
    static void SetStopBits(int stop_bits);
    static void SetFlowControl(int flow_control);
    static void SetEnterKey(int enter_key);
    static void SetLocalEcho(bool local_echo);
    static void SetContinuous(bool continuous);

    // QSettings object
    inline static QSettings *_settings = nullptr;

    // Serial port settings
    inline static QString _port_name = "";
    inline static int _baudrate = -1;
    inline static int _data_bits = -1;
    inline static int _parity = -1;
    inline static int _stop_bits = -1;
    inline static int _flow_control = -1;
    inline static int _enter_key = -1;
    inline static bool _local_echo = false;
    inline static bool _continuous = false;

signals:
};

#endif // SETTINGSMANAGER_H
