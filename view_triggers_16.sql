create view sergeants_view(id, name, work, head, weight) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.weight
FROM employees
         JOIN sergeants ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION sergeants_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (8, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into sergeants VALUES (insert_id, NEW.weight);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION sergeants_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM sergeants WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION sergeants_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE sergeants SET weight = NEW.weight WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER sergeants_view_insert_trigger
    INSTEAD OF INSERT
    ON sergeants_view
    FOR EACH ROW
EXECUTE FUNCTION sergeants_view_insert();

CREATE OR REPLACE TRIGGER sergeants_view_delete_trigger
    INSTEAD OF DELETE
    ON sergeants_view
    FOR EACH ROW
EXECUTE FUNCTION sergeants_view_delete();

CREATE OR REPLACE TRIGGER sergeants_view_update_trigger
    INSTEAD OF UPDATE
    ON sergeants_view
    FOR EACH ROW
EXECUTE FUNCTION sergeants_view_update();
