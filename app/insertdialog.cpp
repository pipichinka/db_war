#include "insertdialog.h"
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(std::vector<QPair<QString, QWidget*>> fields, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog),
    fields(fields)
{
    ui->setupUi(this);
    for (const auto& pair: fields){
        pair.second->setParent(this);
        ui->formLayout->addRow(pair.first, pair.second);
    }

}

InsertDialog::~InsertDialog()
{
    delete ui;
}
