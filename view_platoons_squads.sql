create view platoon_squads_view(id, name) as
SELECT id, name
FROM military_subdivisions WHERE type = 7 OR type = 8;