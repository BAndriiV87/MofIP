#include <QtWidgets>
#include <MofIPWidgets/SimpleWidget.hpp>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QWidget wgt;
    SimpleWidget* pcw = new SimpleWidget;
    QScrollBar* phsb = new QScrollBar(Qt::Horizontal);

    phsb->setRange(0, 100);

    QObject::connect(phsb, SIGNAL(valueChanged(int)), pcw, SLOT(slotSetProgress(int)));

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pcw);
    pvbxLayout->addWidget(phsb);
    wgt.setLayout(pvbxLayout);

    wgt.show();

    return app.exec();
}
