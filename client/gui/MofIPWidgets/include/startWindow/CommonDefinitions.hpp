#ifndef COMMON_DEFINITIONS_HPP
#define COMMON_DEFINITIONS_HPP

#include <QtWidgets>

namespace mofipgui {
    constexpr int CLIP_BORDER = 5;
    constexpr QSize ICON_SIZE(12, 12);
    constexpr QRect TOOL_BUTTON_RECT(0, 0, 48, 36);
    constexpr QRect ICON_RECT(TOOL_BUTTON_RECT.center().x() - ICON_SIZE.width() / 2,
        TOOL_BUTTON_RECT.center().y() - ICON_SIZE.height() / 2,
        ICON_SIZE.width(),
        ICON_SIZE.height());
}

#endif // COMMON_DEFINITIONS_HPP
