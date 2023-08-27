#include <MofIPGui/mainWindow.hpp>

namespace MofIPGui {

	MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
		: QMainWindow(parent, flags)
	{
		init();
	}

	void MainWindow::init() {
		QWidget::setWindowFlags( Qt::Window );
		QWidget::setWindowTitle("MofIP Application");
		QPalette plt;
		plt.setColor(this->backgroundRole(), Qt::white);
		setPalette(plt);
	}

}
