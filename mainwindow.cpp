#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "postframe.h"
#include "qtgdata/qtgdataoauthdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);        
    connect(this->ui->exitButton,SIGNAL(clicked()),this,SLOT(close()));

    OAuthData *auth = new OAuthData();
    auth->setConsumerKey("anonymous");
    auth->setConsumerSecret("anonymous");
    //set on fire :|
    auth->setToken("1/6GfvJfI1j_FYT76XeDQKdlC-xzCUoZEnhcoQfyuTPB8");
    auth->setTokenSecret("nGSmuX77MkHdpsu0DFlZDTH1");
    bloggerClient = new QtgdataBloggerClient(auth);
    connect(bloggerClient,SIGNAL(listOfPostsRetrieved(AtomFeed*)),this,SLOT(onPostsRetrieved(AtomFeed*)));
    this->retrievePosts();
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
        ui->tableWidget->clear();
        ui->tableWidget->clearContents();
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
                                     bloggerClient,
                                     this);
        ui->tableWidget->setCellWidget(i,0,p);
        connect(p,SIGNAL(rowChanged(int,bool)),this,SLOT(resizeRow(int,bool)));
        connect(p,SIGNAL(rowDeleted()), this, SLOT(retrievePosts()));
    }    
    ui->tableWidget->show();
}

void MainWindow::retrievePosts()
{
    bloggerClient->retrieveListOfPosts("3191627804715422166");
}
