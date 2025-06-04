

CREATE TABLE gebruiker (
    gebruiker_id INT PRIMARY KEY,
    voornaam VARCHAR(50),
    achternaam VARCHAR(50),
    straat VARCHAR(100),
    huisnummer INT,
    postcode VARCHAR(10),
    telefoonnummer VARCHAR(50),
    email VARCHAR(100)
);
 
CREATE TABLE rekening (
    rekening_id INT PRIMARY KEY,
    rekeningnummer VARCHAR(50),
    saldo NUMERIC(15,2)
);
 
CREATE TABLE kaart (
    kaart_id SERIAL PRIMARY KEY,
    gebruiker_id INT NOT NULL,
    rekening_id INT NOT NULL,
    vervaldatum TIMESTAMP,
    pincode_hash VARCHAR(100), -- 🔐 Use this instead of pincode CHAR(4)
    pogingen INT NOT NULL,
    FOREIGN KEY (gebruiker_id) REFERENCES gebruiker(gebruiker_id) ON DELETE CASCADE,
    FOREIGN KEY (rekening_id) REFERENCES rekening(rekening_id) ON DELETE CASCADE
);

 
CREATE TABLE transactie (
    transactie_id SERIAL PRIMARY KEY,
    bedrag NUMERIC(15,2),
    datum TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    gebruiker_id INT NOT NULL,
    FOREIGN KEY (gebruiker_id) REFERENCES gebruiker(gebruiker_id) ON DELETE CASCADE
);
 
 INSERT INTO rekening (rekening_id, rekeningnummer, saldo) VALUES (1, 'NL01BANK0123456789', 1000.00);

ALTER TABLE kaart ALTER COLUMN pogingen SET DEFAULT 0;
UPDATE kaart SET pogingen = 0 WHERE pogingen IS NULL;

ALTER TABLE kaart ADD COLUMN geblokkeerd BOOLEAN DEFAULT FALSE;

SELECT k.kaart_id, k.rekening_id, r.saldo
FROM kaart k
JOIN rekening r ON k.rekening_id = r.rekening_id
WHERE k.kaart_id = '1';
