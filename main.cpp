#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

int counter_for_employees = 1;

int counter_for_subdivision = 1;

int counter_for_construction = 1;


const char* pets[] = {
    "cat",
    "dog",
    "parrot",
    "rabbit"
};

int pets_counter = 0;


const char* names[] = {
    "Alexander",
    "Alexei",
    "Andrei",
    "Artem",
    "Boris",
    "Vadim",
    "Victor",
    "Vladimir",
    "Dmitry",
    "Ivan",
    "Konstantin",
    "Leonid",
    "Maxim",
    "Mikhail",
    "Pavel",
    "Sergei",
    "Gleb",
    "Albert",
    "Artur",
    "Valentin",
    "Vasiliy",
    "Georgy"
};

int name_counter = 0;

const char* middle_names[] = {
    "Alexandrovich",
    "Alexeyevich",
    "Andreyevich",
    "Artemovich",
    "Borisovich",
    "Vadimovich",
    "Viktorovich",
    "Vladimirovich",
    "Dmitriyevich",
    "Ivanovich",
    "Konstantinovich",
    "Leonidovich",
    "Maximovich",
    "Mikhailovich",
    "Pavlovich",
    "Sergeyevich",
    "Glebov",
    "Albertovich",
    "Arturovich",
    "Valentinovich",
    "Vasiliyvich",
    "Georgyvich"
};

int middle_name_counter = 0;

const char* last_names[]{
    "Ivanov",
    "Petrov",
    "Sidorov",
    "Vasiliev",
    "Kuznetsov",
    "Popov",
    "Sokolov",
    "Mikhailov",
    "Fedorov",
    "Lebedev",
    "Kozlov",
    "Smirnov",
    "Nikolaev",
    "Orlov",
    "Zakharov",
    "Volkov",
    "Sokolov",
    "Morozov",
    "Pavlov",
    "Golubev",
    "Vorobiev",
    "Komorov"
};

int last_name_counter = 0;


std::string generate_name(){
    std::string res = names[name_counter];
    res += " ";
    res += middle_names[middle_name_counter];
    res += " ";
    res += last_names[last_name_counter];
    name_counter++;
    if (name_counter == 22){
        middle_name_counter++;
        name_counter = 0;
    }
    if (middle_name_counter == 22){
        middle_name_counter = 0;
        last_name_counter++;
    }
    if (last_name_counter == 22){
        last_name_counter = 0;
        middle_name_counter = 0;
        name_counter = 0;
    }
    return res;
}


std::string generate_random_date(){
    std::string res = std::to_string(1960 + (rand() % 60));
    res += "-";
    res += std::to_string(1 + rand()%12);
    res += "-";
    res += std::to_string(1 + rand() % 28);
    return res;
}

const char* get_pet_name(){
    const char* res = pets[pets_counter];
    pets_counter = (pets_counter + 1) % 4;
    return res;
}


enum employee_ranks{
    GENERAL = 1,

    COLONEL, 

    LIEUTENANT_COLONEL,

    MAJOR, 

    CAPTAIN,

    LIEUTENANT, 

    SERGEANTMAJOR, 

    SERGEANT,

    ENSIGN,  
    CORPORAL, 
    SOLDIER 
};


enum subdivision_ranks{
    ARMY = 1,
    BRIGADE,
    CORP,
    DIVISION,
    UNIT,
    COMPANY,
    PLATOON,
    SQUAD
};

struct unit{
    int id;
    int place_id;
    unit(int id, int place_id): id(id), place_id(place_id){
    }

    void print_values(std::ostream& s){
        s << "INSERT INTO \"military_unit\"(\"id\", \"place_id\")" << std::endl;
        s << "VALUES(" << id << ", " << place_id << ");" << std::endl;
    }
};





struct military_subdivision{
    int id;
    std::string name;
    int type;
    int part_of;
    military_subdivision(std::string& name, int type, int part_of): id(counter_for_subdivision++), name(name), type(type), part_of(part_of){
        
    }
    void print_values(std::ostream& s){
        if (part_of == -1){
            s << "INSERT INTO \"military_subdivisions\"(\"id\", \"name\", \"type\")" << std::endl;
            s << "VALUES(" << id << ", '" << name << "', " << type <<");" << std::endl;
            return;
        }
        s << "INSERT INTO \"military_subdivisions\"(\"id\", \"name\", \"type\", \"part_of\")" << std::endl;
        s << "VALUES(" << id << ", '" << name << "', " << type << ", " << part_of << ");" << std::endl;
    }
};


struct employee{
    int id;
    int rank;
    int work;
    std::string name;
    int head;
    std::vector<int> spec;
    employee(int rank, int work, std::string& name,int head): id(counter_for_employees++), rank(rank), work(work), name(name), head(head){
        int spec_num = 1 + (rand() % 3);
        if (spec_num == 1){
            spec.push_back(1 + (rand()% 6));
        } else if (spec_num == 2){
            int first_spec = 1 + (rand()% 6);
            int second_spec = 1 + (rand()% 6);
            while (second_spec == first_spec){
                second_spec = 1 + (rand() % 6);
            }
            spec.push_back(first_spec);
            spec.push_back(second_spec);
        } else {
            int first_spec = 1 + (rand()% 6);
            int second_spec = 1 + (rand()% 6);
            int third_spec = 1 + (rand() % 6);
            while (second_spec == first_spec){
                second_spec = 1 + (rand() % 6);
            }
            while (third_spec == first_spec || third_spec == second_spec){
                third_spec = 1 + (rand() % 6);
            }
            spec.push_back(first_spec);
            spec.push_back(second_spec);
            spec.push_back(third_spec);
        }
    }
    void print_values(std::ostream& s){
        if (head == -1){
            s << "INSERT INTO \"employees\"(\"id\", \"rank\", \"work\", \"name\")" << std::endl;
            s << "VALUES(" << id << ", " << rank << ", " << work << ", '" << name << "');" << std::endl;
        }
        else {
            s << "INSERT INTO \"employees\"(\"id\", \"rank\", \"work\", \"name\", \"head\")" << std::endl;
            s << "VALUES(" << id << ", " << rank << ", " << work << ", '" << name << "', "<< head << ");" << std::endl;
        }
        s << "INSERT INTO \"employees_specializations\"(\"employee_id\", \"spec_id\") VALUES" << std::endl;
        for (size_t i = 0; i < spec.size(); i++){
            s << "( " << id << ", " << spec[i] << ")";
            if (i == spec.size() - 1){
                s << ";";
            }
            else {
                s << ",";
            }
            s << std::endl;
        }
    }
};


struct general{
    int id;
    std::string hire_date;
    general(int id, std::string&& date):id(id), hire_date(date){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"generals\"(\"id\", \"hire_date\")" << std::endl;
        s << "VALUES(" << id << ", '" << hire_date << "');" << std::endl;
    }
};


struct colonel{
    int id;
    std::string pet;
    colonel(int id, std::string& pet):id(id), pet(pet){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"colonels\"(\"id\", \"pet\")" << std::endl;
        s << "VALUES(" << id << ", '" << pet << "');" << std::endl;
    }
};


struct lieutenant_colonel{
    int id;
    int height;
    lieutenant_colonel(int id, int height):id(id), height(height){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"lieutenant_colonels\"(\"id\", \"height\")" << std::endl;
        s << "VALUES(" << id << ", " << height << ");" << std::endl;
    }
};


struct major{
    int id;
    int weight;
    major(int id, int weight):id(id), weight(weight){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"majors\"(\"id\", \"weight\")" << std::endl;
        s << "VALUES(" << id << ", " << weight << ");" << std::endl;
    }
};


struct captain{
    int id;
    std::string hire_date;
    captain(int id, std::string&& date):id(id), hire_date(date){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"captains\"(\"id\", \"hire_date\")" << std::endl;
        s << "VALUES(" << id << ", '" << hire_date << "');" << std::endl;
    }
};


struct lieutenant{
    int id;
    std::string pet;
    lieutenant(int id, std::string& pet):id(id), pet(pet){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"lieutenants\"(\"id\", \"pet\")" << std::endl;
        s << "VALUES(" << id << ", '" << pet << "');" << std::endl;
    }
};

struct sergeantmajor{
    int id;
    int selary;
    sergeantmajor(int id, int selary):id(id), selary(selary){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"sergeantmajors\"(\"id\", \"selary\")" << std::endl;
        s << "VALUES(" << id << ", " << selary << ");" << std::endl;
    }
};

struct sergeant{
    int id;
    int weight;
    sergeant(int id, int weight):id(id), weight(weight){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"sergeants\"(\"id\", \"weight\")" << std::endl;
        s << "VALUES(" << id << ", " << weight << ");" << std::endl;
    }
};

struct ensign{
    int id;
    std::string hire_date;
    ensign(int id, std::string&& hire_date):id(id), hire_date(hire_date){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"ensigns\"(\"id\", \"hire_date\")" << std::endl;
        s << "VALUES(" << id << ", '" << hire_date << "');" << std::endl;
    }
};


struct corporal{
    int id;
    int height;
    corporal(int id, int height):id(id), height(height){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"corporals\"(\"id\", \"height\")" << std::endl;
        s << "VALUES(" << id << ", " << height << ");" << std::endl;
    }
};

struct soldier{
    int id;
    std::string birth_date;
    soldier(int id, std::string&& birth_date):id(id), birth_date(birth_date){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"soldiers\"(\"id\", \"birth_date\")" << std::endl;
        s << "VALUES(" << id << ", '" << birth_date << "');" << std::endl;
    }
};


struct construction{
    int id;
    std::string name;
    bool dislocation;
    int unit_id;
    construction(std::string& name, bool dislocation, int unit_id):id(counter_for_construction++), name(name), dislocation(dislocation), unit_id(unit_id) {}  
    void print_values(std::ostream& s){
        s << "INSERT INTO \"unit_constructions\"(\"id\", \"name\", \"dislocation\", \"unit_id\")" << std::endl;
        s << "VALUES(" << id << ", '" << name << "', '" << dislocation << "', " << unit_id << ");" << std::endl;
    }
};


struct subdivision_dislocation{
    int subdivision_id;
    int construction_id;
    subdivision_dislocation(int subdivision_id, int construction_id): subdivision_id(subdivision_id), construction_id(construction_id){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"subdivision_dislocation\"(\"subdivision_id\", \"construction_id\")" << std::endl;
        s << "VALUES(" << subdivision_id << ", " << construction_id << ");" << std::endl;
    }
};


struct unit_transport{
    int unit_id;
    int transport_id;
    int amount;

    unit_transport(int unit_id, int transport_id, int amount):unit_id(unit_id), transport_id(transport_id), amount(amount){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"unit_transport\"(\"unit_id\", \"transport_id\", \"amount\")" << std::endl;
        s << "VALUES(" << unit_id << ", " << transport_id << ", " << amount << ");" << std::endl;
    }
};

struct unit_weapons{
    int unit_id;
    int weapon_id;
    int amount;

    unit_weapons(int unit_id, int weapon_id, int amount):unit_id(unit_id), weapon_id(weapon_id), amount(amount){}
    void print_values(std::ostream& s){
        s << "INSERT INTO \"unit_weapons\"(\"unit_id\", \"weapon_id\", \"amount\")" << std::endl;
        s << "VALUES(" << unit_id << ", " << weapon_id << ", " << amount << ");" << std::endl;
    }
};


void create_squad(std::ostream& s, int head, std::vector<int>& cons, bool dislocated){
    std::string squad_name = "squad " + std::to_string(counter_for_subdivision);
    military_subdivision squad(squad_name, COMPANY, head);
    squad.print_values(s);
    if (dislocated){
        int random_index = (rand() % (int) cons.size());
        subdivision_dislocation sd(squad.id, cons[random_index]);
        sd.print_values(s);
    }
    std::string ser_name = generate_name();
    employee ser(SERGEANT, squad.id, ser_name, squad.id);
    ser.print_values(s);
    sergeant ser1(ser.id, 60 + (rand() % 30));
    ser1.print_values(s);

    int number_of_ensign = rand() % 5;
    for (int i = 0; i < number_of_ensign; i++){
        std::string e_name = generate_name();
        employee e(ENSIGN, squad.id, e_name, -1);
        e.print_values(s);
        ensign e1(e.id, generate_random_date());
        e1.print_values(s);
    }

    int number_of_corporals = rand() % 5;
    for (int i = 0; i < number_of_corporals; i++){
        std::string c_name = generate_name();
        employee c(CORPORAL, squad.id, c_name, -1);
        c.print_values(s);
        corporal c1(c.id, 160 + (rand() % 30));
        c1.print_values(s);
    }
    int number_of_soldiers = rand() % 5;
    for (int i = 0; i < number_of_soldiers; i++){
        std::string sol_name = generate_name();
        employee sol(CORPORAL, squad.id, sol_name, -1);
        sol.print_values(s);
        soldier sol1(sol.id, generate_random_date());
        sol1.print_values(s);
    }

}


void create_platoon(std::ostream& s, int head, std::vector<int>& cons, bool dislocated){
    std::string platoon_name = "platoon " + std::to_string(counter_for_subdivision);
    military_subdivision platoon(platoon_name, COMPANY, head);
    platoon.print_values(s);
    if (dislocated){
        int random_index = (rand() % (int) cons.size());
        subdivision_dislocation sd(platoon.id, cons[random_index]);
        sd.print_values(s);
    }
    std::string sm_name = generate_name();
    employee sm(SERGEANTMAJOR, platoon.id, sm_name, platoon.id);
    sm.print_values(s);
    sergeantmajor sm1(sm.id, 75000 + (rand() % 20000));
    sm1.print_values(s);

    int number_of_squads = 1 + (rand() % 4);
    if (cons.size() == 0 || dislocated){
        for (int i = 0; i < number_of_squads; i++){
            create_squad(s, platoon.id, cons, false);
        }
        return;
    }
    
    for (int i = 0; i < number_of_squads; i++){
        create_squad(s, platoon.id, cons, true);
    }
}


void create_company(std::ostream& s, int head, std::vector<int>& cons, bool dislocated){
    std::string company_name = "company " + std::to_string(counter_for_subdivision);
    military_subdivision company(company_name, COMPANY, head);
    company.print_values(s);
    if (dislocated){
        int random_index = (rand() % (int) cons.size());
        subdivision_dislocation sd(company.id, cons[random_index]);
        sd.print_values(s);
    }
    std::string l_name = generate_name();
    employee l(LIEUTENANT, company.id, l_name, company.id);
    l.print_values(s);
    std::string pet_name = get_pet_name();
    lieutenant l1(l.id, pet_name);
    l1.print_values(s);
    
    int number_of_platoons = 1 + (rand() % 5);

    for (int i = 0; i < number_of_platoons; i++){
        if (dislocated){
            std::vector<int> fake_cons;
            create_platoon(s, company.id, fake_cons, false);
            continue;
        }
        if (rand() % 2){
            create_platoon(s, company.id, cons, true);
        } else {
            create_platoon(s, company.id, cons, false);
        }
    }
}


void create_unit(std::ostream& s, int head){
    std::string unit_name = "unit " + std::to_string(counter_for_subdivision);
    military_subdivision unit_sub(unit_name, UNIT, head);
    unit u(unit_sub.id, 1 + (rand() % 6));
    unit_sub.print_values(s);
    u.print_values(s);

    std::string colonel_name = generate_name();
    employee c(CAPTAIN, unit_sub.id, colonel_name, unit_sub.id);
    c.print_values(s);
    captain c1(c.id, generate_random_date());
    c1.print_values(s);
    
        
    std::vector<int> con_with_disl;
    int constructions_with_disl = 2 + (rand() % 5);
    int constructions_without_disl = 1 + (rand() % 2);
    for (int i = 0; i < constructions_with_disl; i++){
        std::string con_name = "construction " + std::to_string(counter_for_construction);
        construction con(con_name, true, unit_sub.id);
        con.print_values(s);
        con_with_disl.push_back(con.id);
    }
    for (int i = 0; i < constructions_without_disl; i++){
        std::string con_name = "construction " + std::to_string(counter_for_construction);
        construction con(con_name, false, unit_sub.id);
        con.print_values(s);
    }

    for (int i = 1; i <= 12; i++){
        unit_transport ut(unit_sub.id, i, 1 + rand() % 20);
        ut.print_values(s);
    }

    for (int i = 1; i <= 8; i++){
        unit_weapons uw(unit_sub.id, i, 1 + rand() % 100);
        uw.print_values(s);
    }

    

    int number_companies = 2 + (rand() % 4);
    for (int i = 0; i < number_companies; i++){
        if (rand() % 2){
            create_company(s, unit_sub.id, con_with_disl, true);
        }
        else {
            create_company(s, unit_sub.id, con_with_disl, false);
        }
    }
}


void create_corp(std::ostream& s, int head){
    std::string corp_name = "corp " + std::to_string(counter_for_subdivision);
    military_subdivision corp(corp_name, CORP, head);
    corp.print_values(s);
    std::string colonel_name = generate_name();
    employee c(COLONEL, corp.id, colonel_name, corp.id);
    c.print_values(s);
    std::string pet_name = get_pet_name();
    colonel c1(c.id, pet_name);
    c1.print_values(s);
    int number_of_units = 1 + rand() % 4;
    for (int i = 0; i < number_of_units; i++){
        create_unit(s, corp.id);
    }
}


void create_brigade(std::ostream& s, int head){
    std::string brigade_name = "brigade " + std::to_string(counter_for_subdivision);
    military_subdivision brigade(brigade_name, BRIGADE, head);
    brigade.print_values(s);
    std::string lc_name = generate_name();
    employee lc(LIEUTENANT_COLONEL, brigade.id, lc_name, brigade.id);
    lc.print_values(s);
    lieutenant_colonel lc1(lc.id, 150 + (rand() % 50));
    lc1.print_values(s);
    int number_of_units = 1 + rand() % 3;
    for (int i = 0; i < number_of_units; i++){
        create_unit(s, brigade.id);
    }
}


void create_division(std::ostream& s, int head){
    std::string division_name = "division " + std::to_string(counter_for_subdivision);
    military_subdivision division(division_name, DIVISION, head);
    division.print_values(s);
    std::string m_name = generate_name();
    employee m(MAJOR, division.id, m_name, division.id);
    m.print_values(s);
    major m1(m.id, 60 + (rand() % 50));
    m1.print_values(s);
    int number_of_units = 1 + rand() % 2;
    for (int i = 0; i < number_of_units; i++){
        create_unit(s, division.id);
    }
}


void create_army(std::ostream& s){
    std::string army_name = "army " + std::to_string(counter_for_subdivision);
    military_subdivision army(army_name ,(int) ARMY, -1);
    army.print_values(s);
    std::string general_name = generate_name();
    employee g(GENERAL, army.id, general_name, army.id);
    g.print_values(s);
    general g1(g.id,generate_random_date());
    g1.print_values(s);
    int number_of_brigades = rand() % 5;
    int number_of_divisions = rand() % 5;
    int number_of_corps = rand() % 5;
    for (int i = 0; i < number_of_brigades; i++){
        create_brigade(s, army.id);
    }
    for (int i = 0; i < number_of_divisions; i++){
        create_corp(s, army.id);
    }
    for (int i = 0; i < number_of_corps; i++){
        create_division(s, army.id);
    }

}


int main(){
    std::ofstream f("load.sql");
    create_army(f);
    create_army(f);
    create_army(f);
    create_army(f);
    return 0;
}