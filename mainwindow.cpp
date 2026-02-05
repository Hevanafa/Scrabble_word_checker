#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("TWL06.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream infile(&file);
        while (!infile.atEnd()) {
            QString line = infile.readLine();
            wordlist.append(line);
        }
        file.close();
    }

    ui->ResultLabel->setText("Loaded " + QString::number(wordlist.count()) + " words");
}

MainWindow::~MainWindow()
{
    wordlist.clear();
    delete ui;
}

void MainWindow::on_InputEdit_returnPressed()
{
    QString term = ui->InputEdit->text().toUpper().trimmed();

    if (!wordlist.contains(term)) {
        ui->ResultLabel->setText("The entry " + term + " was not found");
        return;
    }

    unsigned int score = 0;

    for (QChar c: std::as_const(term)) {
        if (QString("AEIOULNSTR").contains(c))
            score += 1;
        else if (QString("DG").contains(c))
            score += 2;
        else if (QString("BCMP").contains(c))
            score += 3;
        else if (QString("FHVWY").contains(c))
            score += 4;
        else if (QString("K").contains(c))
            score += 5;
        else if (QString("JX").contains(c))
            score += 8;
        else if (QString("QZ").contains(c))
            score += 10;
    }

    // ui->ResultLabel->setText("Found " + term);
    ui->ResultLabel->setText(QString("Score: %1").arg(score));
}
