#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QListWidgetItem>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void onOpen();
    void on_actionOpen_triggered();

//    void onFileExplorerFileClicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);

public:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QString currentDirectory = "";
};
