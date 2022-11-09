#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include "wordlibrarywidget.h"



namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();

private slots:
    void on_btn_edit_words_clicked();

    void on_pbtSave_clicked();

    void on_pbtCancel_clicked();

private:
    Ui::OptionsWidget *ui;

    WordLibraryWidget *wordLibrary;

signals:
    void SavedEasy();

    void SavedMedium();

    void SavedHard();

    void EditWords();

    void CancelClicked();
};

#endif // OPTIONSWIDGET_H
