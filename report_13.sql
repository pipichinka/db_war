--Получить данные об армии, дивизии, корпусе, в которые входит больше всего (меньше
--всего) военных частей.

WITH
    specific_army as (SELECT id from military_subdivisions WHERE military_subdivisions.type = 1),
    specific_under_army as (SELECT ms.id, specific_army.id as army FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of),
    specific_units as (SELECT count(ms.id), army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of
                                          group by army),
    army_units as ( SELECT specific_units.army as army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.army)

SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.army = military_subdivisions.id
          WHERE army_units.number_of_units = (SELECT min(number_of_units) from army_units);


--for under army
WITH
    specific_under_army as (SELECT ms.id FROM  military_subdivisions ms WHERE type = 2),
    specific_units as (SELECT count(ms.id), specific_under_army.id as under_army FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of
                                          group by specific_under_army.id),
    army_units as ( SELECT specific_units.under_army as under_army, specific_units.count as number_of_units FROM specific_units INNER JOIN military_subdivisions on military_subdivisions.id = specific_units.under_army)

SELECT name, number_of_units FROM army_units INNER JOIN military_subdivisions on army_units.under_army = military_subdivisions.id
          WHERE army_units.number_of_units = (SELECT min(number_of_units) from army_units);