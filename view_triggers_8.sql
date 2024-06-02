create view vehicles_view(id, name, avarage_speed) as
SELECT ar.id,
       transport.name,
       ar.avarage_speed
FROM transport
         JOIN vehicles ar ON transport.id = ar.id;


CREATE OR REPLACE FUNCTION vehicles_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into transport(type, name) VALUES (4, NEW.name) RETURNING id INTO insert_id;
    Insert Into vehicles VALUES (insert_id, NEW.avarage_speed);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION vehicles_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM vehicles WHERE id = OLD.id;
    DELETE FROM transport WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION vehicles_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE vehicles SET avarage_speed = NEW.avarage_speed WHERE id = NEW.id;
    UPDATE transport SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER vehicles_view_insert_trigger
    INSTEAD OF INSERT
    ON vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION vehicles_view_insert();

CREATE OR REPLACE TRIGGER vehicles_view_delete_trigger
    INSTEAD OF DELETE
    ON vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION vehicles_view_delete();

CREATE OR REPLACE TRIGGER vehicles_view_update_trigger
    INSTEAD OF UPDATE
    ON vehicles_view
    FOR EACH ROW
EXECUTE FUNCTION vehicles_view_update();
