#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QString>

#include "about.h"
#include "hangmanwidget.h"
#include "optionswidget.h"
#include "wordlibrarywidget.h"
#include "blitz.h"

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private slots:

    void on_pbtStartGame_clicked();

    void on_pbtOptions_clicked();

    void on_pbtChangeWords_clicked();

    void hangmanQuit();

    void optionsEasy();

    void optionsMedium();

    void optionsHard();

    void optionsEdit();

    void optionsCancel();

    void wordLibrarySaved();

    void wordLibraryCanceled();

    void on_pbtAbout_clicked();

    void on_pbtContact_clicked();

    void getHighScoreList();

    void updateHighScores();

    void on_pbtBlitz_clicked();

private:
    Ui::TitleScreen *ui;

    bool bEasy = true;
    bool bMedium = false;
    bool bHard = false;

    QDir path;

    struct highScore
    {
        unsigned int score;
        QString name;
        QString difficulty;
    };

    static bool compareTwoScores(highScore a, highScore b)
    {
        // checks to see which score is higher between
        // two scores in the structure
        return a.score > b.score;
    }

    QVector<highScore> highScoreVector;

signals:
    void newGameEasy();

    void newGameMedium();

    void newGameHard();
};

#endif // TITLESCREEN_H
