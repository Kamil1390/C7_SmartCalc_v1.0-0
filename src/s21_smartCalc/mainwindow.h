#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif
#include "../s21_calc.h"
#include "../s21_credCalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void ButtonPressed();

  void ButtonACPressed();

  void ButtonBacSpcPressed();

  void on_pushButton_point_clicked();

  void on_pushButton_buildGraph_clicked();

  void on_pushButton_loanCalc_clicked();

 private:
  Ui::MainWindow *ui;

  double xBegin, xEnd, h;
  int N, count;
  double X = 0.0;
  double Y = 0.0;
  dif_outPut crOutput_2 = {0, 0, 0, 0};
  aut_outPut crOutput_1 = {0, 0, 0};

  QVector<double> x, y;
};

#endif  // MAINWINDOW_H
