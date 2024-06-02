create OR REPLACE view under_army_view(id, name, part_of) as
SELECT ms.id,
        ms.name,
        ms.part_of
FROM military_subdivisions ms WHERE type = 2 OR type = 3 OR type = 4;

create OR REPLACE view brigade_view(id, name, part_of) as
SELECT ms.id,
        ms.name,
        ms.part_of
FROM military_subdivisions ms WHERE type = 2;

CREATE OR REPLACE FUNCTION brigade_view_insert() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 2, NEW.part_of);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION brigade_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION brigade_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER brigade_view_insert_trigger
    INSTEAD OF INSERT
    ON brigade_view
    FOR EACH ROW
EXECUTE FUNCTION brigade_view_insert();

CREATE OR REPLACE TRIGGER brigade_view_delete_trigger
    INSTEAD OF DELETE
    ON brigade_view
    FOR EACH ROW
EXECUTE FUNCTION brigade_view_delete();

CREATE OR REPLACE TRIGGER brigade_view_update_trigger
    INSTEAD OF UPDATE
    ON brigade_view
    FOR EACH ROW
EXECUTE FUNCTION brigade_view_update();






create OR REPLACE view corp_view(id, name, part_of) as
SELECT ms.id,
        ms.name,
        ms.part_of
FROM military_subdivisions ms WHERE type = 3;

CREATE OR REPLACE FUNCTION corp_view_insert() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 3, NEW.part_of);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION corp_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION corp_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER corp_view_insert_trigger
    INSTEAD OF INSERT
    ON corp_view
    FOR EACH ROW
EXECUTE FUNCTION corp_view_insert();

CREATE OR REPLACE TRIGGER corp_view_delete_trigger
    INSTEAD OF DELETE
    ON corp_view
    FOR EACH ROW
EXECUTE FUNCTION corp_view_delete();

CREATE OR REPLACE TRIGGER corp_view_update_trigger
    INSTEAD OF UPDATE
    ON corp_view
    FOR EACH ROW
EXECUTE FUNCTION corp_view_update();






create OR REPLACE view division_view(id, name, part_of) as
SELECT ms.id,
        ms.name,
        ms.part_of
FROM military_subdivisions ms WHERE type = 4;

CREATE OR REPLACE FUNCTION division_view_insert() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 4, NEW.part_of);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION division_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION division_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER division_view_insert_trigger
    INSTEAD OF INSERT
    ON division_view
    FOR EACH ROW
EXECUTE FUNCTION division_view_insert();

CREATE OR REPLACE TRIGGER division_view_delete_trigger
    INSTEAD OF DELETE
    ON division_view
    FOR EACH ROW
EXECUTE FUNCTION division_view_delete();

CREATE OR REPLACE TRIGGER division_view_update_trigger
    INSTEAD OF UPDATE
    ON division_view
    FOR EACH ROW
EXECUTE FUNCTION division_view_update();


