#include "wardbwindow.h"
#include "./ui_wardbwindow.h"
#include "assaultriflestablewindow.h"
#include "unitweaponstable.h"
#include "warregionwindow.h"
#include "placewindow.h"
#include "unittransport.h"
#include "unitconstructionwindow.h"
#include "rifleswindow.h"
#include "artillerieswindow.h"
#include "missileweaponswindow.h"
#include "infantrycombatvehicleswindow.h"
#include "tankswindow.h"
#include "tractorswindow.h"
#include "vehicleswindow.h"
#include "generalswindow.h"
#include "colonelswindow.h"
#include "lieutenantcolonelswindow.h"
#include "majorswindow.h"
#include "captainswindow.h"
#include "lieutenantswindow.h"
#include "sergeantmajorswindow.h"
#include "sergeantswindow.h"
#include "ensignswindow.h"
#include "corporalswindow.h"
#include "soldierswindow.h"
#include "arrmywindow.h"
#include "brigadewindow.h"
#include "corpwindow.h"
#include "divisionwindow.h"
#include "militaryunitwindow.h"
#include "companywindow.h"
#include "platoonwindow.h"
#include "squadwindow.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QComboBox>
#include "insertdialog.h"
#include <QtDebug>
#include <QCheckBox>
#include <QMessageBox>
WarDBWindow::WarDBWindow(QSqlDatabase* db, app_roles role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WarDBWindow),
      db(db),
      role(role)
{
    ui->setupUi(this);
}

WarDBWindow::~WarDBWindow()
{
    delete ui;
}


void WarDBWindow::on_table_assault_rifles_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    AssaultRiflesTableWindow* window = new AssaultRiflesTableWindow(db, this);
    window->show();
}


void WarDBWindow::on_unit_weapons_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    UnitWeaponsTable* window = new UnitWeaponsTable(db, this);
    window->show();
}


void WarDBWindow::on_war_regions_clicked()
{

    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    WarRegionWindow* window = new WarRegionWindow(db, this);
    window->show();
}


void WarDBWindow::on_places_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    PlaceWindow* window = new PlaceWindow(db, this);
    window->show();
}


void WarDBWindow::on_unit_transport_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    UnitTransport* window = new UnitTransport(db, this);
    window->show();
}


void WarDBWindow::on_unit_construction_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    UnitConstructionWindow* window = new UnitConstructionWindow(db, this);
    window->show();
}


void WarDBWindow::on_rifles_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    RiflesWindow* window = new RiflesWindow(db, this);
    window->show();
}


void WarDBWindow::on_artilleries_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    ArtilleriesWindow* window = new ArtilleriesWindow(db, this);
    window->show();
}


void WarDBWindow::on_missile_weapons_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    MissileWeaponsWindow* window = new MissileWeaponsWindow(db, this);
    window->show();
}


void WarDBWindow::on_infantry_combat_vehicles_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    InfantryCombatVehiclesWindow* window = new InfantryCombatVehiclesWindow(db, this);
    window->show();
}


void WarDBWindow::on_tanks_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    TanksWindow* window = new TanksWindow(db, this);
    window->show();
}


void WarDBWindow::on_tracktors_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    TractorsWindow* window = new TractorsWindow(db, this);
    window->show();
}


void WarDBWindow::on_vehicles_clicked()
{
    if (!(role & SUPPLIER_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least SUPPLIER", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    VehiclesWindow* window = new VehiclesWindow(db, this);
    window->show();
}


void WarDBWindow::on_generals_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    GeneralsWindow* window = new GeneralsWindow(db, this);
    window->show();
}


void WarDBWindow::on_colonels_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    ColonelsWindow* window = new ColonelsWindow(db, this);
    window->show();
}


void WarDBWindow::on_lieutenant_colonels_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    LieutenantColonelsWindow* window = new LieutenantColonelsWindow(db, this);
    window->show();
}


void WarDBWindow::on_majors_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    majorsWindow* window = new majorsWindow(db, this);
    window->show();
}


void WarDBWindow::on_captains_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    CaptainsWindow* window = new CaptainsWindow(db, this);
    window->show();
}


void WarDBWindow::on_lieutenants_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    CaptainsWindow* window = new CaptainsWindow(db, this);
    window->show();
}


void WarDBWindow::on_sergeantmajors_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    SergeantmajorsWindow* window = new SergeantmajorsWindow(db, this);
    window->show();
}


void WarDBWindow::on_sergeants_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    SergeantsWindow* window = new SergeantsWindow(db, this);
    window->show();
}


void WarDBWindow::on_ensigns_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    EnsignsWindow* window = new EnsignsWindow(db, this);
    window->show();
}


void WarDBWindow::on_corporals_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    CorporalsWindow* window = new CorporalsWindow(db, this);
    window->show();
}


void WarDBWindow::on_pushButton_9_clicked()
{
    if (!(role & HR_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must be at least HR", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    SoldiersWindow* window = new SoldiersWindow(db, this);
    window->show();
}


void WarDBWindow::on_army_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    ArrmyWindow* window = new ArrmyWindow(db, this);
    window->show();
}


void WarDBWindow::on_corp_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    CorpWindow* window = new CorpWindow(db, this);
    window->show();
}


void WarDBWindow::on_division_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    divisionWindow* window = new divisionWindow(db, this);
    window->show();
}


void WarDBWindow::on_unit_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    MilitaryUnitWindow* window = new MilitaryUnitWindow(db, this);
    window->show();
}


void WarDBWindow::on_company_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    CompanyWindow* window = new CompanyWindow(db, this);
    window->show();
}


void WarDBWindow::on_pushButton_3_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    PlatoonWindow* window = new PlatoonWindow(db, this);
    window->show();
}


void WarDBWindow::on_squad_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    SquadWindow* window = new SquadWindow(db, this);
    window->show();
}


void WarDBWindow::on_brigade_clicked()
{
    if (!(role == ADMIN_ROLE)){
        QMessageBox box(QMessageBox::Icon::Critical, "error", "you must ADMIN", QMessageBox::Ok, this);
        box.exec();
        return;
    }
    BrigadeWindow* window = new BrigadeWindow(db, this);
    window->show();
}



void showReport(QSqlQuery& q){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(q);
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("report data");
    view->show();
}


bool makeRegionRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("military_region");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(0);
    InsertDialog dialog({{"region", box}});
    dialog.setWindowTitle("choose report parameters");
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 1), Qt::EditRole);
        return true;
    }
    return false;
}


bool makeArmyRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("army_view");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"army", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


bool makeUnderArmyRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("under_army_view");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"subdivision", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


bool makeUnitRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("military_units_view");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"unit", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


bool makeRankRequest(QVariant& res, QSqlDatabase* db, bool is_oficier){
    QSqlQueryModel*  t= new QSqlQueryModel(nullptr);
    if (is_oficier){
        t->setQuery("select * from employee_ranks where id > 7", *db);
    } else {
        t->setQuery("select * from employee_ranks where id <= 7", *db);
    }
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"rank", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


void WarDBWindow::on_report_1_1_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id" \
                " WHERE places.region_id = ?) SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank " \
                " FROM region_units INNER JOIN military_subdivisions ms1 ON region_units.id = ms1.id " \
                                            " INNER JOIN military_subdivisions ms2 ON ms1.part_of = ms2.id " \
                                            " INNER JOIN military_subdivisions ms3 ON ms2.part_of = ms3.id " \
                                            " LEFT JOIN employees ON employees.head = region_units.id " \
                                            " INNER JOIN employee_ranks ON employee_ranks.id = employees.rank";
    q.prepare(s);
    QVariant region_id;
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_1_2_clicked()
{
    QSqlQuery q(*db);
    QString s ="WITH specific_army as (SELECT id from military_subdivisions WHERE id = ?)," \
            " specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of) "\
        " SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank " \
        " FROM specific_units INNER JOIN military_subdivisions ms1 ON specific_units.id = ms1.id " \
                                    " LEFT JOIN employees ON employees.head = specific_units.id " \
                                    " INNER JOIN employee_ranks ON employee_ranks.id = employees.rank ";

    q.prepare(s);
    QVariant army_id;
    if (makeArmyRequest(army_id, db)){
        q.addBindValue(army_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_1_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of)" \
        " SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank" \
        " FROM specific_units INNER JOIN military_subdivisions ms1 ON specific_units.id = ms1.id" \
                                    " LEFT JOIN employees ON employees.head = specific_units.id" \
                                    " INNER JOIN employee_ranks ON employee_ranks.id = employees.rank" ;

    q.prepare(s);
    QVariant underArmy_id;
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_pushButton_clicked()
{
    QSqlQuery q(*db);
    QString s = "SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work, ms1.name as head FROM employees INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id" \
            " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work" \
            " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head" \
            " WHERE employees.rank < 7";
    q.prepare(s);
    q.exec();
    showReport(q);

}


void WarDBWindow::on_report_2_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from region_units UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ?";
    q.prepare(s);
    QVariant region_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, true)){
        return;
    }
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_2_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_army as (SELECT id from military_subdivisions WHERE id = ? ), " \
            " specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from specific_army UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        "INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        "INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        "LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        "LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                                        "WHERE employees.rank = ?";

    q.prepare(s);
    QVariant army_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, true)){
        return;
    }
    if (makeArmyRequest(army_id, db)){
        q.addBindValue(army_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}




void WarDBWindow::on_report_2_4_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ?";

    q.prepare(s);
    QVariant underArmy_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, true)){
        return;
    }
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_2_5_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_units) " \
                " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ? ";

    q.prepare(s);
    QVariant unit_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, true)){
        return;
    }
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_3_1_clicked()
{
    QSqlQuery q(*db);
    QString s = "SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work, ms1.name as head FROM employees INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id" \
            " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work" \
            " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head" \
            " WHERE employees.rank >= 7";
    q.prepare(s);
    q.exec();
    showReport(q);
}


void WarDBWindow::on_report_3_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from region_units UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ?";
    q.prepare(s);
    QVariant region_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, false)){
        return;
    }
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_3_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_army as (SELECT id from military_subdivisions WHERE id = ? ), " \
            " specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from specific_army UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        "INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        "INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        "LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        "LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                                        "WHERE employees.rank = ?";

    q.prepare(s);
    QVariant army_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, false)){
        return;
    }
    if (makeArmyRequest(army_id, db)){
        q.addBindValue(army_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_3_4_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
        " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ?";

    q.prepare(s);
    QVariant underArmy_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, false)){
        return;
    }
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_3_5_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_units) " \
                " SELECT employees.name as name,  employee_ranks.name as rank, ms.name as work_id, ms1.name as head_of FROM employees " \
                                        " INNER JOIN subdivisions ON subdivisions.id = employees.work " \
                                        " INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id " \
                                        " LEFT JOIN public.military_subdivisions ms on ms.id = employees.work " \
                                        " LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head " \
                      " WHERE employees.rank = ? ";

    q.prepare(s);
    QVariant unit_id;
    QVariant rank_id;
    if (!makeRankRequest(rank_id, db, false)){
        return;
    }
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.addBindValue(rank_id);
        q.exec();
        showReport(q);
    }
}

bool makeEmployeeRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("employees");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(3);
    InsertDialog dialog({{"employee", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


void WarDBWindow::on_report_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH RECURSIVE r AS ( " \
                " SELECT " \
                    " id, head FROM employees WHERE id = ? " \
                " UNION " \
                " SELECT " \
                    " employees.id as id, employees.head FROM employees LEFT JOIN military_subdivisions ms on employees.head = ms.id INNER JOIN r on part_of = r.head " \
            " ) " \
            " SELECT employees.id as id, employees.name as name, work, employee_ranks.name as rank " \
            " FROM r INNER JOIN military_subdivisions on military_subdivisions.id = r.head " \
                " INNER JOIN employees on employees.work = military_subdivisions.id " \
                " INNER JOIN employee_ranks on employees.rank = employee_ranks.id ";

    q.prepare(s);
    QVariant employee_id;
    if (makeEmployeeRequest(employee_id, db)){
        q.addBindValue(employee_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_5_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
        " SELECT DISTINCT unit_constructions.name FROM subdivision_dislocation " \
            " INNER JOIN subdivisions on subdivision_id = subdivisions.id " \
            " INNER JOIN unit_constructions on subdivision_dislocation.subdivision_id = unit_constructions.id";
    q.prepare(s);
    QVariant region_id;
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_5_2_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
            " SELECT DISTINCT unit_constructions.name FROM subdivision_dislocation " \
                " INNER JOIN subdivisions on subdivision_id = subdivisions.id " \
                " INNER JOIN unit_constructions on subdivision_dislocation.subdivision_id = unit_constructions.id";

    q.prepare(s);
    QVariant Army_id;
    if (makeArmyRequest(Army_id, db)){
        q.addBindValue(Army_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_5_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
                " SELECT DISTINCT unit_constructions.name FROM subdivision_dislocation " \
                    " INNER JOIN subdivisions on subdivision_id = subdivisions.id " \
                    " INNER JOIN unit_constructions on subdivision_dislocation.subdivision_id = unit_constructions.id";

    q.prepare(s);
    QVariant underArmy_id;
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_5_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_units) " \
                " SELECT DISTINCT unit_constructions.name FROM subdivision_dislocation " \
                    " INNER JOIN subdivisions on subdivision_id = subdivisions.id " \
                    " INNER JOIN unit_constructions on subdivision_dislocation.subdivision_id = unit_constructions.id";

    q.prepare(s);
    QVariant unit_id;
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_6_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH " \
            " region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
         " t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport " \
            " INNER JOIN region_units on region_units.id = unit_transport.unit_id " \
            " INNER JOIN transport on unit_transport.transport_id = transport.id " \
        " GROUP BY transport_id) " \
        " SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id " \
                " INNER JOIN transport_types on transport.type = transport_types.id";
    q.prepare(s);
    QVariant region_id;
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_6_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH " \
            " specific_army as (SELECT id from military_subdivisions WHERE id = ? ), " \
            " specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport " \
            " INNER JOIN specific_units on specific_units.id = unit_transport.unit_id " \
            " INNER JOIN transport on unit_transport.transport_id = transport.id " \
        " GROUP BY transport_id) " \
        " SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id " \
                " INNER JOIN transport_types on transport.type = transport_types.id";

    q.prepare(s);
    QVariant Army_id;
    if (makeArmyRequest(Army_id, db)){
        q.addBindValue(Army_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_6_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport " \
            " INNER JOIN specific_units on specific_units.id = unit_transport.unit_id " \
            " INNER JOIN transport on unit_transport.transport_id = transport.id " \
        " GROUP BY transport_id) " \
        " SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id " \
                " INNER JOIN transport_types on transport.type = transport_types.id";

    q.prepare(s);
    QVariant underArmy_id;
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_6_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport " \
            " INNER JOIN transport on unit_transport.transport_id = transport.id " \
        " WHERE unit_id = ? " \
        " GROUP BY transport_id) " \
        " SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id " \
                " INNER JOIN transport_types on transport.type = transport_types.id";

    q.prepare(s);
    QVariant unit_id;
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.exec();
        showReport(q);
    }
}



void WarDBWindow::on_report_7_1_clicked()
{
    QSqlQuery q(*db);
    QString s = "SELECT * FROM unit_constructions   WHERE unit_constructions.unit_id = ?";

    q.prepare(s);
    QVariant unit_id;
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_7_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH c as (SELECT unit_constructions.id, count(sd.construction_id) FROM unit_constructions LEFT JOIN public.subdivision_dislocation sd on unit_constructions.id = sd.construction_id " \
            " GROUP BY unit_constructions.id) " \
            " SELECT name, c.count as number_of_dislocations from c RIGHT JOIN unit_constructions on c.id = unit_constructions.id " \
            " WHERE c.count > 1";

    q.prepare(s);
    q.exec();
    showReport(q);
}


void WarDBWindow::on_report_7_3_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH c as (SELECT unit_constructions.id, count(sd.construction_id) FROM unit_constructions LEFT JOIN public.subdivision_dislocation sd on unit_constructions.id = sd.construction_id " \
            " GROUP BY unit_constructions.id) " \
            " SELECT name, c.count as number_of_dislocations from c RIGHT JOIN unit_constructions on c.id = unit_constructions.id " \
            " WHERE c.count > 1";

    q.prepare(s);
    q.exec();
    showReport(q);
}


void WarDBWindow::on_report_8_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " SELECT t.type, unit_id, sum(unit_transport.amount) as total_amout from unit_transport RIGHT JOIN public.transport t on t.id = unit_transport.transport_id " \
            " group by t.type, unit_id " \
            " HAVING sum(unit_transport.amount) > 5";

    q.prepare(s);
    q.exec();
    showReport(q);
}


void WarDBWindow::on_report_8_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " SELECT t.type, unit_id, sum(unit_transport.amount) as total_amout from unit_transport RIGHT JOIN public.transport t on t.id = unit_transport.transport_id " \
            " group by t.type, unit_id " \
            " HAVING sum(unit_transport.amount) = 0";

    q.prepare(s);
    q.exec();
    showReport(q);
}


void WarDBWindow::on_report_9_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
         " t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons " \
            " INNER JOIN region_units on region_units.id = unit_weapons.unit_id " \
            " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
        " GROUP BY weapon_id) " \
        " SELECT weapon_id, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id " \
                " INNER JOIN weapon_types on weapons.type = weapon_types.id";
    q.prepare(s);
    QVariant region_id;
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_9_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH " \
            " specific_army as (SELECT id from military_subdivisions WHERE id = ? ), " \
            " specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons " \
            " INNER JOIN specific_units on specific_units.id = unit_weapons.unit_id " \
            " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
        " GROUP BY weapon_id) " \
        " SELECT weapon_id, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id " \
                " INNER JOIN weapon_types on weapons.type = weapon_types.id";

    q.prepare(s);
    QVariant Army_id;
    if (makeArmyRequest(Army_id, db)){
        q.addBindValue(Army_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_9_3_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons " \
            " INNER JOIN specific_units on specific_units.id = unit_weapons.unit_id " \
            " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
        " GROUP BY weapon_id) " \
        " SELECT weapon_id, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id " \
                " INNER JOIN weapon_types on weapons.type = weapon_types.id";

    q.prepare(s);
    QVariant underArmy_id;
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_9_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons " \
                           " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
                       " WHERE unit_id = ? " \
                       " GROUP BY weapon_id) " \
                       " SELECT weapon_id, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id " \
                               " INNER JOIN weapon_types on weapons.type = weapon_types.id";

    q.prepare(s);
    QVariant unit_id;
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_10_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH " \
            " region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from region_units UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
        " SELECT es.spec_id, count(es.spec_id) from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
            " RIGHT JOIN employees_specializations es on employees.id = es.employee_id " \
        " GROUP BY es.spec_id " \
        " HAVING count(es.spec_id) > 5";
    q.prepare(s);
    QVariant region_id;
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_10_2_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
            " SELECT es.spec_id, count(es.spec_id) from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " RIGHT JOIN employees_specializations es on employees.id = es.employee_id " \
            " GROUP BY es.spec_id " \
            " HAVING count(es.spec_id) > 5";

    q.prepare(s);
    QVariant Army_id;
    if (makeArmyRequest(Army_id, db)){
        q.addBindValue(Army_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_10_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " SELECT es.spec_id, count(es.spec_id) from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " RIGHT JOIN employees_specializations es on employees.id = es.employee_id " \
            " GROUP BY es.spec_id " \
            " HAVING count(es.spec_id) > 5";

    q.prepare(s);
    QVariant underArmy_id;
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_10_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads " \
            " SELECT es.spec_id, count(es.spec_id) from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " RIGHT JOIN employees_specializations es on employees.id = es.employee_id " \
            " GROUP BY es.spec_id " \
            " HAVING count(es.spec_id) > 5";

    q.prepare(s);
    QVariant unit_id;
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.exec();
        showReport(q);
    }
}


bool makeSpecRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("military_specializations");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"spec", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}




void WarDBWindow::on_report_11_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH " \
            " region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id " \
        " WHERE places.region_id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id from region_units UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
            " SELECT employees.name from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " INNER JOIN employees_specializations es on employees.id = es.employee_id " \
            " WHERE es.spec_id = ?";
    q.prepare(s);
    QVariant region_id;
    QVariant spec_id;
    if (!makeSpecRequest(spec_id, db)){
        return;
    }
    if (makeRegionRequest(region_id, db)){
        q.addBindValue(region_id);
        q.addBindValue(spec_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_11_2_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT id FROM specific_squads " \
            " UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units) " \
            " SELECT employees.name from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " INNER JOIN employees_specializations es on employees.id = es.employee_id " \
            " WHERE es.spec_id = ? ";

    q.prepare(s);
    QVariant Army_id;
    QVariant spec_id;
    if (!makeSpecRequest(spec_id, db)){
        return;
    }
    if (makeArmyRequest(Army_id, db)){
        q.addBindValue(Army_id);
        q.addBindValue(spec_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_11_3_clicked()
{
    QSqlQuery q(*db);
    QString s = "WITH specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = ?), " \
            " specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
            " SELECT employees.name from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " INNER JOIN employees_specializations es on employees.id = es.employee_id " \
            " WHERE es.spec_id = ?";

    q.prepare(s);
    QVariant underArmy_id;
    QVariant spec_id;
    if (!makeSpecRequest(spec_id, db)){
        return;
    }
    if (makeUnderArmyRequest(underArmy_id, db)){
        q.addBindValue(underArmy_id);
        q.addBindValue(spec_id);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_11_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = ?), " \
            " specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id), " \
            " specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id), " \
            " specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id), " \
            " subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads) " \
            " SELECT employees.name from subdivisions INNER JOIN employees on employees.work = subdivisions.id " \
                " INNER JOIN employees_specializations es on employees.id = es.employee_id " \
            " WHERE es.spec_id = ?";

    q.prepare(s);
    QVariant unit_id;
    QVariant spec_id;
    if (!makeSpecRequest(spec_id, db)){
        return;
    }
    if (makeUnitRequest(unit_id, db)){
        q.addBindValue(unit_id);
        q.addBindValue(spec_id);
        q.exec();
        showReport(q);
    }
}


bool makeWeaponTypeRequest(QVariant& res, QSqlDatabase* db){
    QSqlTableModel*  t= new QSqlTableModel(nullptr, *db);
    t->setTable("weapon_types");
    t->select();
    QComboBox* box = new QComboBox(nullptr);
    box->setModel(t);
    box->setModelColumn(1);
    InsertDialog dialog({{"weapon type", box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = t->data(t->index(box->currentIndex(), 0), Qt::EditRole);
        return true;
    }
    return false;
}


void WarDBWindow::on_report_12_1_clicked()
{
    QSqlQuery q(*db);
    QString s = " SELECT military_subdivisions.name, unit_weapons.weapon_id, unit_weapons.amount from unit_weapons RIGHT JOIN military_unit on unit_weapons.unit_id = military_unit.id " \
            " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
            " INNER JOIN military_subdivisions on military_unit.id = military_subdivisions.id " \
        " WHERE weapons.type = ? AND unit_weapons.amount > 10";

    q.prepare(s);
    QVariant weaponType;
    if (makeWeaponTypeRequest(weaponType, db)){
        q.addBindValue(weaponType);
        q.exec();
        showReport(q);
    }
}


void WarDBWindow::on_report_12_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " SELECT military_subdivisions.name, unit_weapons.weapon_id, unit_weapons.amount from unit_weapons RIGHT JOIN military_unit on unit_weapons.unit_id = military_unit.id " \
            " INNER JOIN weapons on unit_weapons.weapon_id = weapons.id " \
            " INNER JOIN military_subdivisions on military_unit.id = military_subdivisions.id " \
        " WHERE weapons.type = ? AND unit_weapons.amount = 0";

    q.prepare(s);
    QVariant weaponType;
    if (makeWeaponTypeRequest(weaponType, db)){
        q.addBindValue(weaponType);
        q.exec();
        showReport(q);
    }
}


bool makeShooseValue(QVariant& res, QSqlDatabase* db, const QString& text){

    QCheckBox* box = new QCheckBox;
    InsertDialog dialog({{text, box}});
    int dialog_res = dialog.exec();
    if (dialog_res == QDialog::Accepted){
        res = box->isChecked();
        return true;
    }
    return false;
}


void WarDBWindow::on_report_13_1_clicked()
{
     QSqlQuery q(*db);
     QString s = " WITH specific_army as (SELECT id from military_subdivisions WHERE military_subdivisions.type = 1), " \
             " specific_under_army as (SELECT ms.id, specific_army.id as army FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of), " \
             " specific_units as (SELECT count(ms.id), army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of group by army), " \
             " army_units as ( SELECT specific_units.army as army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.army)  " \
         " SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.army = military_subdivisions.id  " \
                   " WHERE army_units.number_of_units = (SELECT %1(number_of_units) from army_units)";
     QVariant v;
     if (makeShooseValue(v, db, "is_max")){
         if (v.toBool()){
             s = s.arg("max");
         } else{
             s = s.arg("min");
         }
         q.prepare(s);
         q.exec();
         showReport(q);

     }
}


void WarDBWindow::on_report_13_2_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_under_army as (SELECT ms.id FROM  military_subdivisions ms WHERE type = 2), " \
            " specific_units as (SELECT count(ms.id), specific_under_army.id as under_army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of "\
              " group by specific_under_army.id), " \
            "army_units as ( SELECT specific_units.under_army as under_army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.under_army) "\
        " SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.under_army = military_subdivisions.id "\
                  " WHERE army_units.number_of_units = (SELECT %1(number_of_units) from army_units)";

    QVariant v;
    if (makeShooseValue(v, db, "is_max")){
        if (v.toBool()){
            s = s.arg("max");
        } else{
            s = s.arg("min");
        }
        q.prepare(s);
        q.exec();
        showReport(q);

    }
}


void WarDBWindow::on_report_13_3_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_under_army as (SELECT ms.id FROM  military_subdivisions ms WHERE type = 3), " \
            " specific_units as (SELECT count(ms.id), specific_under_army.id as under_army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of "\
              " group by specific_under_army.id), " \
            "army_units as ( SELECT specific_units.under_army as under_army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.under_army) "\
        " SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.under_army = military_subdivisions.id "\
                  " WHERE army_units.number_of_units = (SELECT %1(number_of_units) from army_units)";

    QVariant v;
    if (makeShooseValue(v, db, "is_max")){
        if (v.toBool()){
            s = s.arg("max");
        } else{
            s = s.arg("min");
        }
        q.prepare(s);
        q.exec();
        showReport(q);

    }
}


void WarDBWindow::on_report_13_4_clicked()
{
    QSqlQuery q(*db);
    QString s = " WITH specific_under_army as (SELECT ms.id FROM  military_subdivisions ms WHERE type = 4), " \
            " specific_units as (SELECT count(ms.id), specific_under_army.id as under_army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of "\
              " group by specific_under_army.id), " \
            "army_units as ( SELECT specific_units.under_army as under_army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.under_army) "\
        " SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.under_army = military_subdivisions.id "\
                  " WHERE army_units.number_of_units = (SELECT %1(number_of_units) from army_units)";

    QVariant v;
    if (makeShooseValue(v, db, "is_max")){
        if (v.toBool()){
            s = s.arg("max");
        } else{
            s = s.arg("min");
        }
        q.prepare(s);
        q.exec();
        showReport(q);

    }
}

