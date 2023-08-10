#ifndef SIMPLE_WIDGET_HPP
#define SIMPLE_WIDGET_HPP

#include <QFrame>

class SimpleWidget : public QFrame {
	Q_OBJECT
protected:
	int m_nProcess;

	virtual void paintEvent(QPaintEvent*);
public:
	SimpleWidget(QWidget* pwgt = 0);
	virtual QSize sizeHint() const;
signals:
	void progressChanged(int);
public slots:
	void slotSetProgress(int n);
};

#endif //SIMPLE_WIDGET_HPP
