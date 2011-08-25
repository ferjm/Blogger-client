#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtgdata/qtgdatabloggerclient.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtgdataBloggerClient *bloggerClient;
    AtomEntry *_currentEntry;

public slots:
    void resizeRow(int n, bool expand);
    void onPostsRetrieved(AtomFeed*);
    void onCommentsRetrieved(AtomFeed*);
    void retrievePosts();
    void retrieveComments();
    void editPost(AtomEntry* entry);
    void cancelEdit();
    void publish();
};

#endif // MAINWINDOW_H
