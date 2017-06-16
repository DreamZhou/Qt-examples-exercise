#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QMdiSubWindow>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *edit = ui->menuBar->addMenu(tr("&Edit"));
    QAction *actionOpen =edit->addAction(QIcon(":/myImage/images/open.png"),tr("&Open"));
    actionOpen->setShortcut(QKeySequence("Ctrl+O"));
    ui->mainToolBar->addAction(actionOpen);

    QActionGroup *group = new QActionGroup(this);
    QAction *action_L = group->addAction(tr("&Left Align"));
    QAction *action_R = group->addAction(tr("&Right Align"));
    QAction *action_C = group->addAction(tr("&Center Align"));
    action_L->setCheckable(true);
    action_R->setCheckable(true);
    action_C->setCheckable(true);
    action_L->setChecked(true);

    edit->addSeparator();
    edit->addAction(action_L);
    edit->addAction(action_R);
    edit->addAction(action_C);

    QToolButton *toolbtn = new QToolButton(this);
    toolbtn->setText(tr("Color"));
    QMenu *colorMenu = new QMenu(this);
    colorMenu->addAction(tr("Red"));
    colorMenu->addAction(tr("Green"));
    toolbtn->setMenu(colorMenu);
    toolbtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->mainToolBar->addWidget(toolbtn);

    QSpinBox *spinbox = new QSpinBox(this);
    ui->mainToolBar->addWidget(spinbox);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    // 新建文本编辑器部件
    QTextEdit *edit = new QTextEdit(this);
    //使用QMdiArea类的addSubWindow() 创建子窗口
    QMdiSubWindow *child = ui->mdiArea->addSubWindow(edit);
    child->setWindowTitle(tr("多文档编辑器子窗口"));
    child->show();
}

void MainWindow::on_actionShow_Dock_triggered()
{
    ui->dockWidget_2->show();
}
