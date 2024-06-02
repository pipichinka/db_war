CREATE OR REPLACE FUNCTION dislocation_consistency() RETURNS TRIGGER AS
$$
DECLARE
    can_dislocate bigint;
BEGIN
    SELECT dislocation INTO can_dislocate from unit_constructions WHERE id = NEW.construction_id;

    IF NEW IS NOT NULL THEN
        IF  can_dislocate IS NULL OR NOT can_dislocate THEN
            RAISE EXCEPTION 'you cannot dislocate in this construction';
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER dislocation_insert_trigger
    BEFORE INSERT
    ON subdivision_dislocation
    FOR EACH ROW
EXECUTE FUNCTION dislocation_consistency();

CREATE OR REPLACE TRIGGER dislocation_update_trigger
    BEFORE UPDATE
    ON subdivision_dislocation
    FOR EACH ROW
EXECUTE FUNCTION dislocation_consistency();