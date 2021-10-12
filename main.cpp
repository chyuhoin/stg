#include "titlewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TitleWidget w;
    w.show();
    return a.exec();
}
