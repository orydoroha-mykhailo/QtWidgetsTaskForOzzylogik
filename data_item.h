#pragma once

#include <qstring.h>
#include <qlist.h>

class DataItem
{
public:
    struct InitItem
    {
        QString imagePath;
        QString fullName;
        QString name;
        QString mcc;
        QString mnc;
    };

    DataItem(const InitItem& data = {});
    ~DataItem();

    int row() const;
    int childCount() const;
    DataItem *childAt(int row) const;
    DataItem *parent() const;

    QString getMcc() const;
    QString getMnc() const;
    QString getName() const;
    QString getFullName() const;
    QString getImagePath() const;

    void setMcc(const QString &mcc);
    void setMnc(const QString &mnc);
    void setName(const QString &name);
    void setFullName(const QString &fullName);
    void setImagePath(const QString &imagePath);

protected:
    QString m_mcc;
    QString m_mnc;
    QString m_name;
    QString m_fullName;
    QString m_imagePath;

private:
    DataItem* m_parent;
    QList<DataItem*> child;

    friend class DataModel;
};
