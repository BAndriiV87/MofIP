#include "MofIPWidgets/SimpleWidget.hpp"

#include <QtWidgets>

SimpleWidget::SimpleWidget(QWidget* pwgt/* = 0 */) {
	setLineWidth(3);
	setFrameStyle(Box | Sunken);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void SimpleWidget::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QLinearGradient gradient(0, 0, width(), height());
	float f = m_nProcess / 100.0f;

	gradient.setColorAt(0, Qt::yellow);
	gradient.setColorAt(f, Qt::red);

	painter.fillRect(rect(), Qt::black);
	painter.setBrush(gradient);
	painter.drawRect(0, 0, (int)(width() * f), height());

	painter.setPen(QPen(Qt::green));
	QString str = QString().setNum(m_nProcess) + "%";
	painter.drawText(rect(), Qt::AlignCenter, str);

	drawFrame(&painter);
}

QSize SimpleWidget::sizeHint() const {
	return QSize(200, 30);
}

void SimpleWidget::slotSetProgress(int n) {
	m_nProcess = n > 100 ? 100 : n < 0 ? 0 : n;
	repaint();
	emit progressChanged(m_nProcess);
}
