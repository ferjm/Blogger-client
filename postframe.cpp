#include "postframe.h"
#include "ui_postframe.h"
#include "mainwindow.h"
#include <QDesktopServices>

PostFrame::PostFrame(int row,
                     QString postId,
                     QString title,
                     QByteArray content,
                     AtomEntry *entry,
                     QtgdataBloggerClient *bloggerClient,
                     QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PostFrame)
{
    ui->setupUi(this);

    this->_bloggerClient = bloggerClient;
    this->_arrowClosed = true;
    this->_postId = postId;
    this->_row = row;
    this->ui->titleLabel->setText(title);
    this->ui->contentTextEdit->setText(QString(content));
    this->ui->dateLabel->setText(entry->published.toString());

    _entry = entry;

    connect(ui->arrowButton, SIGNAL(clicked()), this, SLOT(changeArrow()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deletePost()));
    connect(ui->editButton,SIGNAL(clicked()),this,SLOT(onEditClicked()));
    connect(ui->viewButton,SIGNAL(clicked()),this,SLOT(viewPost()));
}

PostFrame::~PostFrame()
{
    delete ui;
    delete _entry;
}

void PostFrame::deletePost()
{
    this->_bloggerClient->deletePost("3191627804715422166",this->_postId);    
    emit rowDeleted();
}

void PostFrame::changeArrow()
{
    if(this->_arrowClosed)
    {
        ui->arrowButton->setStyleSheet("background-image: url(:/images/res/arrow_open.gif);");
        emit rowChanged(_row,true);
    }
    else
    {
        ui->arrowButton->setStyleSheet("background-image: url(:/images/res/arrow.gif);");
        emit rowChanged(_row,false);
    }
    this->_arrowClosed =! this->_arrowClosed;
}

void PostFrame::onEditClicked()
{
    emit editPost(_entry);
}

void PostFrame::viewPost()
{
    QDesktopServices::openUrl(QUrl("http://gdataqtclient.blogspot.com/"));
}
