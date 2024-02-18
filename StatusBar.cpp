#include "StatusBar.h"

StatusBar::StatusBar(QObject *parent)
    : QObject{parent}
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    // Add permanent widgets
    layout->addWidget(_tx_bytes_header_label);

    // Add spacer to push everything to the left
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

