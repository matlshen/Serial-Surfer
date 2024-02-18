#include "HistoryLineEdit.h"
#include <QWheelEvent>

HistoryLineEdit::HistoryLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , _history(0)
    , _history_index(-1)
{
    _history_index = -1;
}


void HistoryLineEdit::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        ShowPreviousItem();
        break;
    case Qt::Key_Down:
        ShowNextItem();
        break;
    default:
        // For other keys, proceed as normal
        QLineEdit::keyPressEvent(event);
    }
}

void HistoryLineEdit::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        ShowPreviousItem();
    } else if (event->angleDelta().y() < 0) {
        ShowNextItem();
    }
}

void HistoryLineEdit::AddToHistory() {
    _history.push_back(text());
    _history_index = _history.count()-1;
}

void HistoryLineEdit::ShowPreviousItem() {
    if (_history_index == -1) {
        _history_index = _history.size() - 1;
    } else if (_history_index > 0) {
        _history_index--;
    }

    if (_history_index >= 0) {
        setText(_history[_history_index]);
    }
}

void HistoryLineEdit::ShowNextItem() {
    if (_history_index == -1) {
        return;
    }

    if (_history_index < _history.size() - 1) {
        _history_index++;
        setText(_history[_history_index]);
    } else {
        _history_index = -1;
        clear();
    }
}
