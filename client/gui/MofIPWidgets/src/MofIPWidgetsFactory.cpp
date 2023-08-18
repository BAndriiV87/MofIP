#include "MofIPWidgets/MofIPWidgetsFactory.hpp"

namespace MofIPWidgets {

	// Mofip widget factory methods
	// ----------------------------
	QPushButton* MofIPWidgetFactory::createPushButton(const QString& text, QWidget* parent) {
		return new MofIPPushButton(text, parent);
	}
	QPushButton* MofIPWidgetFactory::createPushButton(QWidget* parent) {
		return new MofIPPushButton(parent);
	}

	// Mofip widget factory methods
	// ----------------------------
	QPushButton* QtWidgetFactory::createPushButton(const QString& text, QWidget* parent) {
		return new QPushButton(text, parent);
	}
	QPushButton* QtWidgetFactory::createPushButton(QWidget* parent) {
		return new QPushButton(parent);
	}

}

