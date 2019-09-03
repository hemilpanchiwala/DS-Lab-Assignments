#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <bits/stdc++.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <string.h>

namespace Ui {
class MainWindow;
}

using namespace std;

struct Node{
public:
    struct Node* child[26];
    char meaning[50];
    bool isEnd;
};

class Trie{
public:
    Node* root;

    Trie() {
        root =  new Node();

        root->isEnd = false;

        for (int i = 0; i < 26; i++)
            root->child[i] = nullptr;
    }

    string search(string word) {

        Node *node = root;

        if(node == nullptr) {
            return "Dictionary is empty!!!";
        }

        for(unsigned long i=0;i<word.size();i++) {

            int letterIndex = word[i] - 65;

            if(!node->child[letterIndex]) {
                return "Word not found!!!";
            }

            node = node->child[letterIndex];

        }

        return node->meaning;

    }

    void insert(string word, string meaning){

        Node *node = root;

        for(unsigned long i=0;i<word.size();i++) {

            int letterIndex = word[i] - 65;

            if(!node->child[letterIndex]){
                Node *temp =  new Node();

                temp->isEnd = false;
                strcpy(node->meaning, "Word not found!!!");
//                temp->meaning = "hello";

                for (int i = 0; i < 26; i++)
                    temp->child[i] = nullptr;

                node->child[letterIndex] = temp;
            }

            node = node->child[letterIndex];

        }

        strcpy(node->meaning, meaning.c_str());
        node->isEnd = true;

    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadData(QString filename);
    Trie trie;

public slots:
    void getMeaning();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
};




#endif // MAINWINDOW_H
