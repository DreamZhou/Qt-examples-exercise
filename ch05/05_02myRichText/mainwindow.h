#ifndef MAINWINDOW_H
#define MAINWINDOW_H
class MySyntaxHighlighter;
#include <QMainWindow>
class QLineEdit;
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
    void showTextFrame();
    void showTextBlock();
    void setTextFont(bool checked);
    void insertTable();
    void insertList();
    void insertImage();
    void textFind();
    void findNext();
private:
    Ui::MainWindow *ui;
    QLineEdit * lineEdit;
    MySyntaxHighlighter * highlighter;
};

#endif // MAINWINDOW_H
