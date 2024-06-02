create view assault_rifles_view(id, name, ammo, fire_rate) as
SELECT ar.id,
       weapons.name,
       ar.ammo,
       ar.fire_rate
FROM weapons
         JOIN assault_rifles ar ON weapons.id = ar.id;


CREATE OR REPLACE FUNCTION assault_rifles_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into weapons(type) VALUES (2, NEW.name) RETURNING id INTO insert_id;
    Insert Into assault_rifles VALUES (insert_id, NEW.fire_rate, NEW.ammo);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION assault_rifles_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM assault_rifles WHERE id = OLD.id;
    DELETE FROM weapons WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION assault_rifles_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE assault_rifles SET fire_rate = NEW.fire_rate, ammo = NEW.ammo WHERE id = NEW.id;
    UPDATE weapons SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER assault_rifles_view_insert_trigger
    INSTEAD OF INSERT
    ON assault_rifles_view
    FOR EACH ROW
EXECUTE FUNCTION assault_rifles_view_insert();

CREATE OR REPLACE TRIGGER assault_rifles_view_delete_trigger
    INSTEAD OF DELETE
    ON assault_rifles_view
    FOR EACH ROW
EXECUTE FUNCTION assault_rifles_view_delete();

CREATE OR REPLACE TRIGGER assault_rifles_view_update_trigger
    INSTEAD OF UPDATE
    ON assault_rifles_view
    FOR EACH ROW
EXECUTE FUNCTION assault_rifles_view_update();
