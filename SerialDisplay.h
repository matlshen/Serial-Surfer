#ifndef SERIALDISPLAY_H
#define SERIALDISPLAY_H

#include <QWidget>
#include <QTextEdit>
#include <QByteArray>

class SerialDisplay : public QTextEdit
{
    Q_OBJECT
public:
    explicit SerialDisplay(QWidget *parent = nullptr) : QTextEdit{parent} {};
    void SetHexFormat(bool hex_format);
    void SetScrollLock(bool locked);
    void Input(QByteArray data);
    virtual void insertPlainText(const QString &text);
signals:
protected:

private:
    bool _hex_format = false;
    bool _scroll_lock = false;
    int _scroll_bar_pos;
};

#endif // SERIALDISPLAY_H
