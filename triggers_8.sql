CREATE OR REPLACE FUNCTION subdivision_consistency() RETURNS TRIGGER AS
$$
DECLARE
    part_of_type bigint;
BEGIN
    IF NEW.part_of IS NOT NULL THEN
        SELECT type INTO part_of_type from military_subdivisions WHERE id = NEW.part_of;
        IF (part_of_type = 1 AND (NEW.type = 2 OR NEW.type = 3 OR NEW.type = 4)) THEN
            RETURN NEW;
        end if;
        IF ((part_of_type = 2 OR part_of_type = 3 OR part_of_type = 4) AND NEW.type = 5) THEN
            RETURN NEW;
        end if;
        IF part_of_type + 1 != NEW.type THEN
            RAISE EXCEPTION 'you cannot make % part of %.', (SELECT name from subdivision_ranks WHERE id = NEW.type),
                                                            (SELECT name from subdivision_ranks WHERE id = part_of_type);
        end if;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER subdivision_update_trigger
    BEFORE UPDATE
    ON military_subdivisions
    FOR EACH ROW
EXECUTE FUNCTION subdivision_consistency();

CREATE OR REPLACE TRIGGER subdivision_insert_trigger
    BEFORE INSERT
    ON military_subdivisions
    FOR EACH ROW
EXECUTE FUNCTION subdivision_consistency();