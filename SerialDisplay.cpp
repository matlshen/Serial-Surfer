#include "SerialDisplay.h"
#include <QScrollBar>

void SerialDisplay::SetScrollLock(bool locked) {
    _scroll_lock = locked;
    _scroll_bar_pos = this->verticalScrollBar()->value();
}

void SerialDisplay::insertPlainText(const QString &text) {
    // If scroll enabled, append text as normal
    if (!_scroll_lock) {
        QTextEdit::insertPlainText(text);
    }
    // If scroll disabled, don't autoscroll
    else {
       // Append text without moving the scrollbar
        QTextEdit::insertPlainText(text);

        // Restore the scrollbar position
        this->verticalScrollBar()->setValue(_scroll_bar_pos);

        qDebug() << "Scroll lock enabled: ";
    }
}
