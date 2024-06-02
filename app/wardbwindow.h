#ifndef WARDBWINDOW_H
#define WARDBWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class WarDBWindow; }
QT_END_NAMESPACE

class WarDBWindow : public QMainWindow
{
    Q_OBJECT

public:
    WarDBWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~WarDBWindow();

private slots:
    void on_table_assault_rifles_clicked();

    void on_unit_weapons_clicked();

    void on_war_regions_clicked();

    void on_places_clicked();

    void on_unit_transport_clicked();

    void on_unit_construction_clicked();

    void on_rifles_clicked();

    void on_artilleries_clicked();

    void on_missile_weapons_clicked();

    void on_infantry_combat_vehicles_clicked();

    void on_tanks_clicked();

    void on_tracktors_clicked();

    void on_vehicles_clicked();

    void on_generals_clicked();

    void on_colonels_clicked();

    void on_lieutenant_colonels_clicked();

    void on_majors_clicked();

    void on_captains_clicked();

    void on_lieutenants_clicked();

    void on_sergeantmajors_clicked();

    void on_sergeants_clicked();

    void on_ensigns_clicked();

    void on_corporals_clicked();

    void on_pushButton_9_clicked();

    void on_army_clicked();

    void on_corp_clicked();

    void on_division_clicked();

    void on_unit_clicked();

    void on_company_clicked();

    void on_pushButton_3_clicked();

    void on_squad_clicked();

    void on_brigade_clicked();

    void on_report_1_1_clicked();

    void on_report_1_2_clicked();

    void on_report_1_3_clicked();

    void on_pushButton_clicked();

    void on_report_2_2_clicked();

    void on_report_2_3_clicked();

    void on_report_2_4_clicked();

    void on_report_2_5_clicked();

    void on_report_3_1_clicked();

    void on_report_3_2_clicked();

    void on_report_3_3_clicked();

    void on_report_3_4_clicked();

    void on_report_3_5_clicked();

    void on_report_4_clicked();

    void on_report_5_1_clicked();

    void on_report_5_2_clicked();

    void on_report_5_3_clicked();

    void on_report_5_4_clicked();

    void on_report_6_1_clicked();

    void on_report_6_2_clicked();

    void on_report_6_3_clicked();

    void on_report_6_4_clicked();

    void on_report_7_1_clicked();

    void on_report_7_2_clicked();

    void on_report_7_3_clicked();

    void on_report_8_1_clicked();

    void on_report_8_2_clicked();

    void on_report_9_1_clicked();

    void on_report_9_2_clicked();

    void on_report_9_3_clicked();

    void on_report_9_4_clicked();

    void on_report_10_1_clicked();

    void on_report_10_2_clicked();

    void on_report_10_3_clicked();

    void on_report_10_4_clicked();

private:
    Ui::WarDBWindow *ui;
    QSqlDatabase* db;
};
#endif // WARDBWINDOW_H
