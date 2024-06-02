INSERT INTO "weapons"("type", "name")
VALUES(1, 'SVD'),
 (1, 'Mosin Nagant'),
 (2, 'ak47'),
 (2, 'ak74'),
 (3, 'M-13'),
 (3, '2C40'),
 (4, 'Iskander-M'),
 (4, 'S-400');

INSERT INTO "assault_rifles" ("id", "fire_rate", "ammo")
 VALUES(3 , 600, '7,62 mm'),
 (4 , 650, '5,45 mm');

INSERT INTO "rifles" ("id", "fire_rate", "ammo")
 VALUES(1, 30, '7,62 mm'),
 (2, 10, '7,62 mm');

INSERT INTO "artilleries"("id", "ammo", "squad_size")
 VALUES(5, '132 mm', 2),
 (6, '120 mm', 4);

INSERT INTO "missile_weapons"("id", "ammo", "weight")
 VALUES(7, 'quasi-ballistic missiles', 4.6),
 (8, 'surface-to-air missiles', 35);



INSERT INTO "transport"("type", "name")
 VALUES(1, 'BMP-3'),
 (1, 'T-15'),
 (1, 'Kurganets-25'),
 (2, 'T-14 Armata'),
 (2, 'T-90M Proryv'),
 (2, 'T-80BVM'),
 (3, 'MT-LB'),
 (3, 'MZKT-7930'),
 (3, 'KAMAZ-6560'),
 (4, 'Ural-4320'),
 (4, 'Kamaz-5350'),
 (4, 'GAZ-2330 Tiger');

INSERT INTO "infantry_combat_vehicles" ("id", "capacity")
 VALUES(1, 7),
 (2, 9),
 (3, 13);

INSERT INTO "tanks" ("id", "ammo")
 VALUES(4, '125mm smoothbore gun'),
 (5, '125mm smoothbore gun'),
 (6, '125mm smoothbore gun');

INSERT INTO "tractors" ("id", "thrust_force")
 VALUES(7, 600),
 (8, 1000),
 (9, 800);

INSERT INTO "vehicles" ("id", "avarage_speed")
VALUES (10, 80),
 (11, 90),
 (12, 100);



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