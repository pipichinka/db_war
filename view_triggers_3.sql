create view artilleries_view(id, name, ammo, squad_size) as
SELECT ar.id,
       weapons.name,
       ar.ammo,
       ar.squad_size
FROM weapons
         JOIN artilleries ar ON weapons.id = ar.id;


CREATE OR REPLACE FUNCTION artilleries_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into weapons(type, name) VALUES (3, NEW.name) RETURNING id INTO insert_id;
    Insert Into artilleries VALUES (insert_id, NEW.ammo, NEW.squad_size);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION artilleries_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM artilleries WHERE id = OLD.id;
    DELETE FROM weapons WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION artilleries_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE artilleries SET squad_size = NEW.squad_size, ammo = NEW.ammo WHERE id = NEW.id;
    UPDATE weapons SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER artillery_view_insert_trigger
    INSTEAD OF INSERT
    ON artilleries_view
    FOR EACH ROW
EXECUTE FUNCTION artilleries_view_insert();

CREATE OR REPLACE TRIGGER artillery_view_delete_trigger
    INSTEAD OF DELETE
    ON artilleries_view
    FOR EACH ROW
EXECUTE FUNCTION artilleries_view_delete();

CREATE OR REPLACE TRIGGER artillery_view_update_trigger
    INSTEAD OF UPDATE
    ON artilleries_view
    FOR EACH ROW
EXECUTE FUNCTION artilleries_view_update();
