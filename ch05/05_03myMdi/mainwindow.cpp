#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QString>
#include <QSignalMapper>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <QDebug>
// TO BE ADD
const QString filterStr = "All type(*.*);; Text files (*.txt);;Flash ActionScript file (*.as *.mx);;"
                          "Ada file(*.ada *.ads *.adb);;Assembly language source file(*.asm);;"
                          "Active Server Pages script file(*.asp);;AutoIt(*.au3);;"
                          "C source file(*.c *.lex);;CMake file(*.cmake);;"
                          "C++ source file(*.h *.hpp *.hxx *.cpp *.cxx *.cc *.ino);;"
                          "C# sourcefile(*.cs)";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
    readSettings();
    actionSeparator = new QAction(this);
    actionSeparator->setSeparator(true);
    updateMenus();
    connect(ui->mdiArea,QMdiArea::subWindowActivated,this,updateMenus);

    // 创建信号映射器  映射器重新发射信号，根据信号设置活动窗口
    windowMapper = new QSignalMapper(this);

    // 下面这信号 函数的转换 没看懂
    connect(windowMapper,static_cast<void(QSignalMapper::*)(QWidget *)>(&QSignalMapper::mapped),this,setActiveSubWindow);

    updateWindowMenu();  // 更新窗口菜单；
    // 设置当窗口菜单将要要显示的时候更新菜单
    connect(ui->menu_Window,QMenu::aboutToShow,this,updateWindowMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMenus()
{
    // 根据是否有活动窗口来设置各个菜单是否可用
    bool hasMdiChild = (activeMdiChild() != 0);
    ui->action_Save->setEnabled(hasMdiChild);
    ui->actionSave_As->setEnabled(hasMdiChild);
    ui->action_Paste->setEnabled(hasMdiChild);
    ui->actionClose->setEnabled(hasMdiChild);
    ui->actionClose_All->setEnabled(hasMdiChild);
    ui->actionTile->setEnabled(hasMdiChild);
    ui->actionCascade->setEnabled(hasMdiChild);
    ui->actionNext->setEnabled(hasMdiChild);
    ui->actionPrevious->setEnabled(hasMdiChild);

    //设置间隔器是否显示
    actionSeparator->setVisible(hasMdiChild);

    //有活动窗口且有被选择的文本，剪切复制才可用
    bool hasSelection = (activeMdiChild() &&
            activeMdiChild()->textCursor().hasSelection());
    ui->actionCu_T->setEnabled(hasSelection);
    ui->action_Copy->setEnabled(hasSelection);

    // 有活动窗口且文档 撤销操作可用
    ui->action_Undo->setEnabled(activeMdiChild()
                       && activeMdiChild()->document()->isUndoAvailable());
    // 有活动窗口且文档 恢复动作可用
    ui->action_Redo->setEnabled(activeMdiChild()
                       && activeMdiChild()->document()->isRedoAvailable() );


}

MdiChild *MainWindow::createMdiChild()
{
   //创建MdiChild 部件
    MdiChild * child = new MdiChild;

    // 向多文档区域添加子窗口，child 为中心部件
    ui->mdiArea->addSubWindow(child);
    //根据QTextEdit类的是否可以复制信号设置剪贴复制动作是否可用
    connect(child,QTextEdit::copyAvailable,ui->action_Copy,QAction::setEnabled);
    connect(child,QTextEdit::copyAvailable,ui->actionCu_T,QAction::setEnabled);
    //根据QTextDocument 类的是否可以撤销恢复信号 设置撤销恢复动作是否可用
    connect(child,QTextEdit::undoAvailable,ui->action_Undo,QAction::setEnabled);
    connect(child,QTextEdit::redoAvailable,ui->action_Redo,QAction::setEnabled);
    connect(child,QTextEdit::cursorPositionChanged,this,showTextRowAndCol);
    return child;
}

// 因为QsignalMapper 的参数时
void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow * >(window));
}

void MainWindow::updateWindowMenu()
{
    //先清空菜单，然后再添加各个菜单动作
    ui->menu_Window->clear();
    ui->menu_Window->addAction(ui->actionClose);
    ui->menu_Window->addAction(ui->actionClose_All);
    ui->menu_Window->addAction(ui->actionTile);
    ui->menu_Window->addAction(ui->actionCascade);
    ui->menu_Window->addSeparator();
    ui->menu_Window->addAction(ui->actionNext);
    ui->menu_Window->addAction(ui->actionPrevious);
    ui->menu_Window->addAction(actionSeparator);

    // 如有窗口，则显示间隔器
    QList<QMdiSubWindow * > windowlists = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windowlists.isEmpty());

    //遍历各个子窗口
    for ( int i = 0 ;i < windowlists.size(); ++i){
        MdiChild * child = qobject_cast<MdiChild *> (windowlists.at(i)->widget());
        QString text;
        // 如果窗口数小于9，则设置编号为快捷键
        if (i < 9){
            text = tr("&%1 %2").arg(i+1).arg(child->userFriendlyCurrentFile());
        }else
            text = tr("%1 %2").arg(i+1).arg(child->userFriendlyCurrentFile());

    QAction * action = ui->menu_Window->addAction(text);

    action->setCheckable(true);
    //设置当前活动窗口动作为选中状态
    action->setChecked(child == activeMdiChild());
    // 关联动作的触发信号到映射器的map()槽，这个槽会发射maped信号
    connect(action, SIGNAL(triggered(bool)), windowMapper,SLOT(map()));
    // 将动作与相应的窗口部件进行映射 在发射mapped信号时 就以这个窗口部件为参数
    windowMapper->setMapping(action,windowlists.at(i));
    }
}

void MainWindow::showTextRowAndCol()
{
    if (activeMdiChild()){
        int rowNum = activeMdiChild()->textCursor().blockNumber() + 1;
        int colNum = activeMdiChild()->textCursor().columnNumber() + 1;
        QString rowCol = tr("  Row: %1 Col %2").arg(rowNum).arg(colNum);
        RowColLabel->setText(rowCol);
//        RowColLabel->setLineWidth(rowCol.size());
//        qDebug() << tr("  Row:%1  Col:%2  ").arg(rowNum).arg(colNum);
    }
}


MdiChild *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow * activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *> (activeSubWindow->widget());
    return nullptr;
}

void MainWindow::readSettings()
{
    QSettings settings("Dream","MDIEdit");
    QPoint pos = settings.value("pos").toPoint();
    QSize size = settings.value("size").toSize();
    move(pos);
    resize(size);
}

void MainWindow::writeSettings()
{
    QSettings settings("Dream","MDIEdit");
    // 写入位置和大小信息
    settings.setValue("pos",pos());
    settings.setValue("size",size());
}

void MainWindow::initWindow()
{
    setWindowTitle((tr("MDIEdit")));
    ui->mainToolBar->setWindowTitle(tr("工具栏"));
    ui->statusBar->showMessage(tr("欢迎使用多文档编辑器"),2000);
    label = new QLabel(this);
    RowColLabel = new QLabel(this);
    RowColLabel->setAlignment(Qt::AlignLeft);
    label->setText(tr("Powerd by Dream"));
    label->setAlignment(Qt::AlignLeft);
    RowColLabel->setText(tr("  Row:%1  Col:%2  ").arg("0").arg("0"));
    ui->statusBar->addPermanentWidget(RowColLabel);
    ui->statusBar->addPermanentWidget(label);


}
QMdiSubWindow *MainWindow::findMidChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    for (auto w : ui->mdiArea->subWindowList()){
        MdiChild * mdiChild = qobject_cast<MdiChild * > (w->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return w;
    }
    return nullptr;
}


// ********************************--signals--******************** //
void MainWindow::on_action_New_triggered()
{
    MdiChild *child = createMdiChild();
    child->newFile();
    child->show();
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select file to open"),"./",
                                                    filterStr);
    if (!fileName.isEmpty()){
        QMdiSubWindow *exitsting = findMidChild(fileName);
        // 如果窗口已经存在，则将对应的子窗口设置为活动窗口
        if (exitsting){
            ui->mdiArea->setActiveSubWindow(exitsting);
            return;
        }
        // 如果没有则新建子窗口
        MdiChild * child = createMdiChild();
        if (child->loadFile(fileName)){
            ui->statusBar->showMessage(tr("File loaded"),2000);  // 2000 ms
            child->show();
        }else {
            child->close();
        }
    }
}



void MainWindow::on_action_Save_triggered()
{
    if (activeMdiChild() && activeMdiChild()->save())
        ui->statusBar->showMessage(tr("File saved"),2000);
}

void MainWindow::on_actionExit_triggered()
{
    //等价于QApplication::closeAllWindows();
    qApp->closeAllWindows();
}

void MainWindow::on_action_Undo_triggered()
{
    if (activeMdiChild())
        activeMdiChild()->undo();
}

void MainWindow::on_action_Redo_triggered()
{
    if (activeMdiChild())
        activeMdiChild()->redo();
}

void MainWindow::on_actionCu_T_triggered()
{
    if (activeMdiChild())
        activeMdiChild()->cut();
}

void MainWindow::on_action_Copy_triggered()
{
    if (activeMdiChild())
        activeMdiChild()->copy();
}

void MainWindow::on_action_Paste_triggered()
{
    if (activeMdiChild())
        activeMdiChild()->paste();
}

void MainWindow::on_actionClose_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionClose_All_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionSave_As_triggered()
{
    if (activeMdiChild() && activeMdiChild()->saveAs())
        ui->statusBar->showMessage(tr("File saved"),2000);
}
// 窗口排列
void MainWindow::on_actionTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}
// 窗口层叠
void MainWindow::on_actionCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}
// 下一个窗口
void MainWindow::on_actionNext_triggered()
{
    ui->mdiArea->activateNextSubWindow();
}

// 上一个窗口 快捷键有问题
void MainWindow::on_actionPrevious_triggered()
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,tr("About MDIEdit"),tr("Copyright by Dream"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 限制性多文档区域的关闭操作
    ui->mdiArea->closeAllSubWindows();
    //如果还有窗口没关闭，则忽略该事件
    if (ui->mdiArea->currentSubWindow()){
        event->ignore();
    }
    else {
        writeSettings();
        event->accept();
    }
}
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,tr("About Qt"));
}


