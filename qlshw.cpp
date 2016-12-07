#include "qlshw.h"
#include "ui_qlshw.h"
#include <QProcess>
#include <QDebug>
#include <QAbstractItemModel>
#include <QClipboard>
#include "autotooltipdelegate.h"

#include "treemodel.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTree();
    setWindowIcon(QIcon(":/icons/motherboard.svg"));
}

void MainWindow::updateTree()
{
    QProcess lshw;
    if(ui->actionRun_as_Superuser->isChecked())
        lshw.start("gksudo lshw");
    else
        lshw.start("lshw");
    if(!lshw.waitForStarted())
    {
        ui->statusBar->showMessage("Failed to start lshw");
        return;
    }
    if(!lshw.waitForFinished())
    {
        ui->statusBar->showMessage("lshw did not finish");
        return;
    }
    QByteArray result = lshw.readAll();
    QString error = lshw.readAllStandardError();
    ui->statusBar->showMessage(error);

    TreeModel *model = new TreeModel(result);
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
    ui->treeView->resizeColumnToContents(0);
    QAction *action1=new QAction("Copy", this);
    ui->treeView->addAction(action1);
    connect(action1, SIGNAL(triggered()), this, SLOT(on_actionCopy_triggered()));
    ui->treeView->setItemDelegate( new AutoToolTipDelegate( ui->treeView ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit(0);
}

void MainWindow::on_actionRefresh_triggered()
{
    updateTree();
}

void MainWindow::on_actionCopy_triggered()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->treeView->model()->data(ui->treeView->currentIndex()).toString());

}
