INSERT INTO "weapons"("type")
VALUES(1),
 (1),
 (2),
 (2),
 (3),
 (3),
 (4),
 (4);

INSERT INTO "assault_rifles" ("id", "name", "fire_rate", "ammo")
 VALUES(3, 'ak47', 600, '7,62 mm'),
 (4, 'ak74', 650, '5,45 mm');

INSERT INTO "rifles" ("id", "name", "fire_rate", "ammo")
 VALUES(1, 'SVD', 30, '7,62 mm'),
 (2, 'Mosin Nagant', 10, '7,62 mm');

INSERT INTO "artilleries"("id", "name", "ammo", "squad_size")
 VALUES(5,'M-13', '132 mm', 2),
 (6, '2C40', '120 mm', 4);

INSERT INTO "missile_weapons"("id", "name", "ammo", "weight")
 VALUES(7, 'Iskander-M', 'quasi-ballistic missiles', 4.6),
 (8, 'S-400', 'surface-to-air missiles', 35);



INSERT INTO "transport"("type")
 VALUES(1),
 (1),
 (1),
 (2),
 (2),
 (2),
 (3),
 (3),
 (3),
 (4),
 (4),
 (4);

INSERT INTO "infantry_combat_vehicles" ("id", "name", "capacity")
 VALUES(1, 'BMP-3', 7),
 (2, 'T-15', 9),
 (3, 'Kurganets-25', 13);

INSERT INTO "tanks" ("id", "name", "ammo")
 VALUES(4, 'T-14 Armata', '125mm smoothbore gun'),
 (5, 'T-90M Proryv', '125mm smoothbore gun'),
 (6, 'T-80BVM', '125mm smoothbore gun');

INSERT INTO "tractors" ("id", "name", "thrust_force")
 VALUES(7, 'MT-LB', 600),
 (8, 'MZKT-7930', 1000),
 (9, 'KAMAZ-6560', 800);

INSERT INTO "vehicles" ("id", "name", "avarage_speed")
VALUES (10, 'Ural-4320', 80),
 (11, 'Kamaz-5350', 90),
 (12, 'GAZ-2330 Tiger', 100);



INSERT INTO "military_region"("name")
 VALUES('Novosibirsk'),
 ('Moscow');

INSERT INTO "places"("name", "region_id")
 VALUES('place 1', 1),
 ('place 2', 1),
 ('place 3', 1),
 ('place 4', 2),
 ('place 5', 2),
 ('place 6', 2);

INSERT INTO "military_specializations"("name")
 VALUES('infantryman'),
('paratrooper'),
 ('special forces operator'),
 ('navy SEAL'),
 ('parine'),
 ('air force pilot');