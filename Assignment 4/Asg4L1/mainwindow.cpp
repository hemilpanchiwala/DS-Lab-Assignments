#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadData("/home/blackreaper/Desktop/Desktop Folder/dslabs Assignments/Assignment 4/Asg4L1/L4_P1_input.csv");
    button = ui->pushButton;
    connect(button, SIGNAL(clicked()), this, SLOT(getMeaning()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadData(QString filename) {
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file";
        return;
    }
    QTextStream in(&file);
    QString text;

    while((text = in.readLine()) != "") {
        QStringList query = text.split(",");
        char a = '\"';
        if(query[1].toUtf8().constData()[0] != a) {
            trie.insert(query[0].toUtf8().constData(), query[1].toUtf8().constData());
        }else{
            QStringList query1 = text.split("\"");
            trie.insert(query[0].toUtf8().constData(), query1[1].toUtf8().constData());
        }
    }

}

void MainWindow::getMeaning() {
    QString word = ui->textEdit->toPlainText();
    word = word.trimmed();
    ui->textEdit_2->clear();
    string ss = trie.search(word.toUtf8().constData());
    QString sss(ss.c_str());
    ui->textEdit_2->setText(sss);
}
