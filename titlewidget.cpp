#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QLabel>
#include<QKeyEvent>

TitleWidget::TitleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    setFixedSize(1024, 960);

    GameWidget *game = new GameWidget();

    titleimg.load(":/pics/title.png");
    QLabel *title = new QLabel(this);
    title->setPixmap(titleimg);
    title->setGeometry(0, 0, titleimg.width(), titleimg.height());

    connect(this, &TitleWidget::startGame, [=](){
        this->hide();
        game->setGeometry(geometry());
        game->show();
        game->playGame();
    });

    connect(game, &GameWidget::endGame, [=](){
        game->hide();
        this->show();
    });
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z)
        emit startGame();
}
