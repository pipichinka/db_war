CREATE OR REPLACE FUNCTION employees_consistency() RETURNS TRIGGER AS
$$
DECLARE
    rank_check bigint;
    real_type bigint;
BEGIN
    rank_check := TG_ARGV[0];
    SELECT rank INTO real_type from employees WHERE id = NEW.id;

    IF NEW IS NOT NULL THEN
        IF  real_type IS NULL OR real_type != rank_check THEN
            RAISE EXCEPTION 'expected rank % for this table', (SELECT name FROM employee_ranks WHERE id = rank_check);
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER generals_insert_trigger
    BEFORE INSERT
    ON generals
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(1);

CREATE OR REPLACE TRIGGER colonels_insert_trigger
    BEFORE INSERT
    ON colonels
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(2);

CREATE OR REPLACE TRIGGER lieutenant_colonels_insert_trigger
    BEFORE INSERT
    ON lieutenant_colonels
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(3);

CREATE OR REPLACE TRIGGER majors_insert_trigger
    BEFORE INSERT
    ON majors
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(4);

CREATE OR REPLACE TRIGGER captains_insert_trigger
    BEFORE INSERT
    ON captains
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(5);

CREATE OR REPLACE TRIGGER lieutenants_insert_trigger
    BEFORE INSERT
    ON lieutenants
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(6);

CREATE OR REPLACE TRIGGER sergeantmajors_insert_trigger
    BEFORE INSERT
    ON sergeantmajors
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(7);

CREATE OR REPLACE TRIGGER sergeants_insert_trigger
    BEFORE INSERT
    ON sergeants
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(8);

CREATE OR REPLACE TRIGGER ensigns_insert_trigger
    BEFORE INSERT
    ON ensigns
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(9);

CREATE OR REPLACE TRIGGER corporals_insert_trigger
    BEFORE INSERT
    ON corporals
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(10);

CREATE OR REPLACE TRIGGER soldiers_insert_trigger
    BEFORE INSERT
    ON soldiers
    FOR EACH ROW
EXECUTE FUNCTION employees_consistency(11);