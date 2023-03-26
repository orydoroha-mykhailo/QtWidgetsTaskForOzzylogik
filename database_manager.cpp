#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "database_manager.h"

DatabaseManager::DatabaseManager(const QString &path /* = DATABASE_FILENAME */)
    : m_Database(std::make_unique<QSqlDatabase>(
                     QSqlDatabase::addDatabase("QSQLITE"))),
                     m_CountriesTableManager(*m_Database),
                     m_OperatorsTableManager(*m_Database)
{
    m_Database->setDatabaseName(path);

    if(!m_Database->open())
    {
        qDebug() << "Can`t open the database:" << m_Database->lastError();
    }
}

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    m_Database->close();
}
