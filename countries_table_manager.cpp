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
