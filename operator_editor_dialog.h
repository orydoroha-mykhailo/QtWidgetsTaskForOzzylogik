#pragma once

#include <QDialog>
#include <QModelIndex>

class QLabel;
class QLineEdit;
class DataModel;
class DatabaseManager;

class OperatorEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperatorEditorDialog(const QModelIndex& index = {},
                                  DataModel *model = nullptr,
                                  QWidget* parent = nullptr);

public slots:
    void onSaveClicked();
    void loadIcon(const QString& mcc);

private:
    bool checkEmptyFields() const;

private:
    QModelIndex m_index;
    DataModel *m_model = nullptr;
    DatabaseManager& m_DatabaseManager;
    QLabel *m_nameOperator = nullptr;
    QLabel *m_mccLabel = nullptr;
    QLabel *m_mncLabel = nullptr;
    QLabel *m_iconCountry = nullptr;
    QLineEdit *m_nameEdit = nullptr;
    QLineEdit *m_mccEdit = nullptr;
    QLineEdit *m_mncEdit = nullptr;
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_cancelButton = nullptr;
};
