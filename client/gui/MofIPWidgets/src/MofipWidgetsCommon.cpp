#include "MofIPWidgets/MofipWidgetsCommon.hpp"

namespace MofIPWidgets {

    QPainterPath rectRoundPath(QRectF rect, qreal radius) {
        qreal halfradius = radius / 2;
        QPainterPath path;
        path.moveTo(rect.left() + halfradius, rect.top());
        path.lineTo(rect.right() - halfradius, rect.top());
        // right top corner
        path.arcTo(QRectF(rect.right() - radius, rect.top(), radius, radius), 90, -90);
        path.lineTo(rect.right(), rect.bottom() - halfradius);
        // right bottom corner
        path.arcTo(QRectF(rect.right() - radius, rect.bottom() - radius, radius, radius), 0, -90);
        path.lineTo(rect.left() + halfradius, rect.bottom());
        // left bottom corner
        path.arcTo(QRectF(rect.left(), rect.bottom() - radius, radius, radius), -90, -90);
        path.lineTo(rect.left(), rect.top() + halfradius);
        // left top corner
        path.arcTo(QRectF(rect.left(), rect.top(), radius, radius), 180, -90);
        return path;
    }

}
