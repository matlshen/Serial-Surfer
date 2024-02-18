#include "SerialDisplay.h"
#include <QScrollBar>

void SerialDisplay::SetHexFormat(bool hex_format) {
    _hex_format = hex_format;
}

void SerialDisplay::SetScrollLock(bool locked) {
    _scroll_lock = locked;
    _scroll_bar_pos = this->verticalScrollBar()->value();
}

void SerialDisplay::Input(QByteArray data) {
    // If not hex format, append data as utf8 string
    if (!_hex_format) {
        QString text_data;

        // Handle special characters
        for (char ch : data) {
            if (ch == '\n' || ch == '\r')
                text_data.append(ch);
            else if (ch <= 0x1F)
                text_data.append('.');
            else
                text_data.append(ch);
        }

        insertPlainText(text_data);
    }
    // If hex is set
    else {
        // If not empty, add a leading space
        if (!this->document()->isEmpty()) {
            insertPlainText(" ");
        }
        insertPlainText(data.toHex(' '));
    }
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
    }
}
