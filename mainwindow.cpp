#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  model = new QSqlRelationalTableModel(this, *database.getDatebase());
  linesLineEdit = {};
  columns = {};
  isConnectTable = false;
  MySqlQuery query;
  on_actionusers_triggered();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete model;
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void MainWindow::generateInsertButtons()
{
  clearLayout(ui->verticalLayout_insert, true);
  linesLineEdit.clear();
  columns.clear();
  for(int i = 0; i < model->columnCount(); i++)
  {
    columns.append(model->headerData(i, Qt::Horizontal).toString());
    QLabel *label = new QLabel(columns[i]);
    QLineEdit *lineEdit = new QLineEdit();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    ui->verticalLayout_insert->addLayout(layout);
    linesLineEdit.append(lineEdit);
  }
}

void MainWindow::generateInsertButtonsConnection()
{
  clearLayout(ui->verticalLayout_insert, true);
  linesComboBox.clear();
  columns.clear();
  for(int i = 0; i < model->columnCount(); i++)
  {
    columns.append(model->headerData(i, Qt::Horizontal).toString());
    QLabel *label = new QLabel(columns[i]);
    QComboBox *comboBox = new QComboBox();
    QString columnN = columns[i].left(columns[i].indexOf('_')),
        tableN = columns[i].right(columns[i].size() - columns[i].indexOf('_') - 1);
    QSqlTableModel tmpModel(this, *database.getDatebase());
    tmpModel.setTable(tableN);
    tmpModel.select();

    std::cout << columnN.toStdString() << " " << tableN.toStdString() << std::endl;

    comboBox->addItem("");
    for (int j = 0; j < tmpModel.rowCount(); j++) {
      std::cout << tmpModel.data(tmpModel.index(j, 0), 0).toString().toStdString() << std::endl;
      comboBox->addItem(tmpModel.data(tmpModel.index(j, 0), 0).toString());
      // (j, 0), так как первичный ключ всегда на первом месте (в случае с моими таблицами)
    }
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(comboBox);
    ui->verticalLayout_insert->addLayout(layout);
    linesComboBox.append(comboBox);
  }
}

bool MainWindow::insertIntoTable(QString table, QVector<QString> columns, QVector<QString> values)
{
  return database.insertRecord(MySqlQuery::INSERT(table, columns, values));
}

bool MainWindow::selectFromTable(QString table, QVector<QString> columns, QVector<QString> values)
{
  model->setTable(table);
  model->select();
  ui->tableView->setModel(model);
  ui->tableView->horizontalHeader()->setMinimumSectionSize(50);
  ui->tableView->horizontalHeader()->setMaximumSectionSize(200);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->horizontalHeader()->setMaximumSectionSize(2000);
  return true;
}

//TODO
bool MainWindow::selectFromTableConnection(QString table, QVector<QString> columns, QVector<QString> values)
{
  model->setTable(table);
  model->select();
  ui->tableView->setModel(model);
  ui->tableView->horizontalHeader()->setMinimumSectionSize(50);
  ui->tableView->horizontalHeader()->setMaximumSectionSize(200);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->horizontalHeader()->setMaximumSectionSize(2000);
  return true;
}

bool MainWindow::updateInTable(QString table, QVector<QString> values, QVector<QString> conditions)
{
  return database.updateRecord(MySqlQuery::UPDATE(table, columns, values, conditions));
}

void MainWindow::on_actionusers_triggered()
{
  selectFromTable("users", {}, {});
  table = "users";
  isConnectTable = false;
  generateInsertButtons();
}

void MainWindow::on_actiontests_triggered()
{
  selectFromTable("tests", {}, {});
  table = "tests";
  isConnectTable = false;
  generateInsertButtons();
}

void MainWindow::on_actiontasks_triggered()
{
  selectFromTable("tasks", {}, {});
  table = "tasks";
  isConnectTable = false;
  generateInsertButtons();
}

void MainWindow::on_actionsolves_triggered()
{
  selectFromTable("solves", {}, {});
  table = "solves";
  isConnectTable = false;
  generateInsertButtons();
}

void MainWindow::on_actioncontrol_examples_triggered()
{
  selectFromTable("control_examples", {}, {});
  table = "control_examples";
  isConnectTable = false;
  generateInsertButtons();
}

void MainWindow::on_actionsolves_tasks_triggered()
{
  selectFromTable("solves_tasks", {}, {});
  table = "solves_tasks";
  isConnectTable = true;
  generateInsertButtonsConnection();
}

void MainWindow::on_actiontest_tasks_triggered()
{
  selectFromTable("tasks_tests", {}, {});
  table = "tasks_tests";
  isConnectTable = true;
  generateInsertButtonsConnection();
}

void MainWindow::on_actioncontrol_examples_tasks_triggered()
{
  selectFromTable("control_examples_tasks", {}, {});
  table = "control_examples_tasks";
  isConnectTable = true;
  generateInsertButtonsConnection();
}

void MainWindow::on_actiontests_users_triggered()
{
  selectFromTable("tests_users", {}, {});
  table = "tests_users";
  isConnectTable = true;
  generateInsertButtonsConnection();
}

void MainWindow::on_actionusers_solves_triggered()
{
  selectFromTable("users_solves", {}, {});
  table = "users_solves";
  isConnectTable = true;
  generateInsertButtonsConnection();
}

void MainWindow::on_pushButton_add_clicked()
{
  QVector<QString> values;
  QVector<QString> cols;
  if (!isConnectTable) {
    for (int i = 0; i < linesLineEdit.size(); i++) {
      if (linesLineEdit[i]->text().isEmpty()) continue;
      bool isNumber = true;
      for (QChar j : linesLineEdit[i]->text()) {
        if (!j.isNumber()) isNumber = false;
      }
      if (!isNumber) values.append("\'" + linesLineEdit[i]->text() + "\'");
      else values.append(linesLineEdit[i]->text());
      cols.append(columns[i]);
    }
  } else {
    for (int i = 0; i < linesComboBox.size(); i++) {
      if (linesComboBox[i]->currentText().isEmpty()) continue;
      bool isNumber = true;
      for (QChar j : linesComboBox[i]->currentText()) {
        if (!j.isNumber()) isNumber = false;
      }
      if (!isNumber) values.append("\'" + linesComboBox[i]->currentText() + "\'");
      else values.append(linesComboBox[i]->currentText());
      cols.append(columns[i]);
    }
  }
  if (!insertIntoTable(table, cols, values)) {
    std::cout << "Insert ERROR!!!";
  }
  model->select();
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
  QMenu *menu=new QMenu(this);
  QAction* edit = new QAction("Изменить", this);
  QAction* remove = new QAction("Удалить", this);
  connect(edit, SIGNAL(triggered(bool)), this, SLOT(slotEditRecord()));
  connect(remove, SIGNAL(triggered(bool)), this, SLOT(slotRemoveRecord()));
  menu->addAction(edit);
  menu->addAction(remove);
  menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::slotRemoveRecord()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if(row >= 0){
        if (QMessageBox::warning(this,
                                 "Удаление записи",
                                 "Вы уверены, что хотите удалить эту запись?",
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            QSqlDatabase::database().rollback();
            return;
        } else {
            if(!model->removeRow(row)){
                QMessageBox::warning(this,"Уведомление",
                                     "Не удалось удалить запись\n");
            }
            model->select();
            ui->tableView->setCurrentIndex(model->index(-1, -1));
        }
    }
}

void MainWindow::slotEditRecord()
{
  QDialog dialog(this);
  QFormLayout form(&dialog);
  int row = ui->tableView->selectionModel()->currentIndex().row();
  form.addRow(new QLabel("Изменение записи"));

  QVector<QString> conditions;
  QVector<QString> values;
  QList<QLineEdit *> fields;
  for(int i = 0; i < columns.size(); ++i) {
      QLineEdit *lineEdit = new QLineEdit(model->data(model->index(row, i), 0).toString(), &dialog);
      QString text = model->data(model->index(row, i), 0).toString();
      bool isNumber = true;
      for (QChar j : text) {
        if (!j.isNumber()) isNumber = false;
      }
      if (!isNumber) conditions.append("\'" + text + "\'");
      else conditions.append(text);
      QString label = columns[i].arg(i + 1);
      form.addRow(label, lineEdit);
      fields << lineEdit;
  }

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);
  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  if (dialog.exec() == QDialog::Accepted) {
    foreach(QLineEdit * lineEdit, fields) {
      std::cout << lineEdit->text().toStdString();
      bool isNumber = true;
      for (QChar j : lineEdit->text()) {
        if (!j.isNumber()) isNumber = false;
      }
      if (!isNumber) values.append("\'" + lineEdit->text() + "\'");
      else values.append(lineEdit->text());
    }
  }
  updateInTable(table, values, {conditions[0]});
  model->select();
}

void MainWindow::on_pushButton_select_clicked()
{
  QVector<QString> values;
  QVector<QString> cols;
  if (!isConnectTable) {
    for (int i = 0; i < linesLineEdit.size(); i++) {
      if (linesLineEdit[i]->text().isEmpty()) continue;
      values.append("\'%" + linesLineEdit[i]->text() + "%\'");
      cols.append(columns[i]);
    }
  } else {
    for (int i = 0; i < linesComboBox.size(); i++) {
      if (linesComboBox[i]->currentText().isEmpty()) continue;
      values.append("\'%" + linesComboBox[i]->currentText() + "%\'");
      cols.append(columns[i]);
    }
  }
  std::cout << MySqlQuery::SELECT(table, cols, {}, values).toStdString() << std::endl;
  for (int i = 0; i < values.size(); i++) {
    //model->setFilter(cols[i] + " LIKE " + values[i]);
  }
  model->setFilter(MySqlQuery::SELECT(table, cols, {}, values));
  model->select();
}

