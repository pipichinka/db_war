create view missile_weapons_view(id, name, ammo, weight) as
SELECT ar.id,
       weapons.name,
       ar.ammo,
       ar.weight
FROM weapons
         JOIN missile_weapons ar ON weapons.id = ar.id;


CREATE OR REPLACE FUNCTION missile_weapons_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into weapons(type, name) VALUES (4, NEW.name) RETURNING id INTO insert_id;
    Insert Into missile_weapons VALUES (insert_id, NEW.ammo, NEW.weight);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION missile_weapons_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM missile_weapons WHERE id = OLD.id;
    DELETE FROM weapons WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION missile_weapons_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE missile_weapons SET weight = NEW.weight, ammo = NEW.ammo WHERE id = NEW.id;
    UPDATE weapons SET name = NEW.name WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER missile_weapons_insert_trigger
    INSTEAD OF INSERT
    ON missile_weapons_view
    FOR EACH ROW
EXECUTE FUNCTION missile_weapons_view_insert();

CREATE OR REPLACE TRIGGER missile_weapons_delete_trigger
    INSTEAD OF DELETE
    ON missile_weapons_view
    FOR EACH ROW
EXECUTE FUNCTION missile_weapons_view_delete();

CREATE OR REPLACE TRIGGER missile_weapons_update_trigger
    INSTEAD OF UPDATE
    ON missile_weapons_view
    FOR EACH ROW
EXECUTE FUNCTION missile_weapons_view_update();
