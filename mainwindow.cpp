#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList header;
    header<<"学号"<<"姓名"<<"年龄";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnCount(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString id=ui->lineEdit->text();
    QString name=ui->lineEdit_2->text();
    QString age=ui->lineEdit_3->text();
    int row=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(id));
     ui->tableWidget->setItem(row,1,new QTableWidgetItem(name));
     ui->tableWidget->setItem(row,2,new QTableWidgetItem(age));
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}


void MainWindow::on_pushButton_6_clicked()
{
    int row=ui->tableWidget->currentRow();
    if(row==-1){
        return;
    }
    ui->tableWidget->removeRow(row);
}


void MainWindow::on_pushButton_3_clicked()
{
    QString searchId=ui->lineEdit->text();
    ui->tableWidget->clearSelection();
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        QString id=ui->tableWidget->item(i,0)->text();
        if(id==searchId){
            ui->tableWidget->selectRow(i);
            return;
        }

    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QFile file("stu.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,"提示","文件打开失败");
        return;
    }
    QTextStream out(&file);
    int rowCount=ui->tableWidget->rowCount();
    for(int i=0;i<rowCount;i++){
        QString id=ui->tableWidget->item(i,0)->text();
        QString name=ui->tableWidget->item(i,1)->text();
        QString age=ui->tableWidget->item(i,2)->text();
        out<<id<<" "<<name<<" "<<age<<"\n";
    }
    file.close();
    QMessageBox::information(this,"提示","保存成功");
    }





    void MainWindow::on_pushButton_5_clicked()
    {
        QFile file("stu.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QMessageBox::warning(this,"提示","文件打开失败");
            return ;
        }
        QTextStream in(&file);
        ui->tableWidget->setRowCount(0);
        while(!in.atEnd()){
            QString id,name,age;
            in>>id>>name>>age;
            int row =ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(id));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(name));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(age));
        }
        file.close();
        QMessageBox::information(this,"提示","读取完毕");
    }

