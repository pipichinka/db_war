CREATE OR REPLACE FUNCTION employee_head_consistency() RETURNS TRIGGER AS
$$
DECLARE
    head_type bigint;
BEGIN
    IF NEW.head IS NOT NULL THEN
        SELECT type INTO head_type FROM military_subdivisions WHERE id = NEW.head;
        IF (NEW.rank > 6 AND head_type > 7) THEN
            RAISE EXCEPTION 'employees with ranks less than lieutenant can manage only squads and platoons';
        end if;
    end if;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER employee_head_update_trigger
    BEFORE UPDATE
    ON employees
    FOR EACH ROW
EXECUTE FUNCTION employee_head_consistency();

CREATE OR REPLACE TRIGGER employee_head_insert_trigger
    BEFORE INSERT
    ON employees
    FOR EACH ROW
EXECUTE FUNCTION employee_head_consistency();