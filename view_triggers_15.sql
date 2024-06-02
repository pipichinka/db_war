create view sergeantmajors_view(id, name, work, head, selary) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.selary
FROM employees
         JOIN sergeantmajors ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION sergeantmajors_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (7, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into sergeantmajors VALUES (insert_id, NEW.selary);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION sergeantmajors_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM sergeantmajors WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION sergeantmajors_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE sergeantmajors SET selary = NEW.selary WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER sergeantmajors_view_insert_trigger
    INSTEAD OF INSERT
    ON sergeantmajors_view
    FOR EACH ROW
EXECUTE FUNCTION sergeantmajors_view_insert();

CREATE OR REPLACE TRIGGER sergeantmajors_view_delete_trigger
    INSTEAD OF DELETE
    ON sergeantmajors_view
    FOR EACH ROW
EXECUTE FUNCTION sergeantmajors_view_delete();

CREATE OR REPLACE TRIGGER sergeantmajors_view_update_trigger
    INSTEAD OF UPDATE
    ON sergeantmajors_view
    FOR EACH ROW
EXECUTE FUNCTION sergeantmajors_view_update();
