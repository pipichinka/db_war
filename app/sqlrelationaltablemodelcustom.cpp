#include "sqlrelationaltablemodelcustom.h"
#include <QWidget>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlField>
#include <QModelIndexList>
#include <QSqlQuery>
#include <QMessageBox>
#include <sstream>
#include <QSqlError>
#include <iostream>
SqlRelationalTableModelCustom::SqlRelationalTableModelCustom(QWidget* parent, QSqlDatabase* db, std::vector<ChangeCol> changeCols):
    QSqlRelationalTableModel(parent, *db),
    changeCols(changeCols)
{

}


bool SqlRelationalTableModelCustom::updateRowInTable(int row, const QSqlRecord &values){
    qDebug() << values;
    QSqlRecord r;
    for (int i = 0; i < values.count(); i++){
        bool isChange = false;
        for (size_t j = 0; j < changeCols.size(); j++){
            if (i != changeCols[j].col_id){
                continue;
            }
            QSqlTableModel* model = relationModel(i);
            QModelIndexList ids = model->match(model->index(0,changeCols[j].rel_val_id), Qt::EditRole, values.value(i));
            if (ids.empty()){
                QVariant data = values.value(i).toString().toLongLong();
                QSqlField field(changeCols[j].originalName, data.type(), values.field(0).tableName());
                field.setValue(data);
                field.setGenerated(false);
                r.append(field);
                isChange = true;
                continue;
            }
            QVariant data = model->data(model->index(ids[0].row(), changeCols[j].rel_index_id));
            QSqlField field(changeCols[j].originalName, data.type(), values.field(0).tableName());
            field.setValue(data);
            field.setGenerated(false);
            r.append(field);
            isChange = true;
        }
        if (!isChange){
            r.append(values.field(i));
        }
    }
    qDebug() << r;
    QSqlQuery q(database());
    std::stringstream s;
    s << "UPDATE " << values.field(0).tableName().toStdString() << " SET ";
    for (int i = 1; i < r.count(); i++){
        s << r.field(i).name().toStdString() << " = " << "?";
        if (i != r.count() - 1){
            s << ", ";
        } else {
            s << " ";
        }
    }

    s << "WHERE " << r.field(0).name().toStdString()  << " = " <<  r.value(0).toString().toStdString();
    std::string str = s.rdbuf()->str();
    std::cout << str << std::endl;
    QString v = QString::fromStdString(str);
    q.prepare(v);
    for (int i = 1; i < r.count(); i++){
        q.addBindValue(r.value(i));
    }
    if (!q.exec()){
        QMessageBox box(QMessageBox::Icon::Critical, "error", q.lastError().databaseText(), QMessageBox::Ok, qobject_cast<QWidget*>(this->parent()));
        box.exec();
        return false;
    }
//    select();
    return true;

}
