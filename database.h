#pragma once

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <mysqlquery.h>

#include <iostream>

class Database
{
public:
  Database();
  QSqlRecord selectRecord(QString);
  bool insertRecord(QString);
  bool updateRecord(QString);
  bool deleteRecord(QString);

  QSqlDatabase* getDatebase();

private:
  QSqlDatabase database;
};

