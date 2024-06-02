create view lieutenants_view(id, name, work, head, pet) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.pet
FROM employees
         JOIN lieutenants ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION lieutenants_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (6, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into lieutenants VALUES (insert_id, NEW.pet);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION lieutenants_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM lieutenants WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION lieutenants_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE lieutenants SET pet = NEW.pet WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER lieutenants_view_insert_trigger
    INSTEAD OF INSERT
    ON lieutenants_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenants_view_insert();

CREATE OR REPLACE TRIGGER lieutenants_view_delete_trigger
    INSTEAD OF DELETE
    ON lieutenants_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenants_view_delete();

CREATE OR REPLACE TRIGGER lieutenants_view_update_trigger
    INSTEAD OF UPDATE
    ON lieutenants_view
    FOR EACH ROW
EXECUTE FUNCTION lieutenants_view_update();
