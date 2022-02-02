#include "imc.h"
#include "ui_imc.h"
#include <cstdlib>
#include <QMessageBox>
#include <QFile>
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>


IMC::IMC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IMC)
{
    ui->setupUi(this);
}

IMC::~IMC()
{
    delete ui;
}

void IMC::limpiar()
{
    ui->inAltura->setValue(0);
    ui->inPeso->setValue(0);

}

void IMC::calcular()
{
    float altura = ui->inAltura->value();
    float peso = ui->inPeso->value();
    if (peso==0 || altura==0){
        QMessageBox::warning(this,"Advertencia", "La altura o el peso esatá vacio" );
        return;
    }
    float st= (peso/(altura*altura))*10000;
    ui->outIMC->setText(QString:: number(st)+ " kg/m²");
    ui->outAltura->setText(QString::number(altura)+" cm");
    ui->outActual->setText(QString::number(peso)+ "kg");
    limpiar ();
}

void IMC::guardar()
{
    float altura = ui->inAltura->value();
    float peso = ui->inPeso->value();
    float st= (peso/(altura*altura))*10000;

    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        // Crear un 'stream' de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outResultados->toPlainText()
                    +"Altura: *"+ QString ::number(altura)+"*\n"
                    +"Peso: "+QString::number(peso)+"\n"
                    +"IMC: "+ QString::number(st);
        ui->statusbar->showMessage("Datos almacenados en " + nombreArchivo, 5000);
    }else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
    }
    // Cerrar el archivo
    archivo.close();

}

void IMC::abrir()
{
    // Abrir cuadro de diálogo para seleccionar ubicación y nombre del archivo.
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         "Abrir archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");

    // Crear un objeto QFile
    QFile archivo(nombreArchivo);
    // Abrirlo para lectura
    if(archivo.open(QFile::ReadOnly)){
        // Crear un 'stream' de texto
        QTextStream entrada(&archivo);
        // Leer todo el contenido del archivo
        QString datos = entrada.readAll();
        auto totales=datos.split("*");
        // Cargar el contenido al área de texto
        ui->outResultados->clear();
        ui->outResultados->setPlainText(totales[0]);
        ui->outIMC->setText(totales[2]);
        totales[2].toFloat();
        ui->outActual->setText(totales[4]);
        totales[4].toFloat();
        ui->outAltura->setText(totales[6]);
        totales[6].toFloat();
        // Mostrar 5 segundo que todo fue bien
        ui->statusbar->showMessage("Datos leidos desde " + nombreArchivo, 5000);
    }else {
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(this,
                             "Abrir datos",
                             "No se pudo abrir el archivo");
    }
    // Cerrar el archivo
    archivo.close();
}


void IMC::on_btnCalcular_clicked()
{
    calcular();
}


void IMC::on_action_Nuevo_triggered()
{
    limpiar();
    ui->outResultados->clear();
    ui->outIMC->clear();
    ui->outActual->clear();
    ui->outAltura->clear();

}


void IMC::on_action_Abrir_triggered()
{
    abrir();
}


void IMC::on_action_Guardar_triggered()
{
    guardar();
}


void IMC::on_action_Calcular_triggered()
{
    calcular();
}



void IMC::on_action_Salir_triggered()
{
    close();
}

