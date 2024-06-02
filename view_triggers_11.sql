create view lieutenant_colonels_view(id, name, work, head, height) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.height
FROM employees
         JOIN lieutenant_colonels ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION lieutenant_colonels_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(type, name, work, head) VALUES (3, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into lieutenant_colonels VALUES (insert_id, NEW.height);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION lieutenant_colonels_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM lieutenant_colonels WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION lieutenant_colonels_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE lieutenant_colonels SET height = NEW.height WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER lieutenant_colonels_view_insert_trigger
    INSTEAD OF INSERT
    ON lieutenant_colonels_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenant_colonels_view_insert();

CREATE OR REPLACE TRIGGER lieutenant_colonels_view_delete_trigger
    INSTEAD OF DELETE
    ON lieutenant_colonels_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenant_colonels_view_delete();

CREATE OR REPLACE TRIGGER lieutenant_colonels_view_update_trigger
    INSTEAD OF UPDATE
    ON lieutenant_colonels_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenant_colonels_view_update();
