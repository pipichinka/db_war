--Получить перечень всех частей военного округа, указанной армии, дивизии, корпуса и их
--командиров.

WITH region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id
WHERE places.region_id = 2)

SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank
FROM region_units INNER JOIN military_subdivisions ms1 ON region_units.id = ms1.id
                            INNER JOIN military_subdivisions ms2 ON ms1.part_of = ms2.id
                            INNER JOIN military_subdivisions ms3 ON ms2.part_of = ms3.id
                            LEFT JOIN employees ON employees.head = region_units.id
                            INNER JOIN employee_ranks ON employee_ranks.id = employees.rank;



WITH
    specific_army as (SELECT id from military_subdivisions WHERE id = 1),
    specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of)

SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank
FROM specific_units INNER JOIN military_subdivisions ms1 ON specific_units.id = ms1.id
                            LEFT JOIN employees ON employees.head = specific_units.id
                            INNER JOIN employee_ranks ON employee_ranks.id = employees.rank;


WITH
    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = 2),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of)

SELECT ms1.name AS subdivision_name, employees.name AS head_name, employee_ranks.name AS rank
FROM specific_units INNER JOIN military_subdivisions ms1 ON specific_units.id = ms1.id
                            LEFT JOIN employees ON employees.head = specific_units.id
                            INNER JOIN employee_ranks ON employee_ranks.id = employees.rank;