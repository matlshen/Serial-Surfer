#include "SettingsManager.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject{parent}
{
    _settings = new QSettings("SerialSurfer.ini", QSettings::Format::IniFormat);
    //LoadSettings();
}

SettingsManager::~SettingsManager() {
    //StoreSettings();
    delete _settings;
}

void SettingsManager::LoadSettings() {
    qDebug() << "Loading settings";
    if (_settings == nullptr)
        _settings = new QSettings("SerialSurfer.ini", QSettings::Format::IniFormat);

    if (_settings->contains("SerialParameters/Port"))
        _port_name = _settings->value("SerialParameters/Port").toString();

    if (_settings->contains("SerialParameters/Baudrate"))
        _baudrate = _settings->value("SerialParameters/Baudrate").toInt();

    if (_settings->contains("SerialParameters/DataBits"))
        _data_bits = _settings->value("SerialParameters/DataBits").toInt();

    if (_settings->contains("SerialParameters/Parity"))
        _parity = _settings->value("SerialParameters/Parity").toInt();

    if (_settings->contains("SerialParameters/StopBits"))
        _stop_bits = _settings->value("SerialParameters/StopBits").toInt();

    if (_settings->contains("SerialParameters/FlowControl"))
        _flow_control = _settings->value("SerialParameters/FlowControl").toInt();

    if (_settings->contains("TerminalParameters/EnterKey"))
        _enter_key = _settings->value("TerminalParameters/EnterKey").toInt();

    if (_settings->contains("TerminalParameters/LocalEcho"))
        _local_echo = _settings->value("TerminalParameters/LocalEcho").toBool();

    if (_settings->contains("TerminalParameters/Continuous"))
        _continuous = _settings->value("TerminalParameters/Continuous").toBool();
}

void SettingsManager::StoreSettings() {
    qDebug() << "Storing settings";
    _settings->setValue("SerialParameters/Port", _port_name);
    _settings->setValue("SerialParameters/Baudrate", _baudrate);
    _settings->setValue("SerialParameters/DataBits", _data_bits);
    _settings->setValue("SerialParameters/Parity", _parity);
    _settings->setValue("SerialParameters/StopBits", _stop_bits);
    _settings->setValue("SerialParameters/FlowControl", _flow_control);
    _settings->setValue("TerminalParameters/EnterKey", _enter_key);
    _settings->setValue("TerminalParameters/LocalEcho", _local_echo);
    _settings->setValue("TerminalParameters/Continuous", _continuous);
}

QString SettingsManager::GetPort() {
    return _port_name;
}

int SettingsManager::GetBaudrate() {
    return _baudrate;
}

int SettingsManager::GetDataBits() {
    return _data_bits;
}

int SettingsManager::GetParity() {
    return _parity;
}

int SettingsManager::GetStopBits() {
    return _stop_bits;
}

int SettingsManager::GetFlowControl() {
    return _flow_control;
}

int SettingsManager::GetEnterKey() {
    return _enter_key;
}

bool SettingsManager::GetLocalEcho() {
    return _local_echo;
}

bool SettingsManager::GetContinuous() {
    return _continuous;
}

void SettingsManager::SetPort(QString port) {
    _port_name = port;
}

void SettingsManager::SetBaudrate(int baudrate) {
    _baudrate = baudrate;
}

void SettingsManager::SetDataBits(int data_bits) {
    _data_bits = data_bits;
}

void SettingsManager::SetParity(int parity) {
    _parity = parity;
}

void SettingsManager::SetStopBits(int stop_bits) {
    _stop_bits = stop_bits;
}

void SettingsManager::SetFlowControl(int flow_control) {
    _flow_control = flow_control;
}

void SettingsManager::SetEnterKey(int enter_key) {
    _enter_key = enter_key;
}

void SettingsManager::SetLocalEcho(bool local_echo) {
    _local_echo = local_echo;
}

void SettingsManager::SetContinuous(bool continuous) {
    _continuous = continuous;
}
