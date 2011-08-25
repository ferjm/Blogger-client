#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "postframe.h"
#include "commentframe.h"
#include "qtgdata/qtgdataoauthdata.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);        
    connect(this->ui->exitButton,SIGNAL(clicked()),this,SLOT(close()));

    ui->editPostFrame->hide();
    this->_currentEntry = NULL;

    OAuthData *auth = new OAuthData();
    auth->setConsumerKey("anonymous");
    auth->setConsumerSecret("anonymous");
    //set on fire :|
    auth->setToken("1/6GfvJfI1j_FYT76XeDQKdlC-xzCUoZEnhcoQfyuTPB8");
    auth->setTokenSecret("nGSmuX77MkHdpsu0DFlZDTH1");
    bloggerClient = new QtgdataBloggerClient(auth);
    connect(bloggerClient,SIGNAL(listOfPostsRetrieved(AtomFeed*)),this,SLOT(onPostsRetrieved(AtomFeed*)));
    connect(bloggerClient,SIGNAL(listOfCommentsRetrieved(AtomFeed*)),this,SLOT(onCommentsRetrieved(AtomFeed*)));
    connect(ui->newButton,SIGNAL(clicked()),ui->editPostFrame,SLOT(show()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancelEdit()));
    connect(ui->publishButton,SIGNAL(clicked()),this,SLOT(publish()));
    this->retrievePosts();
    this->retrieveComments();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bloggerClient;
}

void MainWindow::resizeRow(int n,bool expand)
{
    if(expand)
        ui->tableWidget->setRowHeight(n,200);
    else
        ui->tableWidget->setRowHeight(n,40);

}

void MainWindow::onPostsRetrieved(AtomFeed* bloggerFeed)
{
    ui->tableWidget->hide();
    if(ui->tableWidget->rowCount() > 0)
    {
        for(int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->cellWidget(i,0)->deleteLater();
            ui->tableWidget->removeCellWidget(i,0);
            ui->tableWidget->removeRow(i);
        }
        ui->tableWidget->removeColumn(0);
        ui->tableWidget->insertColumn(0);
    }
    ui->tableWidget->setColumnWidth(0,761);
    for(int i=0; i < (bloggerFeed->entries.size()); i++)
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setRowHeight(i,40);
        PostFrame *p = new PostFrame(i,
                                     bloggerFeed->entries.at(i)->id,
                                     bloggerFeed->entries.at(i)->title,
                                     bloggerFeed->entries.at(i)->content.content,
                                     bloggerFeed->entries.at(i),
                                     bloggerClient,
                                     this);        
        ui->tableWidget->setCellWidget(i,0,p);
        connect(p,SIGNAL(rowChanged(int,bool)),this,SLOT(resizeRow(int,bool)));
        connect(p,SIGNAL(rowDeleted()), this, SLOT(retrievePosts()));
        connect(p,SIGNAL(editPost(AtomEntry*)),this,SLOT(editPost(AtomEntry*)));
    }    
    ui->tableWidget->show();
}

void MainWindow::onCommentsRetrieved(AtomFeed *commentsFeed)
{
    ui->commentsTableWidget->hide();
    if(ui->commentsTableWidget->rowCount() > 0)
    {
        for(int i=0; i<ui->commentsTableWidget->rowCount(); i++)
        {
            ui->commentsTableWidget->cellWidget(i,0)->deleteLater();
            ui->commentsTableWidget->removeCellWidget(i,0);
            ui->commentsTableWidget->removeRow(i);
        }
        ui->commentsTableWidget->removeColumn(0);
        ui->commentsTableWidget->insertColumn(0);
    }
    ui->commentsTableWidget->setColumnWidth(0,761);
    for(int i=0; i < (commentsFeed->entries.size()); i++)
    {
        ui->commentsTableWidget->insertRow(i);
        ui->commentsTableWidget->setRowHeight(i,60);
        CommentFrame *c = new CommentFrame(i,
                                           commentsFeed->entries.at(i)->id,
                                           QString("i"),
                                           commentsFeed->entries.at(i)->title,
                                           commentsFeed->entries.at(i)->content.content,
                                           commentsFeed->entries.at(i)-> published,
                                           this
                                           );
        ui->commentsTableWidget->setCellWidget(i,0,c);
    }
    ui->commentsTableWidget->show();
}

void MainWindow::retrievePosts()
{
    bloggerClient->retrieveListOfPosts("3191627804715422166");
}

void MainWindow::retrieveComments()
{
    bloggerClient->retrieveListOfComments("3191627804715422166");
}

void MainWindow::editPost(AtomEntry* entry)
{
    this->_currentEntry = entry;
    ui->titleTextEdit->setText(entry->title);
    ui->contentcTextEdit->setText(entry->content.content);
    ui->editPostFrame->show();
}

void MainWindow::cancelEdit()
{
    this->_currentEntry = NULL;
    ui->titleTextEdit->clear();
    ui->contentcTextEdit->clear();
    ui->editPostFrame->hide();
}

void MainWindow::publish()
{
    if(!this->_currentEntry)
    {
        if((!ui->titleTextEdit->toPlainText().isEmpty())&&(!ui->contentcTextEdit->toPlainText().isEmpty()))
            this->bloggerClient->createPost("3191627804715422166",
                                            ui->titleTextEdit->toPlainText(),
                                            QByteArray(ui->contentcTextEdit->toPlainText().toAscii()));
        //TODO: else        
    }
    else
    {
        qDebug() << this->_currentEntry->published.toString(Qt::ISODate);
        this->_currentEntry->title = ui->titleTextEdit->toPlainText();
        this->_currentEntry->content.content = QByteArray(ui->contentcTextEdit->toPlainText().toAscii());
        this->bloggerClient->updatePost(*(this->_currentEntry));
    }
    retrievePosts();
    cancelEdit();
}
