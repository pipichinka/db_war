--Получить перечень военных частей, в которых число единиц указанного вида боевой
--техники больше 5 (нет указанной боевой техники).

WITH t as (SELECT t.type, unit_id, sum(unit_transport.amount) as total_amout from unit_transport
    RIGHT JOIN transport t on t.id = unit_transport.transport_id
    RIGHT JOIN military_unit on unit_transport.unit_id = military_unit.id
group by t.type, unit_id
HAVING sum(unit_transport.amount) > 5)
SELECT wt.name as type, ms.name as unit, total_amout FROM t INNER JOIN weapon_types wt on wt.id = t.type INNER JOIN military_subdivisions ms on t.unit_id = ms.id;