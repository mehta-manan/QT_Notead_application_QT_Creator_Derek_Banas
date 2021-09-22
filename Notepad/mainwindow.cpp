#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setCentralWidget(ui->textEdit);
  setWindowTitle("QtNotes - Untitled");
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    // clear the file name string
    currentFile.clear();
    // clear the text edit
    ui->textEdit->setText(QString());
    setWindowTitle("QtNotes - Untitled");
}


void MainWindow::on_actionOpen_triggered()
{
   // get open file name from dialog box and store it
  QString fileName = QFileDialog::getOpenFileName(this,"Open");

  // set file pointer
  QFile file(fileName);

  // set currentfile to filename
  currentFile = fileName;

  //check for unsuccessful file open
  if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
      // pop up warning
      QMessageBox::warning(this,"Warning", "Cannot open file: " + file.errorString());
      return;
    }

  //set window title
  setWindowTitle("QtNotes - " + fileName);

  //stream to read data from file
  QTextStream in(&file);

  // copy data in string
  QString text = in.readAll();

  // display data
  ui->textEdit->setText(text);

  //close file
  file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    // get save file name and store it
  QString fileName = QFileDialog::getSaveFileName(this, "Save as");

  // set file pointer
  QFile file(fileName);

  // set currentfile to filename
  currentFile = fileName;

  //check for unsuccessful file open
  if (!file.open(QFile::WriteOnly | QFile::Text))
    {
      // pop up warning
      QMessageBox::warning(this,"Warning", "Cannot save file: " + file.errorString());
      return;
    }

  //set window title
  setWindowTitle("QtNotes - " + fileName);

  //stream to write data to file
  QTextStream out(&file);

  // copy data from textEdit into string
  QString text = ui->textEdit->toPlainText();

  // save data in file
  out << text;

  //close file
  file.close();
}


void MainWindow::on_actionPrint_triggered()
{
  // object to get access to printer
  QPrinter printer;

  // set printer name (optional)
  printer.setPrinterName("Printer name");

  QPrintDialog pDialog(&printer, this);

  // check for unsuccessful printer access
  if (pDialog.exec() == QDialog::Rejected)
    {
      QMessageBox::warning(this, "Warning", "Cannot access printer.");
      return;
    }

  // send data from text edit to printer
  ui->textEdit->print(&printer);

}


void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

