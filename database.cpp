#include "database.h"

Database::Database()
{
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("/home/pavel/Programming/Projects/TestSystem/database/database.db");
  if (!database.open()) {
    std::cout << database.lastError().text().toStdString();
  } else std::cout << "Success opened database\n";
  database.exec("PRAGMA foreign_keys = ON");
}

QSqlRecord Database::selectRecord(QString)
{

}

bool Database::insertRecord(QString sql)
{
  std::cout << sql.toStdString() << std::endl;
  QSqlQuery query;
  bool isDone = query.exec(sql);
  if (!isDone) {
    std::cout << query.lastError().text().toStdString() << std::endl;
    QMessageBox::warning(new QWidget(), "Уведомление",
                         "Не удалось добавить запись\n" +
                         query.lastError().text());
  }
  return isDone;
}

QSqlDatabase* Database::getDatebase()
{
  return &database;
}

bool Database::updateRecord(QString sql)
{
  std::cout << "Update: " << sql.toStdString() << std::endl;
  QSqlQuery query;
  bool isDone = query.exec(sql);
  if (!isDone) {
    std::cout << query.lastError().text().toStdString() << std::endl;
    QMessageBox::warning(new QWidget(), "Уведомление",
                         "Не удалось обновить запись\n" +
                         query.lastError().text());
  }
  return isDone;
}
