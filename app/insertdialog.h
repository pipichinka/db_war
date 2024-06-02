#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <vector>
#include <QPair>
#include <QString>
namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertDialog(std::vector<QPair<QString, QWidget*>> fields, QWidget *parent = nullptr);
    ~InsertDialog();

private:
    Ui::InsertDialog *ui;
    std::vector<QPair<QString, QWidget*>> fields;
};

#endif // INSERTDIALOG_H
