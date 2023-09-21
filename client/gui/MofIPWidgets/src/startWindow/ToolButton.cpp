#include "startWindow/ToolButton.hpp"

// ----------------------------------------------------
namespace mofipgui {

    void ToolButtonPainter::enter(QPainter& painter) {
        painter.fillRect(0, 0, TOOL_BUTTON_RECT.width(), TOOL_BUTTON_RECT.height(), mEnterColor);
        drawIcon(painter);
    }

    void ToolButtonPainter::leave(QPainter& painter) {
        painter.fillRect(0, 0, TOOL_BUTTON_RECT.width(), TOOL_BUTTON_RECT.height(), 
            QApplication::palette().color(QPalette::Window));
        drawIcon(painter);
    }

    void ToolButtonPainter::press(QPainter& painter) {
        painter.fillRect(0, 0, TOOL_BUTTON_RECT.width(), TOOL_BUTTON_RECT.height(), mEnterColor);
        painter.fillRect(0, 0, TOOL_BUTTON_RECT.width(), TOOL_BUTTON_RECT.height(), mTransparentMaskColor);
        drawIcon(painter);
    }

    // ----------------------------------------------------

    CloseButtonPainter::CloseButtonPainter()
    {
        ToolButtonPainter::mEnterColor = Qt::red;
        ToolButtonPainter::mTransparentMaskColor = QColor(255, 255, 255, 90);
    }

    void CloseButtonPainter::drawIcon(QPainter& painter) {
        painter.setPen(QPen(QApplication::palette().color(QPalette::WindowText), 1));
        painter.drawLine(ICON_RECT.topLeft(), ICON_RECT.bottomRight());
        painter.drawLine(ICON_RECT.bottomLeft(), ICON_RECT.topRight());
    }

    void CollapseButtonPainter::drawIcon(QPainter& painter) {
        painter.setPen(QPen(QApplication::palette().color(QPalette::WindowText), 1));
        painter.drawLine(ICON_RECT.topLeft().x(), ICON_RECT.center().y() + 1,
            ICON_RECT.topRight().x(), ICON_RECT.center().y() + 1);
    }

    void MaxButtonPainter::drawIcon(QPainter& painter) {
        painter.setPen(QPen(QApplication::palette().color(QPalette::WindowText), 1));
        painter.drawRect(ICON_RECT);
    }

    MinButtonPainter::MinButtonPainter() {
        int deltarect = 2;
        QRect icon = ICON_RECT.adjusted(deltarect, deltarect, -deltarect, -deltarect);
        int shiftRect = 2;
        overRect = icon.adjusted(0, shiftRect, 0, shiftRect);
        underRect = icon.adjusted(shiftRect, 0, shiftRect + 1, 1);
        path.moveTo(underRect.x(), underRect.y() + shiftRect);
        path.lineTo(underRect.topLeft());
        path.lineTo(underRect.topRight());
        path.lineTo(underRect.bottomRight());
        path.lineTo(underRect.bottomRight().x() - shiftRect, underRect.bottomRight().y());
    }

    void MinButtonPainter::drawIcon(QPainter& painter) {
        QPen pen(QApplication::palette().color(QPalette::WindowText), 1);
        painter.setPen(pen);
        painter.drawRect(overRect);
        painter.drawPath(path);
    }
}
