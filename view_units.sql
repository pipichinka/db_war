create OR REPLACE view military_units_view(id, name, part_of, place_id) as
SELECT ms.id,
        ms.name,
        ms.part_of,
        mu.place_id
FROM military_subdivisions ms INNER JOIN military_unit mu on ms.id = mu.id;

CREATE OR REPLACE FUNCTION military_units_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 5, NEW.part_of) RETURNING id INTO insert_id;
    Insert Into military_unit VALUES (insert_id, NEW.place_id);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION military_units_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM military_unit WHERE id = OLD.id;
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION military_units_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_unit SET place_id = NEW.place_id WHERE id = NEW.id;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER military_units_view_insert_trigger
    INSTEAD OF INSERT
    ON military_units_view
    FOR EACH ROW
EXECUTE FUNCTION military_units_view_insert();

CREATE OR REPLACE TRIGGER military_units_view_delete_trigger
    INSTEAD OF DELETE
    ON military_units_view
    FOR EACH ROW
EXECUTE FUNCTION military_units_view_delete();

CREATE OR REPLACE TRIGGER military_units_view_update_trigger
    INSTEAD OF UPDATE
    ON military_units_view
    FOR EACH ROW
EXECUTE FUNCTION military_units_view_update();
