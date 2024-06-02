create view military_units_view(id, name) as
SELECT id, name
FROM military_subdivisions WHERE type = 5;