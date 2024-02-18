#ifndef HISTORYLINEEDIT_H
#define HISTORYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QStringList>
#include <QKeyEvent>

class HistoryLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HistoryLineEdit(QWidget *parent = nullptr);

public slots:
    void AddToHistory();
signals:
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    QStringList _history;
    int _history_index;

    void ShowPreviousItem();
    void ShowNextItem();
};

#endif // HISTORYLINEEDIT_H
