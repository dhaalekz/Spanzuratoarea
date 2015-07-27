#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTSql>
#include <QtDebug>
#include <QFileinfo>

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
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_buttop3_clicked();

    void on_butback_clicked();

    void on_butstatistici_clicked();

    void on_pushButton_4_clicked();

    void on_catanim_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_cataut_clicked();

    void on_catfruct_clicked();

    void on_catjud_clicked();

    void on_catpict_clicked();

    void on_catplant_clicked();

    void on_cattari_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_cataleat_clicked();

    void on_butadmin_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase utilizatori;
};

#endif // MAINWINDOW_H
