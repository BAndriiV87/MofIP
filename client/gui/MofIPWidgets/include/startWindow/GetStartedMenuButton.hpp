#ifndef GET_STARTED_MENU_BUTTON_HPP
#define GET_STARTED_MENU_BUTTON_HPP

#include <QPushButton>

class QPaintEvent;

namespace mofipgui {

	class GetStartedMenuButton : public QPushButton {
	public:
		GetStartedMenuButton(QString iconpath, QWidget* pwgt = nullptr);
		void setMainText(const QString& text);
		void setHintText(const QString& text);
	public:
		void paintEvent(QPaintEvent* event);
	private:
		QImage mIcon;
		QString mMainText;
		QString mHintText;
	};

}

#endif // GET_STARTED_MENU_BUTTON_HPP
