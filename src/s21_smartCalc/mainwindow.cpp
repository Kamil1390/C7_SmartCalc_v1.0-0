#include "mainwindow.h"

#include <string.h>

#include <QDoubleValidator>
#include <sstream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->lineEdit->setPlaceholderText("0");
  ui->lineEdit_X->setPlaceholderText("0");
  ui->lineEdit_x_max->setPlaceholderText("0");
  ui->lineEdit_x_min->setPlaceholderText("0");
  ui->lineEdit_y_max->setPlaceholderText("0");
  ui->lineEdit_y_min->setPlaceholderText("0");
  ui->lineEdit_X->setValidator(new QDoubleValidator(this));
  ui->lineEdit->setValidator(new QDoubleValidator(this));
  ui->lineEdit_x_max->setValidator(new QDoubleValidator(this));
  ui->lineEdit_x_min->setValidator(new QDoubleValidator(this));
  ui->lineEdit_y_max->setValidator(new QDoubleValidator(this));
  ui->lineEdit_y_min->setValidator(new QDoubleValidator(this));
  ui->lineEdit_sumCred->setValidator(new QDoubleValidator(this));
  ui->lineEdit_termCred->setValidator(new QDoubleValidator(this));
  //    ui->lineEdit_procStavka->setValidator( new QDoubleValidator(this));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_000, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_frBrac, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->pushButton_sectBr, SIGNAL(clicked()), this,
          SLOT(ButtonPressed()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_csn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_acsn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_asn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_atn, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_pls, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_scale, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_rez, SIGNAL(clicked()), this, SLOT(ButtonPressed()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(ButtonACPressed()));
  connect(ui->pushButton_BacSpc, SIGNAL(clicked()), this,
          SLOT(ButtonBacSpcPressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text();
  QString display_value = ui->lineEdit->text();
  QString display_xValue = ui->lineEdit_X->text();
  QByteArray ds = display_value.toLocal8Bit();
  QByteArray dx = display_xValue.toLocal8Bit();
  char *strSrc = ds.data();
  char *xSrc = dx.data();
  double x = 0;
  int error = 0;
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->setCursorPosition(50);
    ui->lineEdit->setText(ui->lineEdit->text() += button_text);
    if ((button_text == "acos") || (button_text == "asin") ||
        (button_text == "atan") || (button_text == "cos") ||
        (button_text == "sin") || (button_text == "tan") ||
        (button_text == "log") || (button_text == "ln") ||
        (button_text == "sqrt") || (button_text == "^"))
      ui->lineEdit->setText(ui->lineEdit->text() += "(");
  } else if (ui->lineEdit_X->hasFocus()) {
      ui->lineEdit_X->setText(ui->lineEdit_X->text() += button_text);
      if (button_text != "=") {
        if ((button_text == "acos") || (button_text == "asin") ||
        (button_text == "atan") || (button_text == "cos") ||
        (button_text == "sin") || (button_text == "tan") ||
        (button_text == "log") || (button_text == "ln") ||
        (button_text == "sqrt") || (button_text == "^"))
        ui->lineEdit_X->setText(ui->lineEdit_X->text() += "(");
      }
  }
  if (button_text == "=") {
    QString x_res = QString::number(s21_parser(xSrc, &error, 0), 'g', 15);
    x = x_res.toDouble();
    QString str_res = QString::number(s21_parser(strSrc, &error, x), 'g', 15);
    if (error == 2)
      ui->lineEdit->setText("ERROR!");
    else {
      ui->lineEdit->setText(str_res);
      ui->lineEdit_X->setText(x_res);
    }
  }
}

void MainWindow::ButtonBacSpcPressed() {
  if (ui->lineEdit->hasFocus()) {
    QString text = ui->lineEdit->text();
    QString last = text;
    if (last.size() >= 6 && last.last(6) == "ERROR!") {
      text.chop(6);
    }
    if (last.size() >= 5 &&
        (last.last(5) == "asin(" || last.last(5) == "acos(" ||
         last.last(5) == "atan(" || last.last(5) == "sqrt(")) {
      text.chop(5);
    } else if (last.size() >= 4 &&
               (last.last(4) == "sin(" || last.last(4) == "cos(" ||
                last.last(4) == "tan(" || last.last(4) == "log(")) {
      text.chop(4);
    } else if (last.size() >= 3 && last.last(3) == "mod") {
      text.chop(3);
    } else if (last.size() >= 2 && last.last(2) == "ln") {
      text.chop(2);
    } else {
      text.chop(1);
    }
    ui->lineEdit->setText(text);
    if (ui->lineEdit->text() == "") ui->lineEdit->setPlaceholderText("0");
  } else if (ui->lineEdit_X->hasFocus()) {
    QString text_X = ui->lineEdit_X->text();
    text_X.chop(1);
    ui->lineEdit_X->setText(text_X);
  }
}

void MainWindow::ButtonACPressed() {
  if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->clear();
  } else if (ui->lineEdit_X->hasFocus()) {
    ui->lineEdit_X->clear();
  }
}

void MainWindow::on_pushButton_point_clicked() {
  if (ui->lineEdit_X->hasFocus()) {
    if (!(ui->lineEdit_X->text().contains('.')))
      ui->lineEdit_X->setText(ui->lineEdit_X->text() += ".");
  } else if (ui->lineEdit->hasFocus()) {
    ui->lineEdit->setText(ui->lineEdit->text() += ".");
  }
}

void MainWindow::on_pushButton_buildGraph_clicked() {
  QString str = ui->lineEdit->text();
  QByteArray ba = str.toLocal8Bit();
  char *buf = ba.data();

  h = 0.1;
  xBegin = ui->lineEdit_x_min->text().toDouble();
  xEnd = ui->lineEdit_x_max->text().toDouble();
  double y_min = ui->lineEdit_y_min->text().toDouble();
  double y_max = ui->lineEdit_y_max->text().toDouble();
  int error = 0;
  ui->widget->clearGraphs();
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(y_min, y_max);
  if (str != "") {
    for (X = xBegin; X <= xEnd; X += h) {
      Y = s21_parser(buf, &error, X);
      if (Y < (y_min * 2) || Y > (y_max * 2)) {
        Y = qQNaN();
      }
      x.push_back(X);
      y.push_back(Y);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_pushButton_loanCalc_clicked() {
  QString per;
  QString general;

  double summa = 0;
  double countMoth = 0;
  double procStavka = 0;

  ui->label_mothPay->setText("");
  ui->label_procents->setText("");
  ui->label_dolgProc->setText("");

  if (ui->lineEdit_sumCred->text() != "") {
    summa = ui->lineEdit_sumCred->text().toDouble();
  } else
    ui->lineEdit_sumCred->setPlaceholderText("Обязательное поле");

  if (ui->lineEdit_procStavka->text() != "") {
    char src[256] = {'\0'};
    char dst[256] = {'\0'};
    ui->label_8->clear();
    QString in_str = ui->lineEdit_procStavka->text();
    std::string str = in_str.toUtf8().constData();
    strncpy(src, str.c_str(), strlen(str.c_str()));
    s21_cpStr(src, dst);
    procStavka = atof(dst);
    if (procStavka < 0.01) {
      ui->label_8->setText("Минимальное значение 0.01");
    }
  } else
    ui->lineEdit_procStavka->setPlaceholderText("Обязательное поле");

  if (ui->lineEdit_termCred->text() != "") {
    countMoth = ui->lineEdit_termCred->text().toDouble();
  } else
    ui->lineEdit_termCred->setPlaceholderText("Обязательное поле");

  if ((ui->lineEdit_sumCred->text() != "") &&
      (ui->lineEdit_procStavka->text() != "") &&
      (ui->lineEdit_termCred->text() != "")) {
    if (ui->radioButton_anu->isChecked()) {
      QString pay;
      crOutput_1 = autetCalc(summa, procStavka, countMoth);
      pay = QString::number(crOutput_1.aut, 'f', 2);
      ui->label_mothPay->setText(pay);
      ui->label_mothPay->setText(ui->label_mothPay->text() += " ");

      per = QString::number(crOutput_1.pereplata, 'f', 2);
      ui->label_procents->setText(per);
      ui->label_procents->setText(ui->label_procents->text() += " ");

      general = QString::number(crOutput_1.generalSumma, 'f', 2);
      ui->label_dolgProc->setText(general);
      ui->label_dolgProc->setText(ui->label_dolgProc->text() += " ");
    }
    if (ui->radioButton_dif->isChecked()) {
      QString fPay;
      QString lPay;
      crOutput_2 = diferCalc(summa, procStavka, countMoth);

      fPay = QString::number(crOutput_2.firstPay, 'f', 2);
      lPay = QString::number(crOutput_2.lastPay, 'f', 2);
      ui->label_mothPay->setText(fPay);
      ui->label_mothPay->setText(ui->label_mothPay->text() +=
                                 " ... " + lPay + " ");

      per = QString::number(crOutput_2.pereplata, 'f', 2);
      ui->label_procents->setText(per);
      ui->label_procents->setText(ui->label_procents->text() += " ");

      general = QString::number(crOutput_2.generalSumma, 'f', 2);
      ui->label_dolgProc->setText(general);
      ui->label_dolgProc->setText(ui->label_dolgProc->text() += " ");
    }
  }
}
