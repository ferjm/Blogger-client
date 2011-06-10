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

public slots:
    void resizeRow(int n, bool expand);
    void onPostsRetrieved(AtomFeed*);
    void retrievePosts();
};

#endif // MAINWINDOW_H
