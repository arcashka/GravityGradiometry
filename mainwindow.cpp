#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inputButton_clicked()
{
    ui->buttonReDo->setEnabled(true);
    QString file_name = QFileDialog::getOpenFileName(this, trUtf8("Open File"), fileName, "Text Files (*.txt);;All Files (*.*)");
    if(file_name.length() == 0)
        return;
    fileName = file_name;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);
    ui->textInput->setPlainText(stream.readAll());
    file.close();

    std::stringstream str;
    str << ui->textInput->toPlainText().toStdString();
    try
    {
        ui->mainWindow->ar.generateFromStream(str);
    }
    catch(...)
    {
        qDebug("Exception on OK");
        QMessageBox m(QMessageBox::Critical, trUtf8("Ошибка"), trUtf8("Ошибка в описании области"));
        m.exec();
        return;
    }
    ui->mainWindow->defaultScene();
    ui->mainWindow->updateGL();\
    ui->execDirectButton->setEnabled(true);
}


void MainWindow::on_buttonReDo_clicked()
{
    std::stringstream str;
    str << ui->textInput->toPlainText().toStdString();
    try
    {
        ui->mainWindow->ar.generateFromStream(str);
    }
    catch(...)
    {
        qDebug("Exception on OK");
        QMessageBox m(QMessageBox::Critical, trUtf8("Ошибка"), trUtf8("Ошибка в описании области"));
        m.exec();
        return;
    }
    ui->mainWindow->updateGL();
}


void MainWindow::on_execDirectButton_clicked()
{
    ui->mainWindow->ar.dTask.numX = ui->numXBox->value();
    ui->mainWindow->ar.dTask.numY = ui->numYBox->value();
    ui->mainWindow->ar.dTask.execDirectTask(ui->mainWindow->ar.cubes, ui->mainWindow->ar.xMin, ui->mainWindow->ar.xMax,
                                            ui->mainWindow->ar.yMin, ui->mainWindow->ar.yMax, ui->mainWindow->ar.zMax);
}



void MainWindow::on_checkOnlyLines_clicked(bool checked)
{
    if(checked)
        ui->mainWindow->ar.drawLines = false;
    else
        ui->mainWindow->ar.drawLines = true;
    ui->mainWindow->updateGL();
}


void MainWindow::on_checkGauss_clicked(bool checked)
{
    if(checked)
        ui->mainWindow->ar.gaussPointsDraw = true;
    else
        ui->mainWindow->ar.gaussPointsDraw = false;
    ui->mainWindow->updateGL();
}


void MainWindow::on_execInverseButton_clicked()
{
    ui->mainWindow2->ar = ui->mainWindow->ar;
    std::vector< cube >& cubes = ui->mainWindow2->ar.cubes;
    std::vector< receiver >& receivers = ui->mainWindow2->ar.dTask.receivers;

    if(ui->checkIsReg->isChecked())
    {
        int itt;
        double alpha = ui->alphaBox->value();
        double gamma = ui->gammaBox->value();
        double percentage = ui->percBox->value();
        double gammaD = ui->gammaDBox->value();
        std::vector< double >& newP = ui->mainWindow2->ar.iTask.execWithRegular(
                    cubes, receivers,
                    alpha, gamma, percentage, gammaD, itt);
        ui->mainWindow2->ar.setNewP(newP);
        ui->labIter->setText(QString::number(itt));
    }
    else
    {
        std::vector< double >& newP = ui->mainWindow2->ar.iTask.execInverseTask(cubes, receivers);
        ui->mainWindow2->ar.setNewP(newP);
    }

    ui->mainWindow2->updateGL();
}


void MainWindow::on_checkBoxX_clicked(bool checked)
{
    if(checked)
    {
        ui->mainWindow2->plane = 0;
        ui->verticalSliderX->setValue(0);
        ui->verticalSliderY->setValue(0);
        ui->verticalSliderZ->setValue(0);
        ui->checkBoxY->setChecked(false);
        ui->checkBoxZ->setChecked(false);

        ui->verticalSliderX->setEnabled(true);
        ui->verticalSliderY->setEnabled(false);
        ui->verticalSliderZ->setEnabled(false);
        ui->mainWindow2->side = 1;
        ui->verticalSliderX->setRange(0, ui->mainWindow2->ar.xNum - 1);
    }
    else
    {
        ui->mainWindow2->side = -1;
        ui->verticalSliderX->setEnabled(false);
        //ui->checkBoxX->setChecked(true);
    }
    ui->mainWindow2->recalc();
    ui->mainWindow2->updateGL();
}


void MainWindow::on_checkBoxY_clicked(bool checked)
{
    if(checked)
    {
        ui->verticalSliderX->setValue(0);
        ui->verticalSliderY->setValue(0);
        ui->verticalSliderZ->setValue(0);
        ui->mainWindow2->plane = 0;
        ui->checkBoxX->setChecked(false);
        ui->checkBoxZ->setChecked(false);

        ui->verticalSliderY->setEnabled(true);
        ui->verticalSliderX->setEnabled(false);
        ui->verticalSliderZ->setEnabled(false);
        ui->mainWindow2->side = 2;
        ui->verticalSliderY->setRange(0, ui->mainWindow2->ar.yNum - 1);
    }
    else
    {
        ui->mainWindow2->side = -1;
        ui->verticalSliderY->setEnabled(false);
        //ui->checkBoxY->setChecked(true);
    }
    ui->mainWindow2->recalc();
    ui->mainWindow2->updateGL();
}


void MainWindow::on_checkBoxZ_clicked(bool checked)
{
    if(checked)
    {
        ui->verticalSliderX->setValue(0);
        ui->verticalSliderY->setValue(0);
        ui->verticalSliderZ->setValue(0);
        ui->mainWindow2->plane = 0;
        ui->checkBoxX->setChecked(false);
        ui->checkBoxY->setChecked(false);

        ui->verticalSliderZ->setEnabled(true);
        ui->verticalSliderX->setEnabled(false);
        ui->verticalSliderY->setEnabled(false);
        ui->mainWindow2->side = 3;
        ui->verticalSliderZ->setRange(0, ui->mainWindow2->ar.zNum - 1);
    }
    else
    {
        ui->verticalSliderZ->setEnabled(false);
        ui->mainWindow2->side = -1;
        //ui->checkBoxZ->setChecked(true);
    }
    ui->mainWindow2->recalc();
    ui->mainWindow2->updateGL();
}


void MainWindow::on_verticalSliderX_valueChanged(int value)
{
    ui->mainWindow2->plane = value;
    ui->mainWindow2->updateGL();
}


void MainWindow::on_verticalSliderY_valueChanged(int value)
{
    ui->mainWindow2->plane = value;
    ui->mainWindow2->updateGL();
}


void MainWindow::on_verticalSliderZ_valueChanged(int value)
{
    ui->mainWindow2->plane = value;
    ui->mainWindow2->updateGL();
}

void MainWindow::on_checkIsReg_clicked(bool checked)
{
    ui->percBox->setEnabled(checked);
    ui->alphaBox->setEnabled(checked);
    ui->gammaBox->setEnabled(checked);
    ui->gammaDBox->setEnabled(checked);
}
