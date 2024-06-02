create view infantry_combat_vehicles_view(id, name, capacity) as
SELECT ar.id,
       transport.name,
       ar.capacity
FROM transport
         JOIN infantry_combat_vehicles ar ON transport.id = ar.id;


CREATE OR REPLACE FUNCTION infantry_combat_vehicles_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into transport(type, name) VALUES (1, NEW.name) RETURNING id INTO insert_id;
    Insert Into infantry_combat_vehicles VALUES (insert_id, NEW.capacity);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION infantry_combat_vehicles_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM infantry_combat_vehicles WHERE id = OLD.id;
    DELETE FROM transport WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION infantry_combat_vehicles_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE infantry_combat_vehicles SET capacity = NEW.capacity WHERE id = NEW.id;
    UPDATE transport SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER infantry_combat_vehicles_view_insert_trigger
    INSTEAD OF INSERT
    ON infantry_combat_vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION infantry_combat_vehicles_view_insert();

CREATE OR REPLACE TRIGGER infantry_combat_vehicles_view_delete_trigger
    INSTEAD OF DELETE
    ON infantry_combat_vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION infantry_combat_vehicles_view_delete();

CREATE OR REPLACE TRIGGER infantry_combat_vehicles_view_update_trigger
    INSTEAD OF UPDATE
    ON infantry_combat_vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION infantry_combat_vehicles_view_update();
