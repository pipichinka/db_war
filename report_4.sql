--Получить цепочку подчиненности снизу доверху для указанного военнослужащего.

WITH RECURSIVE r AS (

    SELECT
        id, head FROM employees WHERE id = 294

    UNION

    SELECT
        employees.id as id, employees.head FROM employees LEFT JOIN military_subdivisions ms on employees.head = ms.id INNER JOIN r on part_of = r.head
)
SELECT employees.id as id, employees.name as name, work, employee_ranks.name as rank
FROM r INNER JOIN military_subdivisions on military_subdivisions.id = r.head
    INNER JOIN employees on employees.work = military_subdivisions.id
    INNER JOIN employee_ranks on employees.rank = employee_ranks.id;