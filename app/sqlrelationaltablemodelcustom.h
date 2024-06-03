#ifndef SQLRELATIONALTABLEMODELCUSTOM_H
#define SQLRELATIONALTABLEMODELCUSTOM_H

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <vector>
#include <QString>
struct ChangeCol{
    int col_id;
    int rel_val_id;
    int rel_index_id;
    QString originalName;
    ChangeCol(int col_id, int rel_val_id, int rel_index_id, QString originalName):
        col_id(col_id), rel_val_id(rel_val_id), rel_index_id(rel_index_id), originalName(originalName){}
};


class SqlRelationalTableModelCustom:public QSqlRelationalTableModel
{
    Q_OBJECT
    std::vector<ChangeCol> changeCols;
protected:
    bool updateRowInTable(int row,const QSqlRecord &values) override;
public:
    SqlRelationalTableModelCustom(QWidget* parend, QSqlDatabase* db, std::vector<ChangeCol> changeCols);
};

#endif // SQLRELATIONALTABLEMODELCUSTOM_H
