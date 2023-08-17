#include <QtWidgets>
#include <MofipWidgets.hpp>

#include "guiConfig.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {

	QApplication app(argc, argv);

	QWidget wgt;

	MofIPWidgets::MofIPPushButton* cst1 = new MofIPWidgets::MofIPPushButton(QString("Cancel"));
	MofIPWidgets::MofIPPushButton* cst2 = new MofIPWidgets::MofIPPushButton(QString("OK"));
	MofIPWidgets::MofIPPushButton* cst3 = new MofIPWidgets::MofIPPushButton(QString("Quit"));

	QPushButton* btn = new QPushButton("Button");
	qDebug() << "[SIZE] " << btn->minimumSizeHint() << endl;
	qDebug() << "[SIZE] " << cst1->minimumSizeHint() << endl;

	QVBoxLayout* vbxlayout = new QVBoxLayout;
	vbxlayout->addWidget(cst1);
	vbxlayout->addWidget(cst2);
	vbxlayout->addWidget(cst3);
	vbxlayout->addWidget(btn);

	wgt.setLayout(vbxlayout);

	wgt.show();

    return app.exec();
}
