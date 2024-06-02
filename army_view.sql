create OR REPLACE view army_view(id, name) as
SELECT ms.id,
        ms.name
FROM military_subdivisions ms WHERE type = 1;

CREATE OR REPLACE FUNCTION army_view_insert() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    Insert Into military_subdivisions(name, type) VALUES (NEW.name, 1);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION army_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION army_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER army_view_insert_trigger
    INSTEAD OF INSERT
    ON army_view
    FOR EACH ROW
EXECUTE FUNCTION army_view_insert();

CREATE OR REPLACE TRIGGER army_view_delete_trigger
    INSTEAD OF DELETE
    ON army_view
    FOR EACH ROW
EXECUTE FUNCTION army_view_delete();

CREATE OR REPLACE TRIGGER army_view_update_trigger
    INSTEAD OF UPDATE
    ON army_view
    FOR EACH ROW
EXECUTE FUNCTION army_view_update();
