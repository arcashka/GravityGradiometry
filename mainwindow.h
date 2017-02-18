#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);\
    QString fileName;

    ~MainWindow();

private slots:
    void on_inputButton_clicked();

    void on_buttonReDo_clicked();

    void on_execDirectButton_clicked();

    void on_checkOnlyLines_clicked(bool checked);

    void on_checkGauss_clicked(bool checked);

    void on_execInverseButton_clicked();

    void on_checkBoxX_clicked(bool checked);

    void on_checkBoxY_clicked(bool checked);

    void on_checkBoxZ_clicked(bool checked);

    void on_verticalSliderX_valueChanged(int value);

    void on_verticalSliderY_valueChanged(int value);

    void on_verticalSliderZ_valueChanged(int value);

    void on_checkIsReg_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
