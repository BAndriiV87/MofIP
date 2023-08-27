#include <QtWidgets>
#include <MofipWidgets.hpp>
#include <MofIPGui.hpp>

#include "guiConfig.h"
#include <iostream>
#include <string>

#define commandPrint(command) qDebug() << "[" << #command << "] "<< command << endl

void widgetgroup1(QWidget* wgt);
void widgetgroup2(QWidget* wgt);

int main(int argc, char **argv) {

	/*Q_INIT_RESOURCE(styles);

	QApplication::setStyle(new MyStyle);

	QApplication app(argc, argv);
	MyWindow gallery;
	gallery.show();
	return app.exec();*/

	/*QApplication app(argc, argv);

	MofIPWidgets::IWidgetsFactory* wgtFactory = new MofIPWidgets::MofIPWidgetFactory;

	MofIPGui::MainWindow mw;
	commandPrint(mw.geometry());

	QPushButton* btn = wgtFactory->createPushButton(&mw);
	btn->setText("Button");
	btn->resize(150, 40);
	btn->move(200, 200);

	mw.resize(640, 480);
	mw.show();

	return app.exec();*/
	// ===============================

	QApplication app(argc, argv);

	QWidget *wgt = new QWidget;
	widgetgroup2(wgt);

	return app.exec();

	/* MofIPPushButton Exemple */
	/*QApplication app(argc, argv);

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
    return app.exec();*/

}

QGroupBox* buttonbox() {
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
	QGroupBox* grpbx = new QGroupBox("Group Box");
	grpbx->setLayout(grd);

	return grpbx;
}

void widgetgroup1(QWidget* wgt) {

	// Configure main layout
	QGridLayout* mainLayout = new QGridLayout;
	//mainLayout->addLayout(grd, 0, 0);
	mainLayout->addWidget(buttonbox(), 0, 0);

	wgt->setLayout(mainLayout);
	wgt->show();
}

void widgetgroup2(QWidget* wgt) {
	QPushButton* A = new QPushButton("Button 1");
	A->setMinimumSize(120, 30);
	QPushButton* B = new QPushButton("Button 2");
	B->setMinimumSize(120, 30);

	QSplitter* vspl = new QSplitter(Qt::Vertical);
	vspl->addWidget(A);
	vspl->addWidget(B);

	QSplitter* hspl = new QSplitter(Qt::Horizontal);
	hspl->addWidget(buttonbox());
	hspl->addWidget(vspl);
	hspl->resize(200, 200);

	hspl->show();

}
