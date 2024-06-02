create view generals_view(id, name, work, head, hire_date) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.hire_date
FROM employees
         JOIN generals ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION generals_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (1, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into generals VALUES (insert_id, NEW.hire_date);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION generals_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM generals WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION generals_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE generals SET hire_date = NEW.hire_date WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER generals_view_insert_trigger
    INSTEAD OF INSERT
    ON generals_view
    FOR EACH ROW
EXECUTE FUNCTION generals_view_insert();

CREATE OR REPLACE TRIGGER generals_view_delete_trigger
    INSTEAD OF DELETE
    ON generals_view
    FOR EACH ROW
EXECUTE FUNCTION generals_view_delete();

CREATE OR REPLACE TRIGGER generals_view_update_trigger
    INSTEAD OF UPDATE
    ON generals_view
    FOR EACH ROW
EXECUTE FUNCTION generals_view_update();
