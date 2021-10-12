#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include "gamewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TitleWidget; }
QT_END_NAMESPACE

class TitleWidget : public QWidget
{
    Q_OBJECT
    QPixmap titleimg;

public:
    TitleWidget(QWidget *parent = nullptr);
    ~TitleWidget();

    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::TitleWidget *ui;

signals:
    void startGame();
};
#endif // TITLEWIDGET_H
