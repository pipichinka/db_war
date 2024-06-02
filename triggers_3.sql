CREATE OR REPLACE FUNCTION weapon_consistency() RETURNS TRIGGER AS
$$
DECLARE
    type_check bigint;
    real_type bigint;
BEGIN
    type_check := TG_ARGV[0];
    SELECT type INTO real_type from weapons WHERE id = NEW.id;

    IF NEW IS NOT NULL THEN
        IF  real_type IS NULL OR real_type != type_check THEN
            RAISE EXCEPTION 'expected type % for this table', (SELECT name FROM weapon_types WHERE id = type_check);
        END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE TRIGGER assault_rifles_update_trigger
    BEFORE UPDATE
    ON assault_rifles
    FOR EACH ROW
EXECUTE FUNCTION weapon_consistency(2);

CREATE OR REPLACE TRIGGER rifles_update_trigger
    BEFORE UPDATE
    ON rifles
    FOR EACH ROW
EXECUTE FUNCTION weapon_consistency(1);


CREATE OR REPLACE TRIGGER artilleries_update_trigger
    BEFORE UPDATE
    ON artilleries
    FOR EACH ROW
EXECUTE FUNCTION weapon_consistency(3);


CREATE OR REPLACE TRIGGER missile_weapons_update_trigger
    BEFORE UPDATE
    ON missile_weapons
    FOR EACH ROW
EXECUTE FUNCTION weapon_consistency(4);