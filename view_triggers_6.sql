create view tanks_view(id, name, ammo) as
SELECT ar.id,
       transport.name,
       ar.ammo
FROM transport
         JOIN tanks ar ON transport.id = ar.id;


CREATE OR REPLACE FUNCTION tanks_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into transport(type, name) VALUES (1, NEW.name) RETURNING id INTO insert_id;
    Insert Into tanks VALUES (insert_id, NEW.ammo);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION tanks_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM tanks WHERE id = OLD.id;
    DELETE FROM transport WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION tanks_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE tanks SET ammo = NEW.ammo WHERE id = NEW.id;
    UPDATE transport SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER tanks_view_insert_trigger
    INSTEAD OF INSERT
    ON tanks_view
    FOR EACH ROW
EXECUTE FUNCTION tanks_view_insert();

CREATE OR REPLACE TRIGGER tanks_view_delete_trigger
    INSTEAD OF DELETE
    ON tanks_view
    FOR EACH ROW
EXECUTE FUNCTION tanks_view_delete();

CREATE OR REPLACE TRIGGER tanks_view_update_trigger
    INSTEAD OF UPDATE
    ON tanks_view
    FOR EACH ROW
EXECUTE FUNCTION tanks_view_update();
