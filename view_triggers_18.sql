create view corporals_view(id, name, work, head, height) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.height
FROM employees
         JOIN corporals ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION corporals_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (10, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into corporals VALUES (insert_id, NEW.height);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION corporals_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM corporals WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION corporals_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE corporals SET height = NEW.height WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER corporals_view_insert_trigger
    INSTEAD OF INSERT
    ON corporals_view
    FOR EACH ROW
EXECUTE FUNCTION corporals_view_insert();

CREATE OR REPLACE TRIGGER corporals_view_delete_trigger
    INSTEAD OF DELETE
    ON corporals_view
    FOR EACH ROW
EXECUTE FUNCTION corporals_view_delete();

CREATE OR REPLACE TRIGGER corporals_view_update_trigger
    INSTEAD OF UPDATE
    ON corporals_view
    FOR EACH ROW
EXECUTE FUNCTION corporals_view_update();
