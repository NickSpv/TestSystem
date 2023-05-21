#pragma once

class DataInterface {};

class QueryInterface {};

class DatabaseInterface
{
public:
  DatabaseInterface();
  virtual DataInterface* getRecord(QueryInterface*);
  virtual bool setRecord(QueryInterface*, DataInterface*);
  virtual bool updateRecord(QueryInterface*, DataInterface*);
  virtual bool deleteRecord(QueryInterface);
};

