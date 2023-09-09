#include <QtWidgets>
//#include <MofIPWidgets.hpp>
//#include <MofIPGui.hpp>

#include "MofIPStyle.h"

#include "guiConfig.h"
#include <iostream>
#include <string>

QGroupBox* buttonbox(QWidget* wgt = nullptr);
void widgetgroup(QWidget* wgt);

int main(int argc, char **argv) {
	/*
		QApplication::setStyle(new MofIPStyle);
		QApplication app(argc, argv);
		QWidget *wgt = new QWidget;
		auto grpbx = buttonbox(wgt);
		grpbx->move(50, 50);
		wgt->resize(640, 480);
		wgt->show();
		return app.exec();
	*/

	//QApplication::setStyle(new MofIPStyle);
	QApplication app(argc, argv);

	QWidget wgt;

	QTabWidget tab(&wgt);
	tab.setTabPosition(QTabWidget::East);
	QStringList lst;
	
	lst << "Linux" << "Windows" << "MacOSX" << "Android";
	foreach(QString str, lst) {
		tab.addTab(new QLabel(str, &tab), str);
	}
	tab.resize(350, 250);
	tab.move(30, 30);

	auto *boxbutton = buttonbox(&wgt);
	boxbutton->move(30, 300);

	wgt.resize(640, 480);
	wgt.show();

	return app.exec();
}

QGroupBox* buttonbox(QWidget *wgt) {
	QPushButton* btns[4]{};
	int btnsize = sizeof(btns) / sizeof(QPushButton*);
	btns[0] = new QPushButton("Disable");
	btns[0]->setEnabled(false);
	btns[1] = new QPushButton("Button Rise");
	btns[2] = new QPushButton("Button Down");
	btns[2]->setDown(true);
	btns[3] = new QPushButton("Flat Button");
	btns[3]->setFlat(true);
	for (int i = 0; i < btnsize; ++i)
		btns[i]->setMinimumSize(100, 30);
	QGridLayout* grd = new QGridLayout;
	grd->setMargin(10);
	grd->setSpacing(10);
	grd->addWidget(btns[0], 0, 0);
	grd->addWidget(btns[1], 0, 1);
	grd->addWidget(btns[2], 1, 0);
	grd->addWidget(btns[3], 1, 1);

	// Group box layout
	QGroupBox* grpbx;
	if (wgt)
		grpbx = new QGroupBox("Group Box", wgt);
	else
		grpbx = new QGroupBox("Group Box");

	grpbx->setLayout(grd);

	return grpbx;
}
void widgetgroup(QWidget* wgt) {
	QPushButton* A = new QPushButton("Button 1");
	A->setMinimumSize(120, 30);
	QPushButton* B = new QPushButton("Button 2");
	B->setMinimumSize(120, 30);

	QSplitter* vspl = new QSplitter(Qt::Vertical);
	vspl->addWidget(A);
	vspl->addWidget(B);

	QSplitter* hspl = new QSplitter(Qt::Horizontal);
	QWidget* wspl = new QWidget;

	auto grpbx = buttonbox(wspl);
	grpbx->move(50, 50);

	hspl->addWidget(wspl);
	hspl->addWidget(vspl);
	hspl->resize(200, 200);

	hspl->show();
}
