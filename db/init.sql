CREATE TABLE Gebruiker (
    gebruiker_id SERIAL PRIMARY KEY,
    voornaam VARCHAR(50),
    achternaam VARCHAR(50),
    straat VARCHAR(100),
    huisnummer INT,
    postcode VARCHAR(10),
    telefoonnummer VARCHAR(50),
    email VARCHAR(100)
);

CREATE TABLE Rekening (
    rekening_id SERIAL PRIMARY KEY,
    rekeningnummer VARCHAR(50),
    saldo NUMERIC(15,2)
);

CREATE TABLE Kaart (
    kaart_id SERIAL PRIMARY KEY,
    vervaldatum TIMESTAMP,
    pincode CHAR(4),
    pogingen INT NOT NULL,
    geblokkeerd BOOLEAN,
    gebruiker_id INT NOT NULL,
    rekening_id INT NOT NULL,
    FOREIGN KEY (gebruiker_id) REFERENCES Gebruiker(gebruiker_id) ON DELETE CASCADE,
    FOREIGN KEY (rekening_id) REFERENCES Rekening(rekening_id) ON DELETE CASCADE
);

CREATE TABLE Transactie (
    transactie_id SERIAL PRIMARY KEY,
    bedrag NUMERIC(15,2),
    datum TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    kaart_id INT NOT NULL,
    FOREIGN KEY (kaart_id) REFERENCES Kaart(kaart_id) ON DELETE CASCADE
);

ALTER TABLE Kaart
RENAME COLUMN pincode TO pincode_hash;

ALTER TABLE Kaart
ALTER COLUMN pincode_hash TYPE VARCHAR(255);

INSERT INTO Gebruiker (
  gebruiker_id,
  voornaam,
  achternaam,
  straat,
  huisnummer,
  postcode,
  telefoonnummer,
  email
) VALUES (
  1,
  'Jan',
  'Jansen',
  'Dorpsstraat',
  12,
  '1234AB',
  '0612345678',
  'jan.jansen@example.com'
);



INSERT INTO Rekening (
  rekeningnummer,
  saldo
) VALUES (
  'NL01BANK0123456789',
  1500.00
) RETURNING rekening_id;
-- Stel dat het rekening_id uit de vorige stap 1 is
INSERT INTO Kaart (
  vervaldatum,
  pincode_hash,
  pogingen,
  geblokkeerd,
  gebruiker_id,
  rekening_id
) VALUES (
  '2027-12-31',
  '1111',  -- vervang dit met echte hash
  0,
  FALSE,
  1,
  1
);

UPDATE kaart 
SET pincode_hash = '$2b$10$wu.d8ZSyRPodSXfj5XHBSOwMsUECOjPRXqdNcLlUV5DGRjSZrpb5q' 
WHERE pincode_hash = '1111';

UPDATE kaart
SET kaart_id = '738392E2'
WHERE kaart_id = '2'

ALTER TABLE transactie ADD COLUMN klant_id INT;

ALTER TABLE transactie
ADD CONSTRAINT fk_transactie_kaart
FOREIGN KEY (kaart_id)
REFERENCES kaart (kaart_id);

UPDATE kaart
SET kaart_id = '2'
WHERE kaart_id = '738392E2'


UPDATE Rekening
SET saldo = 2500.00
WHERE rekening_id = 1;