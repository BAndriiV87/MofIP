#include <QtWidgets>
#include <MofipWidgets.hpp>

#include "guiConfig.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {

	/* MofIPPushButton Exemple */
	QApplication app(argc, argv);

	QWidget wgt;

	MofIPWidgets::IWidgetsFactory* wgtFactory = new MofIPWidgets::MofIPWidgetFactory;

	QPushButton* cst1 = wgtFactory->createPushButton(QString("Cancel"));
	QPushButton* cst2 = wgtFactory->createPushButton(QString("OK"));
	QPushButton* cst3 = wgtFactory->createPushButton(QString("Quit"));

	cst1->setMinimumSize(50, 50);
	cst2->setMinimumSize(50, 50);
	cst3->setMinimumSize(50, 50);
	qDebug() << "[SIZE] " << cst1->size() << endl;

	QVBoxLayout* vbxlayout = new QVBoxLayout;
	vbxlayout->addWidget(cst1);
	vbxlayout->addWidget(cst2);
	vbxlayout->addWidget(cst3);

	wgt.setLayout(vbxlayout);

	wgt.show();
    return app.exec();

}
