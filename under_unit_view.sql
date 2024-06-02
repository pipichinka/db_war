create OR REPLACE view company_view(id, name, part_of, construction_id) as
SELECT ms.id,
        ms.name,
        ms.part_of,
        sd.construction_id
FROM military_subdivisions ms LEFT JOIN subdivision_dislocation sd on sd.subdivision_id = ms.id WHERE type = 6;

CREATE OR REPLACE FUNCTION company_view_insert() RETURNS TRIGGER AS
$$
DECLARE
insert_id bigint;
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 6, NEW.part_of) RETURNING id INTO insert_id;
    IF (NEW.construction_id IS NOT NULL) THEN
        INSERT INTO subdivision_dislocation VALUES(insert_id, NEW.construction_id);
    end if;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION company_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM subdivision_dislocation WHERE subdivision_id = OLD.id;
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION company_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    UPDATE subdivision_dislocation SET construction_id = NEW.construction_id WHERE subdivision_id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER company_view_insert_trigger
    INSTEAD OF INSERT
    ON company_view
    FOR EACH ROW
EXECUTE FUNCTION company_view_insert();

CREATE OR REPLACE TRIGGER company_view_delete_trigger
    INSTEAD OF DELETE
    ON company_view
    FOR EACH ROW
EXECUTE FUNCTION company_view_delete();

CREATE OR REPLACE TRIGGER company_view_update_trigger
    INSTEAD OF UPDATE
    ON company_view
    FOR EACH ROW
EXECUTE FUNCTION company_view_update();





create OR REPLACE view platoon_view(id, name, part_of, construction_id) as
SELECT ms.id,
        ms.name,
        ms.part_of,
        sd.construction_id
FROM military_subdivisions ms LEFT JOIN subdivision_dislocation sd on sd.subdivision_id = ms.id WHERE type = 7;

CREATE OR REPLACE FUNCTION platoon_view_insert() RETURNS TRIGGER AS
$$
DECLARE
insert_id bigint;
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 7, NEW.part_of) RETURNING id INTO insert_id;
    IF (NEW.construction_id IS NOT NULL) THEN
        INSERT INTO subdivision_dislocation VALUES(insert_id, NEW.construction_id);
    end if;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION platoon_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM subdivision_dislocation WHERE subdivision_id = OLD.id;
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION platoon_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    UPDATE subdivision_dislocation SET construction_id = NEW.construction_id WHERE subdivision_id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER platoon_view_insert_trigger
    INSTEAD OF INSERT
    ON platoon_view
    FOR EACH ROW
EXECUTE FUNCTION platoon_view_insert();

CREATE OR REPLACE TRIGGER platoon_view_delete_trigger
    INSTEAD OF DELETE
    ON platoon_view
    FOR EACH ROW
EXECUTE FUNCTION platoon_view_delete();

CREATE OR REPLACE TRIGGER platoon_view_update_trigger
    INSTEAD OF UPDATE
    ON platoon_view
    FOR EACH ROW
EXECUTE FUNCTION platoon_view_update();





create OR REPLACE view squad_view(id, name, part_of, construction_id) as
SELECT ms.id,
        ms.name,
        ms.part_of,
        sd.construction_id
FROM military_subdivisions ms LEFT JOIN subdivision_dislocation sd on sd.subdivision_id = ms.id WHERE type = 8;

CREATE OR REPLACE FUNCTION squad_view_insert() RETURNS TRIGGER AS
$$
DECLARE
insert_id bigint;
BEGIN
    Insert Into military_subdivisions(name, type, part_of) VALUES (NEW.name, 8, NEW.part_of) RETURNING id INTO insert_id;
    IF (NEW.construction_id IS NOT NULL) THEN
        INSERT INTO subdivision_dislocation VALUES(insert_id, NEW.construction_id);
    end if;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION squad_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM subdivision_dislocation WHERE subdivision_id = OLD.id;
    DELETE FROM military_subdivisions WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION squad_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE military_subdivisions SET name = NEW.name, part_of = NEW.part_of WHERE id = NEW.id;
    UPDATE subdivision_dislocation SET construction_id = NEW.construction_id WHERE subdivision_id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER squad_view_insert_trigger
    INSTEAD OF INSERT
    ON squad_view
    FOR EACH ROW
EXECUTE FUNCTION squad_view_insert();

CREATE OR REPLACE TRIGGER squad_view_delete_trigger
    INSTEAD OF DELETE
    ON squad_view
    FOR EACH ROW
EXECUTE FUNCTION squad_view_delete();

CREATE OR REPLACE TRIGGER squad_view_update_trigger
    INSTEAD OF UPDATE
    ON squad_view
    FOR EACH ROW
EXECUTE FUNCTION squad_view_update();