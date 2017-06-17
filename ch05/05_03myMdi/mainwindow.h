#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MdiChild;
class QMdiSubWindow;
class QSignalMapper;
class QLabel;
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
    void on_action_New_triggered();
    void updateMenus();         // 更新菜单
    MdiChild *createMdiChild();  //创建子窗口
    void setActiveSubWindow(QWidget * window);  //设置活动子窗口
    void updateWindowMenu();
    void showTextRowAndCol();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_actionExit_triggered();

    void on_action_Undo_triggered();

    void on_action_Redo_triggered();

    void on_actionCu_T_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_actionClose_triggered();

    void on_actionClose_All_triggered();

    void on_actionSave_As_triggered();

    void on_actionTile_triggered();

    void on_actionCascade_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

    void on_actionAbout_Qt_triggered();

    void on_action_About_triggered();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow * ui;
    QAction * actionSeparator;   //间隔器
    QMdiSubWindow *findMidChild(const QString &fileName); //查找子窗口
    QSignalMapper *windowMapper;
    QLabel *label ;
    QLabel *RowColLabel ;
    // private methods
    MdiChild *activeMdiChild();  //活动窗口
    void readSettings();
    void writeSettings();
    void initWindow();
};

#endif // MAINWINDOW_H
