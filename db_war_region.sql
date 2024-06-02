CREATE TABLE IF NOT EXISTS "places" (
	"id" bigserial,
	"name" text NOT NULL,
	"region_id" bigint NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "military_subdivisions" (
	"id" bigserial,
	"name" text NOT NULL,
	"type" bigint NOT NULL,
	"part_of" bigint ,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "subdivision_ranks" (
	"id" bigserial,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

INSERT INTO "subdivision_ranks" ("name")
VALUES('army'),
('brigade'),
('corp'),
('division'),
('unit'),
('company'),
('platoon'),
('squad');

CREATE TABLE IF NOT EXISTS "employees" (
	"id" bigserial,
	"rank" bigint NOT NULL,
	"work" bigint NOT NULL,
	"name" text NOT NULL,
	"head" bigint,
	PRIMARY KEY ("id")
);


CREATE TABLE IF NOT EXISTS "employee_ranks" (
	"id" bigserial,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

INSERT INTO "employee_ranks"("name")
VALUES('general'), 
('colonel'), 
('lieutenant colonel'), 
('major'), 
('captain'),  
('lieutenant'), 
('sergeantmajor'),  
('sergeant'), 
('ensign'),  
('corporal'), 
('soldier'); 

CREATE TABLE IF NOT EXISTS "generals" (
	"id" bigint NOT NULL,
	"hire_date" date NOT NULL CHECK("hire_date" <= CURRENT_DATE),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "colonels" (
	"id" bigint NOT NULL,
	"pet" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "lieutenant_colonels" (
	"id" bigint NOT NULL,
	"height" integer NOT NULL CHECK("height" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "majors" (
	"id" bigint NOT NULL,
	"weight" integer NOT NULL CHECK("weight" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "captains" (
	"id" bigint NOT NULL,
	"hire_date" date NOT NULL CHECK("hire_date" <= CURRENT_DATE),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "lieutenants" (
	"id" bigint NOT NULL,
	"pet" text NOT NULL,
	PRIMARY KEY ("id")
);



CREATE TABLE IF NOT EXISTS "sergeantmajors" (
	"id" bigint NOT NULL,
	"selary" integer NOT NULL CHECK("selary" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "sergeants" (
	"id" bigint NOT NULL,
	"weight" integer NOT NULL CHECK("weight" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "ensigns"(
	"id" bigint NOT NULL,
	"hire_date" date NOT NULL CHECK("hire_date" <= CURRENT_DATE),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "corporals" (
	"id" bigint NOT NULL,
	"height" integer NOT NULL CHECK(height > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "soldiers" (
	"id" bigint NOT NULL,
	"birth_date" date NOT NULL,
	PRIMARY KEY ("id")
);


CREATE TABLE IF NOT EXISTS "military_specializations" (
	"id" bigserial,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "employees_specializations" (
	"employee_id" bigint NOT NULL,
	"spec_id" bigint NOT NULL,
	PRIMARY KEY("employee_id", "spec_id")
);

CREATE TABLE IF NOT EXISTS "military_unit" (
	"id" bigint NOT NULL UNIQUE,
	"place_id" bigint NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "military_region" (
	"name" text NOT NULL,
	"id" bigserial,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "transport_types"(
	"id" bigserial,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

INSERT INTO "transport_types"("name")
VALUES('infantry combat vehicle'),
('tank'),
('tractor'),
('vehicle');

CREATE TABLE IF NOT EXISTS "infantry_combat_vehicles"(
	"id" bigint NOT NULL,
	"capacity" integer NOT NULL CHECK("capacity" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "tanks"(
	"id" bigint NOT NULL,
	"ammo" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "tractors"(
	"id" bigint NOT NULL,
	"thrust_force" integer NOT NULL CHECK("thrust_force" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "vehicles"(
	"id" bigint NOT NULL,
	"avarage_speed" integer NOT NULL CHECK("avarage_speed" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "transport"(
	"id" bigserial,
	"type" bigint NOT NULL,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "unit_transport"(
	"unit_id" bigint NOT NULL,
	"transport_id" bigint NOT NULL,
	"amount" integer NOT NULL CHECK("amount" > 0),
	PRIMARY KEY("unit_id", "transport_id")
);

CREATE TABLE IF NOT EXISTS "weapon_types"(
	"id" bigserial,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

INSERT INTO "weapon_types"("name")
VALUES('rifle'),
('assault rifle'),
('artillery'),
('missile weapons');

CREATE TABLE IF NOT EXISTS "rifles"(
	"id" bigint NOT NULL,
	"fire_rate" integer NOT NULL CHECK("fire_rate" > 0),
	"ammo" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "assault_rifles"(
	"id" bigint NOT NULL,
	"fire_rate" integer NOT NULL CHECK("fire_rate" > 0),
	"ammo" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "artilleries"(
	"id" bigint NOT NULL,
	"ammo" text NOT NULL,
	"squad_size" integer NOT NULL CHECK ("squad_size" > 0),
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "missile_weapons"(
	"id" bigint NOT NULL,
	"ammo" text NOT NULL,
	"weight" integer NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "weapons"(
	"id" bigserial,
	"type" bigint NOT NULL,
	"name" text NOT NULL,
	PRIMARY KEY ("id")
);

CREATE TABLE IF NOT EXISTS "unit_weapons"(
	"unit_id" bigint NOT NULL,
	"weapon_id" bigint NOT NULL,
	"amount" integer NOT NULL CHECK("amount" > 0),
	PRIMARY KEY("unit_id", "weapon_id")
);

CREATE TABLE IF NOT EXISTS "unit_constructions"(
	"id"  bigserial,
	"name" text NOT NULL,
	"dislocation" boolean NOT NULL,
	"unit_id" bigint NOT NULL,
	PRIMARY KEY("id")
); 

CREATE TABLE IF NOT EXISTS "subdivision_dislocation"(
	"subdivision_id" bigint NOT NULL,
	"construction_id" bigint NOT NULL,
	PRIMARY KEY ("subdivision_id", "construction_id")
);


ALTER TABLE "unit_constructions" ADD CONSTRAINT "unit_constructions_fk1" FOREIGN KEY ("unit_id") REFERENCES "military_unit"("id");
ALTER TABLE "subdivision_dislocation" ADD CONSTRAINT "subdivision_dislocation_fk1" FOREIGN KEY ("construction_id") REFERENCES "unit_constructions"("id");
ALTER TABLE "subdivision_dislocation" ADD CONSTRAINT "subdivision_dislocation_fk2" FOREIGN KEY ("subdivision_id") REFERENCES "military_subdivisions"("id");

ALTER TABLE "unit_weapons" ADD CONSTRAINT "unit_weapon_fk1" FOREIGN KEY ("weapon_id") REFERENCES "weapons"("id");
ALTER TABLE "unit_weapons" ADD CONSTRAINT "unit_weapon_fk2" FOREIGN KEY ("unit_id") REFERENCES "military_unit"("id");
ALTER TABLE "weapons" ADD CONSTRAINT "weapon_fk1" FOREIGN KEY ("type") REFERENCES "weapon_types"("id");

ALTER TABLE "unit_transport" ADD CONSTRAINT "unit_transport_fk1" FOREIGN KEY ("transport_id") REFERENCES "transport"("id");
ALTER TABLE "unit_transport" ADD CONSTRAINT "unit_transport_fk2" FOREIGN KEY ("unit_id") REFERENCES "military_unit"("id");
ALTER TABLE "transport" ADD CONSTRAINT "transport_fk1" FOREIGN KEY ("type") REFERENCES "transport_types"("id");


ALTER TABLE "military_subdivisions" ADD CONSTRAINT "military_subdivisions_fk2" FOREIGN KEY ("type") REFERENCES "subdivision_ranks"("id");

ALTER TABLE "military_subdivisions" ADD CONSTRAINT "military_subdivisions_fk3" FOREIGN KEY ("part_of") REFERENCES "military_subdivisions"("id");

ALTER TABLE "employees" ADD CONSTRAINT "employees_fk1" FOREIGN KEY ("rank") REFERENCES "employee_ranks"("id");

ALTER TABLE "employees" ADD CONSTRAINT "employees_fk2" FOREIGN KEY ("work") REFERENCES "military_subdivisions"("id");

ALTER TABLE "employees" ADD CONSTRAINT "employees_fk3" FOREIGN KEY ("head") REFERENCES "military_subdivisions"("id");

ALTER TABLE "generals" ADD CONSTRAINT "generals_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "colonels" ADD CONSTRAINT "colonels_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "lieutenant_colonels" ADD CONSTRAINT "lieutenant colonels_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "majors" ADD CONSTRAINT "majors_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "captains" ADD CONSTRAINT "captains_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "lieutenants" ADD CONSTRAINT "lieutenants_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "sergeantmajors" ADD CONSTRAINT "sergeantmajors_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "sergeants" ADD CONSTRAINT "sergeants_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "corporals" ADD CONSTRAINT "corporals_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "soldiers" ADD CONSTRAINT "soldiers_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");
ALTER TABLE "ensigns" ADD CONSTRAINT "ensigns_fk0" FOREIGN KEY ("id") REFERENCES "employees"("id");

ALTER TABLE "infantry_combat_vehicles" ADD CONSTRAINT "infantry combat vehicles_fk0" FOREIGN KEY ("id") REFERENCES "transport"("id");
ALTER TABLE "tanks" ADD CONSTRAINT "tanks_fk0" FOREIGN KEY ("id") REFERENCES "transport"("id");
ALTER TABLE "tractors" ADD CONSTRAINT "tractors_fk0" FOREIGN KEY ("id") REFERENCES "transport"("id");
ALTER TABLE "vehicles" ADD CONSTRAINT "vehicles_fk0" FOREIGN KEY ("id") REFERENCES "transport"("id");


ALTER TABLE "rifles" ADD CONSTRAINT "rifles_fk0" FOREIGN KEY ("id") REFERENCES "weapons"("id");
ALTER TABLE "assault_rifles" ADD CONSTRAINT "assault rifles_fk0" FOREIGN KEY ("id") REFERENCES "weapons"("id");
ALTER TABLE "artilleries" ADD CONSTRAINT "artilleries_fk0" FOREIGN KEY ("id") REFERENCES "weapons"("id");
ALTER TABLE "missile_weapons" ADD CONSTRAINT "missile_weapons_fk0" FOREIGN KEY ("id") REFERENCES "weapons"("id");


ALTER TABLE "employees_specializations" ADD CONSTRAINT "employees_specializations_fk0" FOREIGN KEY ("employee_id") REFERENCES "employees"("id");

ALTER TABLE "employees_specializations" ADD CONSTRAINT "employees_specializations_fk1" FOREIGN KEY ("spec_id") REFERENCES "military_specializations"("id");
ALTER TABLE "military_unit" ADD CONSTRAINT "military_unit_fk0" FOREIGN KEY ("id") REFERENCES "military_subdivisions"("id");

ALTER TABLE "military_unit" ADD CONSTRAINT "military_unit_fk1" FOREIGN KEY ("place_id") REFERENCES "places"("id");

ALTER TABLE "places" ADD CONSTRAINT "places_fk0" FOREIGN KEY ("region_id") REFERENCES "military_region"("id");
