#include "commentframe.h"
#include "ui_commentframe.h"

CommentFrame::CommentFrame(int row,
                           QString commentId,
                           QString postId,
                           QString postTitle,
                           QByteArray content,
                           QDateTime date,
                           QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CommentFrame)
{
    ui->setupUi(this);

    this->ui->contentLabel->setText(content);
    this->ui->fechaLabel->setText(date.toString());

    this->_postId = postId;
    this->_commentId = commentId;
}

CommentFrame::~CommentFrame()
{
    delete ui;
}
