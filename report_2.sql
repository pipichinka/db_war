--Получить данные по офицерскому составу в целом и по офицерскому составу указанного
--звания всех частей военного округа, отдельной армии, дивизии, корпуса, военной части.

SELECT employees.name as "name",  employee_ranks.name as "rank", ms.name as "work_id", ms1.name as "head_of" FROM employees INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id
                                LEFT JOIN public.military_subdivisions ms on ms.id = employees.work
                                LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head
              WHERE employees.rank < 7;

--для специальных

-- для региона
WITH
    region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id
WHERE places.region_id = 2),
    specific_companies as (SELECT ms.id as id FROM region_units INNER JOIN military_subdivisions ms ON ms.part_of = region_units.id),
    specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id),
    specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id),
    subdivisions as (SELECT id from region_units UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads)



SELECT employees.name as "name",  employee_ranks.name as "rank", ms.name as "work_id", ms1.name as "head_of" FROM employees
                                INNER JOIN subdivisions ON subdivisions.id = employees.work
                                INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id
                                LEFT JOIN public.military_subdivisions ms on ms.id = employees.work
                                LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head
              WHERE employees.rank < 7;


--для армии

WITH
    specific_army as (SELECT id from military_subdivisions WHERE id = 551 ),
    specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id),
    specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id),
    specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id),
    subdivisions as (SELECT id from specific_army UNION SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads
    UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units)



SELECT employees.name as "name",  employee_ranks.name as "rank", ms.name as "work_id", ms1.name as "head_of" FROM employees
                                INNER JOIN subdivisions ON subdivisions.id = employees.work
                                INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id
                                LEFT JOIN public.military_subdivisions ms on ms.id = employees.work
                                LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head

--для под армии

WITH    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = 552),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id),
    specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id),
    specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id),
    subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads
    UNION SELECT id FROM specific_under_army UNION SELECT id FROM specific_units)



SELECT employees.name as "name",  employee_ranks.name as "rank", ms.name as "work_id", ms1.name as "head_of" FROM employees
                                INNER JOIN subdivisions ON subdivisions.id = employees.work
                                INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id
                                LEFT JOIN public.military_subdivisions ms on ms.id = employees.work
                                LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head
              WHERE employees.rank < 7;

--для unit
WITH    specific_units as (SELECT ms.id FROM  military_subdivisions ms WHERE id = 553),
    specific_companies as (SELECT ms.id as id FROM specific_units INNER JOIN military_subdivisions ms ON ms.part_of = specific_units.id),
    specific_platoons as (SELECT ms.id as id FROM specific_companies INNER JOIN military_subdivisions ms ON ms.part_of = specific_companies.id),
    specific_squads as (SELECT ms.id as id FROM specific_platoons INNER JOIN military_subdivisions ms ON ms.part_of = specific_platoons.id),
    subdivisions as (SELECT id FROM specific_companies UNION SELECT id FROM specific_platoons UNION SELECT  id FROM specific_squads
    UNION SELECT id FROM specific_units)



SELECT employees.name as "name",  employee_ranks.name as "rank", ms.name as "work_id", ms1.name as "head_of" FROM employees
                                INNER JOIN subdivisions ON subdivisions.id = employees.work
                                INNER JOIN  employee_ranks ON employees.rank = employee_ranks.id
                                LEFT JOIN public.military_subdivisions ms on ms.id = employees.work
                                LEFT JOIN public.military_subdivisions ms1 on ms1.id = employees.head
              WHERE employees.rank < 7;