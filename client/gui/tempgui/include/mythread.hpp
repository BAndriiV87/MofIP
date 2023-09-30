#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <QtWidgets>

namespace tempgui {

	class MyThread : public QThread {
		Q_OBJECT
	public:
		MyThread() {}
		void run();
	};

}

#endif //MYTHREAD_HPP
