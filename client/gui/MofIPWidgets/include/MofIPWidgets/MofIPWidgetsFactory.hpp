#ifndef MOFIP_WIDGETS_FACTORY_HPP
#define MOFIP_WIDGETS_FACTORY_HPP

#include <QtWidgets>
#include <memory>

#include "MofIPWidgets/MofIPPushButton.hpp"

namespace MofIPWidgets {

	class IWidgetsFactory {
	public:
		virtual ~IWidgetsFactory() {}
	public:
		virtual QPushButton* createPushButton(const QString& text, QWidget* parent = nullptr) = 0;
		virtual QPushButton* createPushButton(QWidget* parent = nullptr) = 0;
	};

	class MofIPWidgetFactory : public IWidgetsFactory {
	public:
		QPushButton* createPushButton(const QString& text, QWidget* parent = nullptr) override;
		QPushButton* createPushButton(QWidget* parent = nullptr) override;
	};

	class QtWidgetFactory : public IWidgetsFactory {
	public:
		QPushButton* createPushButton(const QString& text, QWidget* parent = nullptr) override;
		QPushButton* createPushButton(QWidget* parent = nullptr) override;
	};

}

#endif // MOFIP_WIDGETS_FACTORY_HPP
