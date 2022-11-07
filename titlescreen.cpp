#include "titlescreen.h"
#include "ui_titlescreen.h"

#include <QString>

TitleScreen::TitleScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    path.setCurrent(QDir::homePath());
    path.cd(".QTProjects\\School\\CIS-224 C++\\Assignment_11\\res");

    hangmanWidget* Hangman = new hangmanWidget;
    OptionsWidget* Options = new OptionsWidget;
    WordLibraryWidget* WordLibrary = new WordLibraryWidget;
    blitz* blitzmode = new blitz;

    ui->stackedWidget->insertWidget(1, WordLibrary);
    ui->stackedWidget->insertWidget(2, Options);
    ui->stackedWidget->insertWidget(3, Hangman);
    ui->stackedWidget->insertWidget(4, blitzmode);

    getHighScoreList();
    updateHighScores();

    //Connections for argument passing between screens
    //Title screen signals
    connect(this, SIGNAL(newGameEasy()), Hangman, SLOT(newGameEasy()));
    connect(this, SIGNAL(newGameMedium()), Hangman, SLOT(newGameMedium()));
    connect(this, SIGNAL(newGameHard()), Hangman, SLOT(newGameHard()));

    //Word library signals
    connect(WordLibrary, SIGNAL(SaveClicked()), this, SLOT(wordLibrarySaved()));
    connect(WordLibrary, SIGNAL(CancelClicked()), this, SLOT(wordLibraryCanceled()));

    //Options screen signals
    connect(Options, SIGNAL(SavedEasy()), this, SLOT(optionsEasy()));
    connect(Options, SIGNAL(SavedMedium()), this, SLOT(optionsMedium()));
    connect(Options, SIGNAL(SavedHard()), this, SLOT(optionsHard()));

    connect(Options, SIGNAL(CancelClicked()), this, SLOT(optionsCancel()));
    connect(Options, SIGNAL(EditWords()), this, SLOT(optionsEdit()));

    //Hangman screen signals
    connect(Hangman, SIGNAL(QuitClicked()), this, SLOT(hangmanQuit()));

    //Blitzmode signals
    connect(blitzmode, SIGNAL(QuitClicked()), this, SLOT(hangmanQuit()));

    ui->stackedWidget->setCurrentIndex(0);
}

TitleScreen::~TitleScreen()
{
    delete ui;
}

void TitleScreen::on_pbtStartGame_clicked()
{
    if (bEasy)
    {
        ui->stackedWidget->setCurrentIndex(3);
        emit newGameEasy();
    }
    else if (bMedium)
    {
        ui->stackedWidget->setCurrentIndex(3);
        emit newGameMedium();
    }
    else if (bHard)
    {
        ui->stackedWidget->setCurrentIndex(3);
        emit newGameHard();
    }
}

void TitleScreen::on_pbtOptions_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void TitleScreen::on_pbtChangeWords_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void TitleScreen::hangmanQuit()
{
    getHighScoreList();
    updateHighScores();
    ui->stackedWidget->setCurrentIndex(0);
}

void TitleScreen::optionsEasy()
{
    ui->stackedWidget->setCurrentIndex(0);
    bEasy = true;
    bMedium = false;
    bHard = false;
}

void TitleScreen::optionsMedium()
{
    ui->stackedWidget->setCurrentIndex(0);
    bEasy = false;
    bMedium = true;
    bHard = false;
}

void TitleScreen::optionsHard()
{
    ui->stackedWidget->setCurrentIndex(0);
    bEasy = false;
    bMedium = false;
    bHard = true;
}

void TitleScreen::optionsEdit()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void TitleScreen::optionsCancel()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TitleScreen::wordLibrarySaved()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TitleScreen::wordLibraryCanceled()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TitleScreen::on_pbtAbout_clicked()
{
    About aboutUs;
    aboutUs.setModal(true);
    aboutUs.exec();
}

void TitleScreen::on_pbtContact_clicked()
{
    QDesktopServices::openUrl(QUrl("mailto:codyrockwell1@email.grcc.edu;dustinbrown4@email.grcc.edu;benjaminvanderhart@email.grcc.edu?subject=Thanks for making this game!&body="));
}

void TitleScreen::getHighScoreList()
{
    QFile highscore(path.filePath("HighScores"));
    if (!highscore.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Impending Doom!", "Unable to open High Score File: " + highscore.errorString());
        return;
    }
    QTextStream in(&highscore);
    QString strText = "";
    strText = in.readAll();
    in.flush();
    highscore.close();

    const QChar chop = ',';

    unsigned short int intChopIndex;

    int intScore;
    QString strName;
    QString strDifficulty;

    QString strData;

    highScore current;

    while (strText.length() > 1)
    {
        for (unsigned short int i = 0; i < 3; i++)
        {
            intChopIndex = strText.indexOf(chop);
            strData = strText.left(intChopIndex);

            switch (i)
            {
                case 0:
                    intScore = strData.toInt();
                    break;

                case 1:
                    strName = strData;
                    break;

                case 2:
                    strDifficulty = strData;
                    break;

                default:
                    //Should never reach this. If you do wow I suck at coding.
                    break;
            }
            strText.remove(0, intChopIndex + 1);
        }
        current.score = intScore;
        current.name = strName;
        current.difficulty = strDifficulty;

        highScoreVector.push_back(current);
    }
}

void TitleScreen::updateHighScores()
{
    QString strHighscores;
    for (unsigned short int i = 0; i < 10; i++)
    {
        strHighscores += highScoreVector.at(i).name + "\t";
        strHighscores += highScoreVector.at(i).difficulty + "\t";
        strHighscores += QString::number(highScoreVector.at(i).score) + "\n";
    }
    ui->txeHighscores->setText(strHighscores);
}

void TitleScreen::on_pbtBlitz_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}
