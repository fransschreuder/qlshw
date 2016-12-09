#ifndef QLSHW_H
#define QLSHW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionRefresh_triggered();

    void on_actionCopy_triggered();

    void on_actionRun_as_Superuser_triggered();

    void on_actionAbout_qlshw_triggered();

private:
    Ui::MainWindow *ui;
    void updateTree(void);
};

#endif // QLSHW_H
