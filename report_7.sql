--Получить перечень сооружений указанной военной части, перечень сооружений, где
--дислоцировано более одного подразделения, где недислоцировано ни одного
--подразделения.


SELECT * FROM unit_constructions

WHERE unit_constructions.unit_id = 3;

-- более одного
WITH c as (SELECT unit_constructions.id, count(sd.construction_id) FROM unit_constructions LEFT JOIN public.subdivision_dislocation sd on unit_constructions.id = sd.construction_id
GROUP BY unit_constructions.id)

SELECT name, c.count as number_of_dislocations from c JOIN unit_constructions on c.id = unit_constructions.id
WHERE c.count > 1;

-- менее одного
WITH c as (SELECT unit_constructions.id, count(sd.construction_id) FROM unit_constructions LEFT JOIN public.subdivision_dislocation sd on unit_constructions.id = sd.construction_id
GROUP BY unit_constructions.id)

SELECT name FROM c INNER JOIN unit_constructions on c.id = unit_constructions.id
WHERE c.count = 0;

