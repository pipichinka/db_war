create view soldiers_view(id, name, work, head, birth_date) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.birth_date
FROM employees
         JOIN soldiers ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION soldiers_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(type, name, work, head) VALUES (11, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into soldiers VALUES (insert_id, NEW.birth_date);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION soldiers_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM soldiers WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION soldiers_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE soldiers SET birth_date = NEW.birth_date WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER soldiers_view_insert_trigger
    INSTEAD OF INSERT
    ON soldiers_view
    FOR EACH ROW
EXECUTE FUNCTION soldiers_view_insert();

CREATE OR REPLACE TRIGGER soldiers_view_delete_trigger
    INSTEAD OF DELETE
    ON soldiers_view
    FOR EACH ROW
EXECUTE FUNCTION soldiers_view_delete();

CREATE OR REPLACE TRIGGER soldiers_view_update_trigger
    INSTEAD OF UPDATE
    ON soldiers_view
    FOR EACH ROW
EXECUTE FUNCTION soldiers_view_update();
