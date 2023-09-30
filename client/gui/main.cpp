#include <QtWidgets>

#include <iostream>
#include <string>

#include "guiConfig.h"
#include "mofipwidgets.hpp"

//#include "tempgui.hpp"

int main(int argc, char **argv) {

	QApplication app(argc, argv);

	QApplication::setFont(QFont("Ink Free"));

	QPalette pal = QApplication::palette();
	pal.setColor(QPalette::Window, QColor(36, 36, 36, 255));
	pal.setColor(QPalette::WindowText, Qt::white);
	QApplication::setPalette(pal);
	
	mofipgui::GetStartedWindow wgt;
	wgt.resize(300, 300);
	wgt.show();

	return app.exec();
}
