#pragma once

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <database.h>
#include <mysqlquery.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  bool deleteFromTable();
  bool insertIntoTable(QString table, QVector<QString> columns, QVector<QString> values);
  bool selectFromTable(QString table, QVector<QString> columns, QVector<QString> values);
  bool selectFromTableConnection(QString table, QVector<QString> columns, QVector<QString> values);
  bool updateInTable(QString table, QVector<QString> values, QVector<QString> conditions);
  // QPdf generateReport();

  void generateInsertButtons();
  void generateInsertButtonsConnection();


private slots:
  void slotRemoveRecord();

  void slotEditRecord();

  void on_actionusers_triggered();

  void on_actiontests_triggered();

  void on_actiontasks_triggered();

  void on_actionsolves_triggered();

  void on_actioncontrol_examples_triggered();

  void on_actionsolves_tasks_triggered();

  void on_actiontest_tasks_triggered();

  void on_actioncontrol_examples_tasks_triggered();

  void on_actiontests_users_triggered();

  void on_actionusers_solves_triggered();

  void on_pushButton_add_clicked();

  void on_tableView_customContextMenuRequested(const QPoint &pos);

  void on_pushButton_select_clicked();

private:
  Ui::MainWindow *ui;
  Database database;
  QSqlRelationalTableModel *model;
  QVector<QLineEdit*> linesLineEdit;
  QVector<QComboBox*> linesComboBox;
  QVector<QString> columns;
  QString table;
  bool isConnectTable;
};
