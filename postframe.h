#ifndef POSTFRAME_H
#define POSTFRAME_H

#include <QFrame>
#include <qtgdata/qtgdatabloggerclient.h>

namespace Ui {
    class PostFrame;
}

class PostFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PostFrame(int row,
                       QString postId,
                       QString title,
                       QByteArray content,
                       QtgdataBloggerClient *bloggerClient,
                       QWidget *parent = 0);
    ~PostFrame();

private:
    Ui::PostFrame *ui;

    QtgdataBloggerClient *_bloggerClient;

    bool _arrowClosed;
    int _row;
    QString _postId;

private slots:
    void deletePost();

public slots:
    void changeArrow();

signals:
    void rowChanged(int row,bool expand);
    void rowDeleted();
};

#endif // POSTFRAME_H
