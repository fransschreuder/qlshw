#include "qlshw.h"
#include "ui_qlshw.h"
#include <QProcess>
#include <QDebug>
#include <QAbstractItemModel>
#include <QClipboard>
#include <QMessageBox>
#include <QLocale>
#include "autotooltipdelegate.h"
#include "version.h"

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
        ui->statusBar->showMessage(tr("Failed to start lshw"));
        return;
    }
    if(!lshw.waitForFinished())
    {
        ui->statusBar->showMessage(tr("lshw did not finish"));
        return;
    }
    QByteArray result = lshw.readAll();
    QString error = lshw.readAllStandardError();
    ui->statusBar->showMessage(error);

    TreeModel *model = new TreeModel(result);
    ui->treeView->setModel(model);
    ui->treeView->expandAll();
    ui->treeView->resizeColumnToContents(0);
    QAction *action1=new QAction(tr("Copy"), this);
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

void MainWindow::on_actionRun_as_Superuser_triggered()
{
    updateTree();
}

void MainWindow::on_actionAbout_qlshw_triggered()
{
    QString s;
    QMessageBox::about(this, tr("About qlshw"), tr("<H1>QLSHW v")+s.sprintf("%1.1f",QLSHW_VERSION)+tr("</H1>qlshw is a simple gui that simply parses the text output of lshw into a Qt TreeView object.\
                    <br/><br/>Developers:<ul><li>Frans Schreuder: <a href=\"mailto:info@schreuderelectronics.com\">info@schreuderelectronics.com</a></li></ul><br/>Website and code:\
                    <a href=\"https://github.com/fransschreuder/qlshw/wiki\">https://github.com/fransschreuder/qlshw/wiki</a><br/><br/>License: <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GNU GPL 3.0</a>"));
}
