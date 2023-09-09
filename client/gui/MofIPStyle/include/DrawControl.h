#ifndef DRAW_CONTROL_H
#define DRAW_CONTROL_H

#include <iostream>

#include <QtWidgets>

class IDrawControl {
public:
	virtual ~IDrawControl() {}
	virtual void operator()(const QProxyStyle* proxy, QStyle::ControlElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget) const = 0;
public:
	static bool print_type;
	static void print(bool flag) { print_type = flag; }
	static bool call_standard;
	static void call(bool flag) { call_standard = flag; }
};

IDrawControl* getDrawControl(QStyle::ControlElement element);

#define methodDrawControl \
		void operator()(const QProxyStyle *proxy, QStyle::ControlElement element, const QStyleOption* option, \
								QPainter* painter, const QWidget* widget) const

template <int value>
class DrawControl : public IDrawControl {
public:
	methodDrawControl;
};

#define drawControlClassSceleton(style_type) \
		template <> \
		class DrawControl<QStyle::##style_type> : public IDrawControl { \
			enum { style = QStyle::##style_type }; \
		public: \
			methodDrawControl; \
		}

drawControlClassSceleton(CE_TabBarTab);
drawControlClassSceleton(CE_TabBarTabLabel);
drawControlClassSceleton(CE_PushButtonLabel);

#endif // DRAW_CONTROL_H
