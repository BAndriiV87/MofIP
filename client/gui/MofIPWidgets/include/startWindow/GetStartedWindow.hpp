#ifndef START_WINDOW_HPP
#define START_WINDOW_HPP

#include "FramelessWindow.hpp"
#include "GetStartedMenuButton.hpp"

namespace mofipgui {
	class GetStartedWindow : public FramelessWindow {
	public:
		GetStartedWindow(QWidget* wgt = nullptr);
	private:
		QLabel* m_plblAppName;
		GetStartedMenuButton* m_pbtnCreateProject;
		GetStartedMenuButton* m_pbtnOpenProject;
		GetStartedMenuButton* m_pbtnCloneProject;
	};
}

#endif // START_WINDOW_HPP
