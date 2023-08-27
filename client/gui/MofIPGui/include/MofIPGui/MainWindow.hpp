#ifndef MOFIP_MAIN_WINDOW_HPP
#define MOFIP_MAIN_WINDOW_HPP

#include <QWidget>
#include <QMainWindow>

namespace MofIPGui {

	class MainWindow : public QMainWindow {
		Q_OBJECT
	private:
		void init();
	public:
		MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	};

}

#endif // MOFIP_MAIN_WINDOW_HPP
