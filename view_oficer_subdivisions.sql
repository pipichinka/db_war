create view oficer_subdivisions_view(id, name) as
SELECT id, name
FROM military_subdivisions WHERE type > 7;