#include "StyleUtility.h"

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
QPainterPath tabpathRect(QRectF rect, qreal radius) {

	qreal arcbox = 2 * radius;
	QPainterPath path;
	path.moveTo(rect.right(), rect.bottom());
	path.lineTo(rect.right(), rect.top() + radius);
	path.arcTo(QRectF(rect.right() - arcbox, rect.top(), arcbox, arcbox), 0, 90);
	path.lineTo(rect.left() + radius, rect.top());
	path.arcTo(QRectF(rect.left(), rect.top(), arcbox, arcbox), 90, 90);
	path.lineTo(rect.left(), rect.bottom());

	return path;
}

QPainterPath tabpath(QRectF rect) {
	QPainterPath path;

	QPointF lefttop(rect.topLeft());
	qreal width = rect.width();
	qreal height = rect.height();

	QPolygonF polygon;
	polygon << QPointF(lefttop.x(), lefttop.y() + height)
		<< lefttop
		<< QPointF(lefttop.x() + width, lefttop.y())
		<< QPointF(lefttop.x() + width, lefttop.y() + height);
	qDebug() << "POLYGON: " << polygon;
	path.addPolygon(polygon);

	return path;
}
