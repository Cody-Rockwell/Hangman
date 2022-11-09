#include "headers/wordlibrarywidget.h"
#include "ui_wordlibrarywidget.h"
#include "headers/optionswidget.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

WordLibraryWidget::WordLibraryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordLibraryWidget)
{
    ui->setupUi(this);
}

WordLibraryWidget::~WordLibraryWidget()
{
    delete ui;
}

void WordLibraryWidget::on_pbtSave_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->txeWords->toPlainText();
    out << text;
    out.flush();
    file.close();
    emit SaveClicked();
}

void WordLibraryWidget::on_pbtCancel_clicked()
{
    emit CancelClicked();
}

void WordLibraryWidget::on_pbtOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file to open");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->txeWords->setText(text);
    in.flush();
    file.close();
}
