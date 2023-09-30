#include "startWindow/GetStartedMenuButton.hpp"

#include <QPainter>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QSize>
#include <QApplication>

namespace {
	#define ICON_SCALE 0.8
	#define MAIN_TEXT_WIDTH_PART 0.4
	constexpr QSize buttonsize = QSize(300, 80);
	constexpr QSize iconsize = QSize(buttonsize.height() * ICON_SCALE, buttonsize.height() * ICON_SCALE);

	const QRect iconrect = QRect(
		(buttonsize.height() - iconsize.height()) / 2,
		(buttonsize.height() - iconsize.height()) / 2,
		iconsize.width(),
		iconsize.height()
	);
	const QRect maintextrect = QRect(
		iconrect.topRight().x(), 0,
		buttonsize.width() - iconrect.topRight().x(),
		buttonsize.height() * MAIN_TEXT_WIDTH_PART
	);
	const QRect hinttextrect = QRect(
		maintextrect.topLeft().x(),
		maintextrect.bottomLeft().y(),
		buttonsize.width() - maintextrect.topLeft().x(),
		buttonsize.height() * (1 - MAIN_TEXT_WIDTH_PART)
	);
}

namespace mofipgui {


	GetStartedMenuButton::GetStartedMenuButton(QString iconpath, QWidget* pwgt)
		: QPushButton(pwgt)
		, mMainText("Default text")
		, mHintText("This is a field for\n short description")
	{
		setMinimumSize(buttonsize);
		mIcon = QImage(iconpath);
	}

	void GetStartedMenuButton::paintEvent(QPaintEvent* event) {
		QPainter painter(this);
		QColor filler(79, 195, 247);
		QColor border(palette().color(QPalette::Mid));

		if (underMouse()) {
			filler.setAlpha(isDown() ? 65 : 80);
			painter.fillRect(rect(), filler);
			border = QColor(2, 43, 76);
		}

		painter.setPen(QPen(border, 1));
		painter.drawRect(rect().adjusted(0, 0, -1, -1));
		painter.drawImage(iconrect, mIcon);

		painter.setPen(palette().color(QPalette::WindowText));
		QFont f(QApplication::font());
		if (!mMainText.isEmpty()) {
			f.setBold(true);
			f.setPointSize(18);
			painter.setFont(f);
			painter.drawText(maintextrect, Qt::AlignCenter, mMainText);
		}
		if (!mHintText.isEmpty()) {
			f.setPointSize(12);
			f.setBold(false);
			painter.setFont(f);
			painter.drawText(hinttextrect, Qt::AlignCenter, mHintText);
		}
	}

	void GetStartedMenuButton::setMainText(const QString& text) {
		mMainText = text;
	}

	void GetStartedMenuButton::setHintText(const QString& text) {
		mHintText = text;
	}

}
