#ifndef ENTRADASFRAME_H
#define ENTRADASFRAME_H

#include <QFrame>

namespace Ui {
    class EntradasFrame;
}

class EntradasFrame : public QFrame
{
    Q_OBJECT

public:
    explicit EntradasFrame(QWidget *parent = 0);
    ~EntradasFrame();

private:
    Ui::EntradasFrame *ui;
};

#endif // ENTRADASFRAME_H
