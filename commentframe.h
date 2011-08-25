#ifndef COMMENTFRAME_H
#define COMMENTFRAME_H

#include <QFrame>
#include <QDateTime>

namespace Ui {
    class CommentFrame;
}

class CommentFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CommentFrame(int row,
                          QString commentId,
                          QString postId,
                          QString postTitle,
                          QByteArray content,
                          QDateTime date,
                          QWidget *parent = 0);
    ~CommentFrame();

private:
    Ui::CommentFrame *ui;

    QString _commentId;
    QString _postId;
};

#endif // COMMENTFRAME_H
