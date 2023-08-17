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

	QVBoxLayout* vbxlayout = new QVBoxLayout;
	vbxlayout->setContentsMargins(2, 2, 2, 2);
	vbxlayout->addWidget(cst1);
	vbxlayout->addWidget(cst2);
	vbxlayout->addWidget(cst3);
	wgt.setLayout(vbxlayout);

	wgt.show();

    return app.exec();
}
