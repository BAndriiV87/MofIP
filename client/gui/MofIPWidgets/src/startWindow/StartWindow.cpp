#include <QtWidgets>

#include "startWindow/StartWindow.hpp"

namespace mofipgui {

	StartWindow::StartWindow(QWidget* wgt) 
		: FramelessWindow(wgt)
	{
		setMinimumSize(640, 480);
		hello = new QPushButton(tr("HELLO"));
		hello->setMinimumWidth(100);
		buy = new QPushButton(tr("GOOD BUY"));
		buy->setMinimumWidth(30);

		QHBoxLayout* hl = new QHBoxLayout;
		hl->addWidget(hello);
		hl->addStretch();
		hl->addWidget(buy);

		QString labeltext(tr("MofIP Application 2023"));
		QFont namefont(tr("Ink Free"), 22, QFont::Bold);

		name = new QLabel(labeltext, this);
		name->setFont(namefont);
		name->setMinimumWidth(QFontMetrics(namefont).width(labeltext));
		name->move(20, 20);

		QVBoxLayout* vl = new QVBoxLayout;
		vl->addSpacing(titlebarHeight());
		vl->addStretch();
		vl->addLayout(hl);

		setLayout(vl);
	}

}