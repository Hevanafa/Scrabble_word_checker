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

    ui->ResultLabel->setText("Found " + term);
}
