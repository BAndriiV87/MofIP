#ifndef START_WINDOW_HPP
#define START_WINDOW_HPP

#include "FramelessWindow.hpp"

namespace mofipgui {
	class StartWindow : public FramelessWindow {
	public:
		StartWindow(QWidget* wgt = nullptr);
	private:
		QPushButton* hello;
		QPushButton* buy;
		QLabel* name;
	};
}

#endif // START_WINDOW_HPP
