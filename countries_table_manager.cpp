#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

#include "countries_table_manager.h"

CountriesTableManager::CountriesTableManager(QSqlDatabase &database)
  : m_Database(database)
{
    if(m_Database.tables().contains("countries"))
    {
        qDebug() << Q_FUNC_INFO << "There is table";
    }
}


QSqlQuery CountriesTableManager::readData() const
{
    QSqlQuery query(m_Database);
    if(!query.exec("SELECT * FROM countries;"))
    {
        qDebug() << Q_FUNC_INFO << "Unable to execute query";
    }

    return query;
}

QSqlQuery CountriesTableManager::readData(const QString& mcc)
{
    QSqlQuery query(m_Database);

    if(!query.exec(QString("SELECT * FROM countries"
                           " WHERE Mcc='%1';").arg(mcc)))
    {
        qDebug() << Q_FUNC_INFO << "Unable to execute query";
    }

    return query;
}
