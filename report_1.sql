--Получить перечень всех частей военного округа, указанной армии, дивизии, корпуса и их
--командиров.
-- $region$
-- $army$
-- $brigade$
-- $corp$
-- $division$


WITH (SELECT "militari_unit"."id" as "id" from "military_unit" INNER JOIN "places" ON "military_unit"."place_id" = "places"."id" 
WHERE "places"."region" = $region$) AS "region_units"

SELECT * FROM "region_units" INNER JOIN "military_subdivisions" "ms1" ON "region_units"."id" = "ms1"."id"
                            INNER JOIN "military_subdivisions" "ms2" ON "ms1"."part_of" = "ms2"."id"
                            WHERE "ms2"."id" = $grigade$