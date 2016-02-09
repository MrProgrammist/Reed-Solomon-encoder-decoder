#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class QString;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    quint16 checkTable[32][2];
    quint16 dataAfterCoder;
    quint16 dataAfterDistortion;
    quint16 dataAfterDecoder;
    quint16 userData;

    void coding();
    void decoding();
    void distortion();
    void showResult();

private slots:
    void buttonClicked();
};

#endif // WIDGET_H
