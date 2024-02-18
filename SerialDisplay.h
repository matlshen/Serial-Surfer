#ifndef SERIALDISPLAY_H
#define SERIALDISPLAY_H

#include <QWidget>
#include <QTextEdit>

class SerialDisplay : public QTextEdit
{
    Q_OBJECT
public:
    explicit SerialDisplay(QWidget *parent = nullptr) : QTextEdit{parent} {};
    void SetScrollLock(bool locked);
    virtual void insertPlainText(const QString &text);
signals:
protected:

private:
    bool _scroll_lock = false;
    int _scroll_bar_pos;
};

#endif // SERIALDISPLAY_H
