#ifndef HANGMANWIDGET_H
#define HANGMANWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QList>
#include <QChar>
#include <QVector>

namespace Ui {
class hangmanWidget;
}

class hangmanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit hangmanWidget(QWidget *parent = nullptr);
    ~hangmanWidget();

private:
    Ui::hangmanWidget *ui;

    //TitleScreen *titleScreen;
    QTimer *timer = new QTimer(this);

    QTime time;

    QVector<QString> strEasyWordList;
    QVector<QString> strMediumWordList;
    QVector<QString> strHardWordList;

    QString strPlayerName;

    QString strHiddenWord;
    QString strWordToGuess;

    QString strNumberOfGuesses;
    QString strNumberOfHints;

    QString strPlayerScore;

    QString strGuess;

    unsigned short int intNumberOfGuesses;
    unsigned short int intNumberOfHints;

    unsigned int intPlayerScore;
    unsigned short int intDifficulty;

    unsigned short int wordIndex;

    bool bCorrectLetter = false;

    bool bEasy = false;
    bool bMedium = false;
    bool bHard = false;

    QDir path;

    struct highScore
    {
        unsigned int score;
        QString name;
        QString difficulty;

        bool operator < (const highScore& str) const
        {
            return (score > str.score);
        }
    };

    QVector<highScore> highScoreVector;

private slots:
    void on_pbtGuess_clicked();

    void on_pbtHint_clicked();

    void on_pbtQuit_clicked();

    void newGameEasy();

    void newGameMedium();

    void newGameHard();

    void resetGame();

    void updateTimer();

    void addWin();

    void newWord(int difficulty);

    void addHighScore();

    void sortHighScoreList();

    void getPlayerName();

    void getWordLists();

    void getHighScoreList();

    void setDifficulty();

signals:
    void QuitClicked();

};

#endif // HANGMANWIDGET_H
