--Получить данные о наличии боевой технике в целом и с учетом указанной категории или 
--вида во всех частях военного округа, в отдельной армии, дивизии, корпусе, военной части.

WITH
    region_units as (SELECT military_unit.id as id from military_unit INNER JOIN places ON military_unit.place_id = places.id
WHERE places.region_id = 2),
 t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport
    INNER JOIN region_units on region_units.id = unit_transport.unit_id
    INNER JOIN transport on unit_transport.transport_id = transport.id
GROUP BY transport_id)
SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id
        INNER JOIN transport_types on transport.type = transport_types.id;

-- для армии
WITH
    specific_army as (SELECT id from military_subdivisions WHERE id = 1 ),
    specific_under_army as (SELECT ms.id FROM specific_army INNER JOIN  military_subdivisions ms ON specific_army.id = ms.part_of),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport
    INNER JOIN specific_units on specific_units.id = unit_transport.unit_id
    INNER JOIN transport on unit_transport.transport_id = transport.id
GROUP BY transport_id)
SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id
        INNER JOIN transport_types on transport.type = transport_types.id;

-- для под армии
WITH    specific_under_army as (SELECT ms.id FROM military_subdivisions ms WHERE ms.id = 2),
    specific_units as (SELECT ms.id FROM specific_under_army INNER JOIN military_subdivisions ms ON specific_under_army.id = ms.part_of),
    t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport
    INNER JOIN specific_units on specific_units.id = unit_transport.unit_id
    INNER JOIN transport on unit_transport.transport_id = transport.id
GROUP BY transport_id)
SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id
        INNER JOIN transport_types on transport.type = transport_types.id;



WITH t as (SELECT transport_id, sum(unit_transport.amount)  FROM unit_transport
    INNER JOIN transport on unit_transport.transport_id = transport.id
WHERE unit_id =3
GROUP BY transport_id)
SELECT transport_id, t.sum as total_amout, transport_types.name as type FROM t INNER JOIN transport on t.transport_id = transport.id
        INNER JOIN transport_types on transport.type = transport_types.id
        
WHERE transport_types.id = ;
