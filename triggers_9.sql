CREATE OR REPLACE FUNCTION unit_consistency() RETURNS TRIGGER AS
$$
DECLARE
    id_military_subdivisions_type bigint;
BEGIN
    SELECT type INTO id_military_subdivisions_type FROM military_subdivisions WHERE id = NEW.id;
    if id_military_subdivisions_type != 5 THEN
        RAISE EXCEPTION 'you cannot add % to this table, because this only for units', (SELECT name FROM subdivision_ranks WHERE id = NEW.id);
    end if;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER military_unit_update_trigger
    BEFORE UPDATE
    ON military_unit
    FOR EACH ROW
EXECUTE FUNCTION unit_consistency();

CREATE OR REPLACE TRIGGER military_unit_insert_trigger
    BEFORE INSERT
    ON military_unit
    FOR EACH ROW
EXECUTE FUNCTION unit_consistency();

