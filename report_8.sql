--Получить перечень военных частей, в которых число единиц указанного вида боевой
--техники больше 5 (нет указанной боевой техники).

SELECT t.type, unit_id, sum(unit_transport.amount) as total_amout from unit_transport RIGHT JOIN public.transport t on t.id = unit_transport.transport_id
group by t.type, unit_id
HAVING sum(unit_transport.amount) > 5;