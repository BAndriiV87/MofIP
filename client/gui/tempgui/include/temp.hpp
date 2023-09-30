#ifndef TEMP_HPP
#define TEMP_HPP

#include <QtWidgets>

namespace tempgui {
    class Temp : public QObject {
        Q_OBJECT
    public:
        Temp(QObject* pobj = nullptr) : QObject(pobj) {}
    public slots:
        void number();
    };
}

#endif //TEMP_HPP
