--Получить перечень военных частей, в которых число единиц указанного вида вооружения
--больше 10 (нет указанного вооружения).

SELECT military_subdivisions.name, unit_weapons.weapon_id, unit_weapons.amount from unit_weapons RIGHT JOIN military_unit on unit_weapons.unit_id = military_unit.id
    INNER JOIN weapons on unit_weapons.weapon_id = weapons.id
    INNER JOIN military_subdivisions on military_unit.id = military_subdivisions.id
WHERE weapons.type = 2 AND unit_weapons.amount > 10;

