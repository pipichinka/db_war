CREATE OR REPLACE FUNCTION transport_consistency() RETURNS TRIGGER AS
$$
DECLARE
    type_check bigint;
    real_type bigint;
BEGIN
    type_check := TG_ARGV[0];
    SELECT type INTO real_type from transport WHERE id = NEW.id;

    IF NEW IS NOT NULL THEN
        IF  real_type IS NULL OR real_type != type_check THEN
            RAISE EXCEPTION 'expected type % for this table', (SELECT name FROM transport_types WHERE id = type_check);
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER infantry_combat_vehicles_insert_trigger
    BEFORE INSERT
    ON infantry_combat_vehicles
    FOR EACH ROW
EXECUTE FUNCTION transport_consistency(1);

CREATE OR REPLACE TRIGGER tanks_insert_trigger
    BEFORE INSERT
    ON tanks
    FOR EACH ROW
EXECUTE FUNCTION transport_consistency(2);

CREATE OR REPLACE TRIGGER tractors_insert_trigger
    BEFORE INSERT
    ON tractors
    FOR EACH ROW
EXECUTE FUNCTION transport_consistency(3);

CREATE OR REPLACE TRIGGER vehicles_insert_trigger
    BEFORE INSERT
    ON vehicles
    FOR EACH ROW
EXECUTE FUNCTION transport_consistency(4);