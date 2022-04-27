#include "qgraphicsitem.h"
#include "resizablerectitem.hpp"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrintDialog>
#include <QListWidgetItem>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private:
        QGraphicsPixmapItem* getImageFromScene();
        ResizableRectItem* getRectItemFromScene();
    private slots:
        void on_actionOpen_triggered();

        void on_listWidget_itemClicked(QListWidgetItem *item);

        void on_cropButton_clicked();

        void on_changeSizeSubmit_clicked();

        void on_imageSizeSubmit_clicked();

public:
        Ui::MainWindow *ui;
        QString currentFile = "";
        QString currentDirectory = QDir::currentPath();
};

#endif
