#pragma once

class QSqlDatabase;
class QSqlQuery;
class QString;

class CountriesTableManager
{
public:
    CountriesTableManager(QSqlDatabase &database);

    QSqlQuery readData() const;
    QSqlQuery readData(const QString &mcc);

private:
    QSqlDatabase &m_Database;
};
