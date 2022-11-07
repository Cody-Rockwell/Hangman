#include "hangmanwidget.h"
#include "ui_hangmanwidget.h"

hangmanWidget::hangmanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hangmanWidget)
{
    ui->setupUi(this);

    path.setCurrent(QDir::homePath());
    path.cd(".QTProjects\\School\\CIS-224 C++\\Assignment_11\\res");

    getWordLists();
    getHighScoreList();

    intNumberOfGuesses = 5;
    intNumberOfHints = 3;
    intPlayerScore = 0;

    strNumberOfGuesses = QString::number(intNumberOfGuesses);
    strNumberOfHints = QString::number(intNumberOfHints);
    strPlayerScore = QString::number(intPlayerScore);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

hangmanWidget::~hangmanWidget()
{
    delete ui;
    delete timer;
}

void hangmanWidget::on_pbtGuess_clicked()
{
//    if (intNumberOfGuesses >= 1)
//    {
//        if (ui->lneGuess->isModified())
//        {
//            strGuess = ui->lneGuess->text();

//            for (unsigned short int i = 0; i < strWordToGuess.length(); i++)
//            {
//                if (strGuess == strWordToGuess[i])
//                {
//                    bCorrectLetter = true;
//                    strHiddenWord.replace(i, 1, strGuess);
//                    ui->lblHiddenWord->setText(strHiddenWord);
//                    //break; //may be used if you want only the first instance of the guessed letter in a word to be displayed instead of all of them
//                }   //TODO: Add a setting to toggle above functionality
//            }
//            if (strHiddenWord == strWordToGuess)
//            {
//                QMessageBox::information(this, "Congratulations!", "Your word to guess was \"" + strWordToGuess + "\".");

//                addWin();
//            }
//            else
//            {
//                if (bCorrectLetter)
//                {
//                    bCorrectLetter = false;
//                    QMessageBox::information(this, "Correct", "Good job buddy!");
//                }
//                else
//                {
//                    intNumberOfGuesses--;
//                    strNumberOfGuesses = QString::number(intNumberOfGuesses);
//                    ui->lblNumberOfGuesses->setText(strNumberOfGuesses);

//                    QMessageBox::information(this, "Incorrect", "Try again!");
//                }
//            }
//        }
//        else
//        {
//            QMessageBox::warning(this, "Warning", "You have not entered a guess");
//        }
//    }
//    else
//    {
//        intNumberOfGuesses = 0;

//        strNumberOfGuesses = QString::number(intNumberOfGuesses);

//        ui->lblNumberOfGuesses->setText(strNumberOfGuesses);

//        QMessageBox::information(this, "Mission Failed!", "Your word to guess was \"" + strWordToGuess + "\". You'll get him next time.");
//    }

    if (intNumberOfGuesses == 0) {

        strNumberOfGuesses = QString::number(intNumberOfGuesses);

        ui->lblNumberOfGuesses->setText(strNumberOfGuesses);

        QMessageBox::information(this, "Mission Failed!", "Your word to guess was \"" + strWordToGuess + "\". You'll get him next time.");
    }
    else {
        if (ui->lneGuess->isModified())
        {
            strGuess = ui->lneGuess->text();

            for (unsigned short int i = 0; i < strWordToGuess.length(); i++)
            {
                if (strGuess == strWordToGuess[i])
                {
                    bCorrectLetter = true;
                    strHiddenWord.replace(i, 1, strGuess);
                    //break; //may be used if you want only the first instance of the guessed letter in a word to be displayed instead of all of them
                }   //TODO: Add a setting to toggle above functionality
            }

            ui->lblHiddenWord->setText(strHiddenWord);

            if (strHiddenWord == strWordToGuess)
            {
                QMessageBox::information(this, "Congratulations!", "Your word to guess was \"" + strWordToGuess + "\".");

                addWin();
            }
            else
            {
                if (bCorrectLetter)
                {
                    bCorrectLetter = false;
                    QMessageBox::information(this, "Correct", "Good job buddy!");
                }
                else
                {
                    intNumberOfGuesses--;
                    strNumberOfGuesses = QString::number(intNumberOfGuesses);
                    ui->lblNumberOfGuesses->setText(strNumberOfGuesses);

                    QMessageBox::information(this, "Incorrect", "Try again!");
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "You have not entered a guess.");
        }
    }
}

void hangmanWidget::on_pbtHint_clicked()
{
    if (intNumberOfHints > 0)
    {
        --intNumberOfHints;
        strNumberOfHints = QString::number(intNumberOfHints);
        ui->lblNumberOfHints->setText(strNumberOfHints);

        int intHintIndex = rand() % strHiddenWord.length();
        QString strHintChar = strWordToGuess.at(intHintIndex);
        QMessageBox::information(this, "Hint", "I would go for a \"" + strHintChar + "\".");
    }
    else
    {
        QMessageBox::warning(this, "Hint", "You have no hints remaining!");
    }
}

void hangmanWidget::on_pbtQuit_clicked()
{
    addHighScore();
    timer->stop();
    emit QuitClicked();
}

void hangmanWidget::newGameEasy()
{
    bEasy = true;
    bMedium = false;
    bHard = false;
    setDifficulty();
    newWord(intDifficulty);
    time.setHMS(0, 2, 0, 0);

    getPlayerName();
    timer->start(1000);
}

void hangmanWidget::newGameMedium()
{
    bEasy = false;
    bMedium = true;
    bHard = false;
    setDifficulty();
    newWord(intDifficulty);
    time.setHMS(0, 2, 0, 0);

    getPlayerName();
    timer->start(1000);
};

void hangmanWidget::newGameHard()
{
    bEasy = false;
    bMedium = false;
    bHard = true;
    setDifficulty();
    newWord(intDifficulty);
    time.setHMS(0, 2, 0, 0);

    getPlayerName();
    timer->start(1000);
}

void hangmanWidget::resetGame()
{
    intNumberOfGuesses = 5;
    intNumberOfHints = 3;
    intPlayerScore = 0;

    strPlayerScore = QString::number(intPlayerScore);
    strNumberOfGuesses = QString::number(intNumberOfGuesses);
    strNumberOfHints = QString::number(intNumberOfHints);

    ui->lblNumberOfGuesses->setText(strNumberOfGuesses);
    ui->lblNumberOfHints->setText(strNumberOfHints);
    ui->lblPlayerScore->setText(strPlayerScore);

    newWord(intDifficulty);
    time.setHMS(0, 2, 0, 0);
    timer->start(1000);
}

void hangmanWidget::getPlayerName()
{
    bool ok;
    strPlayerName = QInputDialog::getText(this, tr("Grabbing Player Name"), tr("Enter Name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !strPlayerName.isEmpty())
    {
        ui->lblPlayerName->setText(strPlayerName);
    }
}

void hangmanWidget::getWordLists()
{
    //Easy Word File Manipulation
    QFile easy(path.filePath("Easy"));
    if (!easy.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Impending Doom!", "Unable to open file. You suck at coding. : " + easy.errorString());
        return;
    }
    QTextStream inEasy(&easy);
    while (!inEasy.atEnd())
    {
        QString strCurrentWord = "";
        strCurrentWord = inEasy.readLine();
        strEasyWordList.push_back(strCurrentWord);
    }
    inEasy.flush();
    easy.close();

    //Medium Word File Manipulation
    QFile medium(path.filePath("Medium"));
    if (!easy.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Impending Doom!", "Unable to open file. You suck at coding. : " + medium.errorString());
        return;
    }
    QTextStream inMedium(&medium);
    while (!inMedium.atEnd())
    {
        QString strCurrentWord = "";
        strCurrentWord = inMedium.readLine();
        strMediumWordList.push_back(strCurrentWord);
    }
    inMedium.flush();
    medium.close();

    //Hard Word File Manipulation
    QFile hard(path.filePath("Hard"));
    if (!hard.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Impending Doom!", "Unable to open file. You suck at coding. : " + hard.errorString());
        return;
    }
    QTextStream inHard(&hard);
    while (!inHard.atEnd())
    {
        QString strCurrentWord = "";
        strCurrentWord = inHard.readLine();
        strHardWordList.push_back(strCurrentWord);
    }
    inHard.flush();
    hard.close();
}

void hangmanWidget::getHighScoreList()
{
    QFile highscore(path.filePath("HighscoreList"));
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

void hangmanWidget::updateTimer()
{

    time = time.addSecs(-1);

    ui->lblTimer->setText(time.toString("m:ss"));

    if (ui->lblTimer->text().endsWith("0:00"))
    {
        timer->stop();

        QMessageBox msgBox;
        msgBox.setText("You have run out of time!");
        msgBox.setInformativeText("Click cancel to Quit, and Reset to start a new game.");
        msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Reset);

        unsigned short int choice = msgBox.exec();

        switch (choice)
        {
        case QMessageBox::Reset:
            resetGame();
            break;

        case QMessageBox::Cancel:
            emit QuitClicked();
            break;
        }
    }
}

void hangmanWidget::addWin()
{
    intPlayerScore += 100;

    strPlayerScore = QString::number(intPlayerScore);

    ui->lblPlayerScore->setText(strPlayerScore);

    ui->lneGuess->setText("");

    ui->lneGuess->setFocus();

    newWord(intDifficulty);

    time.setHMS(0, 2, 0, 0);
    timer->start();
}

void hangmanWidget::newWord(int difficulty)
{
    strWordToGuess = "";
    strHiddenWord = "";

    ui->lblHiddenWord->setText(strWordToGuess);
    ui->lblHiddenWord->setText(strHiddenWord);

    switch (difficulty)
    {
    case 1:

        wordIndex = 0;
        wordIndex = rand() % strEasyWordList.size();

        strWordToGuess = strEasyWordList[wordIndex];

        for (int i = 0; i < strWordToGuess.length(); i++)
        {
            strHiddenWord.replace(i, 1, '_');
        }

        ui->lblHiddenWord->setText(strHiddenWord);
        break;

    case 2:

        wordIndex = 0;
        wordIndex = rand() % strMediumWordList.size();

        strWordToGuess = strMediumWordList[wordIndex];

        for (int i = 0; i < strWordToGuess.length(); i++)
        {
            strHiddenWord.replace(i, 1, '_');
        }

        ui->lblHiddenWord->setText(strHiddenWord);
        break;

    case 3:

        wordIndex = 0;
        wordIndex = rand() % strHardWordList.size();

        strWordToGuess = strHardWordList[wordIndex];

        for (int i = 0; i < strWordToGuess.length(); i++)
        {
            strHiddenWord.replace(i, 1, '_');
        }

        ui->lblHiddenWord->setText(strHiddenWord);
        break;
    }
}

void hangmanWidget::addHighScore()
{
    highScore current;

    current.score = intPlayerScore;
    current.name = strPlayerName;
    switch (intDifficulty)
    {
        case 1:
            current.difficulty = "Easy";
            break;

        case 2:
            current.difficulty = "Medium";
            break;

        case 3:
            current.difficulty = "Hard";
            break;
    }

    highScoreVector.push_back(current);

    sortHighScoreList();

    QFile file(path.filePath("HighScores"));
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        //QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    QTextStream out(&file);
    QString strHighScore;
    QString strOut = "";

    for (unsigned int i = 0; i < 10; ++i) {
        strHighScore = "";
        strHighScore += QString::number(highScoreVector.at(i).score) + ",";
        strHighScore += highScoreVector.at(i).name + ",";
        strHighScore += highScoreVector.at(i).difficulty + ",";

        strOut += strHighScore;
    }
    out << strOut;
    out.flush();
    file.close();
}

void hangmanWidget::sortHighScoreList()
{
    std::sort(highScoreVector.begin(), highScoreVector.end());
}

void hangmanWidget::setDifficulty()
{
    if (bEasy)
    {
        intDifficulty = 1;
    }
    else if (bMedium)
    {
        intDifficulty = 2;
    }
    else if (bHard)
    {
        intDifficulty = 3;
    }
}
