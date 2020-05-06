#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <QGraphicsScene>
#include <cstdlib>
using namespace std;
vector<string> split(string line){
    vector<string> commands;
    string buffer = "";      //буфферная строка
    for(int i=0; i < line.size(); i++){
        if(line[i] != '\t'){      // "—\t" сплиттер
              buffer += line[i];
        }
        else{
              commands.push_back(buffer);
              buffer = "";
        }
    }
    return commands;
}

string withoutLast(string s)
{
    return s.substr(0, s.size()-1);
}

const string way = "C:\\Users\\User\\Documents\\test3\\data.txt";

class Currier
{
public:
    int id;
    string model;
    string industry;
    int mass;
    int can_curry;
    Currier(){

    }
    Currier(int i, string m, string ind, int ma, int cc){
        id= i;
        model=m;
        industry=ind;
        mass = ma;
        can_curry = cc;
    }
    Currier(string s)
    {
        vector<string>vec = split(s);
        int _id = atoi(vec[0].c_str());
        int _mass = atoi(vec[3].c_str());
        int _can_curry = atoi(vec[4].c_str());
        Currier(_id, vec[1], vec[2], _mass, _can_curry);
    }
    string toString(){
        string rez = "";
        rez+=id;
        rez+="\t"+model;
        rez+="\t";
        rez+=industry;
        rez+="\t";
        rez+=mass;
        rez+="\t";
        rez+=can_curry;
        rez+="\n";
        return rez;
    }

};


vector<Currier> curriers;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_2_released()
{
    fstream F(way, ios::out | ios::app);
    bool ok;
    QString str = QInputDialog::getText( 0,
                                         "Input",
                                         "Name:",
                                         QLineEdit::Normal,
                                         "formated input",
                                         &ok
                                        );
    F << str.toUtf8().constData()<<"\t\n";
    F.close();
}

void MainWindow::on_pushButton_3_released()
{
    vector<string> lines;
    ifstream file(way);//создаем объект потока istream  по имени file
                            // который инициализируется  именем fileName,
                           //вызывается функция file.open();
     string str;         //переменная стринг для строки
    while(getline(file,str)) //getline(istream & is, string &s,char c='\n'),читает из потока is, в строку s пока
    {                        //не встретит символ c (без этого символа до новой строки)
            lines.push_back(str);
    }
    lines.pop_back();
    file.close();
     fstream F(way, ios::out | ios::trunc);
    for (string line : lines)
    {
        F<<line<<"\n";
    }
    F.close();
}

void MainWindow::on_pushButton_4_released()
{
    ui->display->clear();



    bool ok;
    QString indName = QInputDialog::getText( 0,
                                         "Industry",
                                         "Name:",
                                         QLineEdit::Normal,
                                         "WAS",
                                         &ok
                                        );


    vector<string> lines;
    ifstream file(way);//создаем объект потока istream  по имени file
                            // который инициализируется  именем fileName,
                           //вызывается функция file.open();
     string str;         //переменная стринг для строки
    while(getline(file,str)) //getline(istream & is, string &s,char c='\n'),читает из потока is, в строку s пока
    {                        //не встретит символ c (без этого символа до новой строки)
            lines.push_back(str);
    }

    file.close();
     ifstream F(way);
    for (string line : lines)
    {
       if (indName.toStdString() == split(line)[2])
           ui->display->append(QString::fromStdString(line));
    }
    F.close();
}

void MainWindow::on_pushButton_5_released()
{

    bool ok;

    string model = QInputDialog::getText( 0,
                                         "Model",
                                         "Name:",
                                         QLineEdit::Normal,
                                         "WAS",
                                         &ok
                                        ).toStdString();
    int massToCurry = atoi(QInputDialog::getText( 0,
                                                  "Mass",
                                                  "Name:",
                                                  QLineEdit::Normal,
                                                  "999",
                                                  &ok
                                                 ).toStdString().c_str());
    ifstream file(way);//создаем объект потока istream  по имени file
                            // который инициализируется  именем fileName,
                           //вызывается функция file.open();
     string str;         //переменная стринг для строки
     int mass;
    while(getline(file,str)) //getline(istream & is, string &s,char c='\n'),читает из потока is, в строку s пока
    {                        //не встретит символ c (без этого символа до новой строки)
           if (model == split(str)[1])
               mass = atoi(split(str)[4].c_str());
    }
    ui->display->clear();
    ui->display->append(to_string(floor(1.0*massToCurry/mass)+1).c_str());

    file.close();
}

void MainWindow::on_pushButton_6_released()
{
    bool ok;
    int maxMass = atoi(QInputDialog::getText( 0,
                                                  "MaxMass",
                                                  "Name:",
                                                  QLineEdit::Normal,
                                                  "999",
                                                  &ok
                                                 ).toStdString().c_str());
     string str;
      ifstream file(way);
      ui->display->clear();
     while(getline(file,str)) //getline(istream & is, string &s,char c='\n'),читает из потока is, в строку s пока
     {                        //не встретит символ c (без этого символа до новой строки)
            if (atoi(split(str)[3].c_str()) < maxMass)
                ui->display->append(QString::fromStdString(split(str)[2]));
     }
     file.close();
}

void MainWindow::on_pushButton_7_released()
{
    QGraphicsScene * scene = new QGraphicsScene;
    ui->graph->setScene(scene);
    vector<vector<char>>points;
    string str;
    ifstream file(way);

    ui->display->clear();
    int maxX = 0;
    int maxY = 0;


    while(getline(file,str)) //getline(istream & is, string &s,char c='\n'),читает из потока is, в строку s пока
    {                        //не встретит символ c (без этого символа до новой строки)

              scene->addEllipse(atoi(split(str)[3].c_str()),atoi(split(str)[4].c_str()), 5, 5);
    }

    file.close();

}
