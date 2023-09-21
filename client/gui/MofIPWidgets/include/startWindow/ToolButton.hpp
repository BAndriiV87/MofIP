#ifndef TOOL_BUTTON_HPP
#define TOOL_BUTTON_HPP

#include <QtWidgets>
#include "CommonDefinitions.hpp"

namespace mofipgui {

    class ToolButtonPainter {
    protected:
        ToolButtonPainter() { }
        virtual void drawIcon(QPainter& painter) = 0;
    public:
        virtual ~ToolButtonPainter() { }
        void enter(QPainter& painter);
        void leave(QPainter& painter);
        void press(QPainter& painter);
    protected:
        QColor mButtonColor = QApplication::palette().color(QPalette::Window);
        QColor mEnterColor = QColor(QApplication::palette().color(QPalette::WindowText).red(),
                                    QApplication::palette().color(QPalette::WindowText).green(),
                                    QApplication::palette().color(QPalette::WindowText).blue(),
                                    50);
        QColor mTransparentMaskColor = QColor(QApplication::palette().color(QPalette::Window).red(),
                                              QApplication::palette().color(QPalette::Window).green(),
                                              QApplication::palette().color(QPalette::Window).blue(),
                                              70);
    };

    class CloseButtonPainter : public ToolButtonPainter {
    protected:
        void drawIcon(QPainter& painter) override;
    public:
        CloseButtonPainter();
    };

    class CollapseButtonPainter : public ToolButtonPainter {
    protected:
        void drawIcon(QPainter& painter) override;
    };

    class MaxButtonPainter : public ToolButtonPainter {
    protected:
        void drawIcon(QPainter& painter) override;
    };

    class MinButtonPainter : public ToolButtonPainter {
    protected:
        void drawIcon(QPainter& painter) override;
    public:
        MinButtonPainter();
    private:
        QPainterPath path;
        QRect overRect;
        QRect underRect;
    };

    template<typename ButtonPainter>
    class ToolButton : public QPushButton {
    protected:
        void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE {
            QPainter painter(this);
            if (underMouse())
                mButtonPainter.enter(painter);
            else
                mButtonPainter.leave(painter);
            if (isDown()) mButtonPainter.press(painter);
        }
    public:
        ToolButton(QWidget* pwgt = nullptr)
            : QPushButton(pwgt)
        {
            QPalette pal(palette());
            pal.setColor(QPalette::Window, QApplication::palette().color(QPalette::Window));
            setPalette(pal);
            setFixedSize(TOOL_BUTTON_RECT.size());
        }
    private:
        ButtonPainter mButtonPainter;
    };
}

#endif // TOOL_BUTTON_HPP
