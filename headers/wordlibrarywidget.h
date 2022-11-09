#ifndef WORDLIBRARYWIDGET_H
#define WORDLIBRARYWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class WordLibraryWidget;
}

class WordLibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordLibraryWidget(QWidget *parent = nullptr);
    ~WordLibraryWidget();

private slots:
    void on_pbtSave_clicked();

    void on_pbtCancel_clicked();

    void on_pbtOpen_clicked();

private:
    Ui::WordLibraryWidget *ui;

signals:
    void SaveClicked();

    void CancelClicked();
};

#endif // WORDLIBRARYWIDGET_H
