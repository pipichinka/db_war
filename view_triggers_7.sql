create view tractors_view(id, name, thrust_force) as
SELECT ar.id,
       transport.name,
       ar.thrust_force
FROM transport
         JOIN tractors ar ON transport.id = ar.id;


CREATE OR REPLACE FUNCTION tractors_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into transport(type, name) VALUES (3, NEW.name) RETURNING id INTO insert_id;
    Insert Into tractors VALUES (insert_id, NEW.thrust_force);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION tractors_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM tractors WHERE id = OLD.id;
    DELETE FROM transport WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION tractors_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE tractors SET thrust_force = NEW.thrust_force WHERE id = NEW.id;
    UPDATE transport SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER tractors_view_insert_trigger
    INSTEAD OF INSERT
    ON tractors_view
    FOR EACH ROW
EXECUTE FUNCTION tractors_view_insert();

CREATE OR REPLACE TRIGGER tractors_view_delete_trigger
    INSTEAD OF DELETE
    ON tractors_view
    FOR EACH ROW
EXECUTE FUNCTION tractors_view_delete();

CREATE OR REPLACE TRIGGER tractors_view_update_trigger
    INSTEAD OF UPDATE
    ON tractors_view
    FOR EACH ROW
EXECUTE FUNCTION tractors_view_update();
