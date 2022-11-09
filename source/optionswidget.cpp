#include "headers/optionswidget.h"
#include "ui_optionswidget.h"
#include "headers/titlescreen.h"


OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
    wordLibrary = new WordLibraryWidget;

}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::on_btn_edit_words_clicked()
{
     emit EditWords();
}

void OptionsWidget::on_pbtSave_clicked()
{
    if (ui->radEasy->isChecked())
    {
        emit SavedEasy();
    }
    else if(ui->radMedium->isChecked())
    {
        emit SavedMedium();
    }
    else if(ui->radHard->isChecked())
    {
        emit SavedHard();
    }
}

void OptionsWidget::on_pbtCancel_clicked()
{
    emit CancelClicked();
}
