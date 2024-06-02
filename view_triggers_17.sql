create view ensigns_view(id, name, work, head, hire_date) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.hire_date
FROM employees
         JOIN ensigns ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION ensigns_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (9, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into ensigns VALUES (insert_id, NEW.hire_date);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION ensigns_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM ensigns WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION ensigns_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE ensigns SET hire_date = NEW.hire_date WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER ensigns_view_insert_trigger
    INSTEAD OF INSERT
    ON ensigns_view
    FOR EACH ROW
EXECUTE FUNCTION ensigns_view_insert();

CREATE OR REPLACE TRIGGER ensigns_view_delete_trigger
    INSTEAD OF DELETE
    ON ensigns_view
    FOR EACH ROW
EXECUTE FUNCTION ensigns_view_delete();

CREATE OR REPLACE TRIGGER ensigns_view_update_trigger
    INSTEAD OF UPDATE
    ON ensigns_view
    FOR EACH ROW
EXECUTE FUNCTION ensigns_view_update();
