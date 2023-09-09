#ifndef DRAW_COMPLEX_CONTROL_H
#define DRAW_COMPLEX_CONTROL_H

#include <iostream>

#include <QtWidgets>

class IDrawComplexControl {
public:
	virtual ~IDrawComplexControl() {}
	virtual void operator()(const QProxyStyle* proxy, QStyle::ComplexControl element, const QStyleOptionComplex* option,
		QPainter* painter, const QWidget* widget) const = 0;
public:
	static bool print_type;
	static void print(bool flag) { print_type = flag; }
	static bool call_standard;
	static void call(bool flag) { call_standard = flag; }
};

IDrawComplexControl* getDrawComplexControl(QStyle::ComplexControl element);

#define methodDrawComplexControl \
		void operator()(const QProxyStyle *proxy, QStyle::ComplexControl element, const QStyleOptionComplex* option, \
								QPainter* painter, const QWidget* widget) const

template <int value>
class DrawComplexControl : public IDrawComplexControl {
	enum { style = value };
public:
	methodDrawComplexControl;
};

#define drawComplexControlClassSceleton(style_type) \
		template <> \
		class DrawComplexControl<QStyle::##style_type> : public IDrawComplexControl { \
			enum { style = QStyle::##style_type }; \
		public: \
			methodDrawComplexControl; \
		};

//drawComplexControlClassSceleton(CC_SpinBox)

#endif // DRAW_COMPLEX_CONTROL_H
