--Получить данные о наличии вооружения в целом и с учетом указанной категории или вида
--во всех частях военного округа, в отдельной армии, дивизии, корпусе, военной части.

WITH
    region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id
WHERE places.region_id = $region_id$),
 t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons
    INNER JOIN region_units on region_units.id = unit_weapons.unit_id
    INNER JOIN weapons on unit_weapons.weapon_id = weapons.id
GROUP BY weapon_id)
SELECT weapons.name as name, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id
        INNER JOIN weapon_types on weapons.type = weapon_types.id WHERE weapon_types.id = $weapon_type$ ;

-- для армии
WITH
    specific_army as (SELECT id from military_subdivisions WHERE id = $army_id$ ),
    specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons
    INNER JOIN specific_units on specific_units.id = unit_weapons.unit_id
    INNER JOIN weapons on unit_weapons.weapon_id = weapons.id
GROUP BY weapon_id)
SELECT weapons.name as name, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id
        INNER JOIN weapon_types on weapons.type = weapon_types.id WHERE weapon_types.id = $weapon_type$ ;

-- для под армии
WITH    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = $under_army_id$),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons
    INNER JOIN specific_units on specific_units.id = unit_weapons.unit_id
    INNER JOIN weapons on unit_weapons.weapon_id = weapons.id
GROUP BY weapon_id)
SELECT weapons.name as name, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id
        INNER JOIN weapon_types on weapons.type = weapon_types.id WHERE weapon_types.id = $weapon_type$ ;



--для unit
WITH t as (SELECT weapon_id, sum(unit_weapons.amount)  FROM unit_weapons
    INNER JOIN weapons on unit_weapons.weapon_id = weapons.id
WHERE unit_id = $unit_id$
GROUP BY weapon_id)
SELECT weapons.name as name, t.sum as total_amout, weapon_types.name as type FROM t INNER JOIN weapons on t.weapon_id = weapons.id
        INNER JOIN weapon_types on weapons.type = weapon_types.id WHERE weapon_types.id = $weapon_type$ ;
