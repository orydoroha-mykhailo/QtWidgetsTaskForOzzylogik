#pragma once

#include <QString>
#include <memory>

#include "countries_table_manager.h"
#include "operators_table_manager.h"

#define DATABASE_FILENAME "system.db"

class QSqlDatabase;

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();

    CountriesTableManager& countries() const;
    OperatorsTableManager& operators() const;

protected:
    DatabaseManager(const QString &path = DATABASE_FILENAME);

private:
    std::unique_ptr<QSqlDatabase> m_Database;

    mutable CountriesTableManager m_CountriesTableManager;
    mutable OperatorsTableManager m_OperatorsTableManager;
};
