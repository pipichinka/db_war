create view colonels_view(id, name, work, head, pet) as
SELECT ar.id,
       employees.name,
       employees.work,
       employees.head, 
       ar.pet
FROM employees
         JOIN colonels ar ON employees.id = ar.id;


CREATE OR REPLACE FUNCTION colonels_view_insert() RETURNS TRIGGER AS
$$
DECLARE
    insert_id bigint;
BEGIN
    Insert Into employees(rank, name, work, head) VALUES (2, NEW.name, NEW.work, NEW.head) RETURNING id INTO insert_id;
    Insert Into colonels VALUES (insert_id, NEW.pet);
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION colonels_view_delete() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    DELETE FROM colonels WHERE id = OLD.id;
    DELETE FROM employees WHERE id = OLD.id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION colonels_view_update() RETURNS TRIGGER AS
$$
DECLARE
BEGIN
    if OLD.id != NEW.id THEN
        RAISE EXCEPTION 'you cannot update id in this table';
    end if;
    UPDATE colonels SET pet = NEW.pet WHERE id = NEW.id;
    UPDATE employees SET name = NEW.name, head = NEW.head, work = NEW.work WHERE id = NEW.id;
    return NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER colonels_view_insert_trigger
    INSTEAD OF INSERT
    ON colonels_view
    FOR EACH ROW
EXECUTE FUNCTION colonels_view_insert();

CREATE OR REPLACE TRIGGER colonels_view_delete_trigger
    INSTEAD OF DELETE
    ON colonels_view
    FOR EACH ROW
EXECUTE FUNCTION colonels_view_delete();

CREATE OR REPLACE TRIGGER colonels_view_update_trigger
    INSTEAD OF UPDATE
    ON colonels_view
    FOR EACH ROW
EXECUTE FUNCTION colonels_view_update();
