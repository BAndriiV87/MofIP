#include <QtWidgets>

#include <iostream>
#include <string>

#include "guiConfig.h"
#include "mofipwidgets.hpp"

int main(int argc, char **argv) {

	QApplication app(argc, argv);

	//QPalette pal = QApplication::palette();
	//pal.setColor(QPalette::Window, QColor(36, 36, 36, 255));
	//pal.setColor(QPalette::WindowText, Qt::white);
	//QApplication::setPalette(pal);

	mofipgui::StartWindow wgt;
	wgt.resize(300, 300);
	wgt.show();

	return app.exec();
}
