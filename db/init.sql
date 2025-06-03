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
    gebruiker_id INT NOT NULL,
    rekening_id INT NOT NULL,
    vervaldatum TIMESTAMP,
    pincode CHAR(4),
    pogingen INT NOT NULL,
    FOREIGN KEY (gebruiker_id) REFERENCES Gebruiker(gebruiker_id) ON DELETE CASCADE,
    FOREIGN KEY (rekening_id) REFERENCES Rekening(rekening_id) ON DELETE CASCADE
);

CREATE TABLE Transactie (
    transactie_id SERIAL PRIMARY KEY,
    bedrag NUMERIC(15,2),
    datum TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    gebruiker_id INT NOT NULL,
    FOREIGN KEY (gebruiker_id) REFERENCES Gebruiker(gebruiker_id) ON DELETE CASCADE
);


ALTER TABLE Kaart DROP CONSTRAINT kaart_gebruiker_id_fkey;
ALTER TABLE Transactie DROP CONSTRAINT transactie_gebruiker_id_fkey;

ALTER TABLE Gebruiker
    ALTER COLUMN gebruiker_id TYPE VARCHAR(8);

    ALTER TABLE Kaart
    ALTER COLUMN gebruiker_id TYPE VARCHAR(8);

ALTER TABLE Transactie
    ALTER COLUMN gebruiker_id TYPE VARCHAR(8);

    ALTER TABLE Kaart
    ADD CONSTRAINT kaart_gebruiker_id_fkey FOREIGN KEY (gebruiker_id) REFERENCES Gebruiker(gebruiker_id) ON DELETE CASCADE;

ALTER TABLE Transactie
    ADD CONSTRAINT transactie_gebruiker_id_fkey FOREIGN KEY (gebruiker_id) REFERENCES Gebruiker(gebruiker_id) ON DELETE CASCADE;

    INSERT INTO Gebruiker (gebruiker_id, voornaam) VALUES ('1234abcd', 'Jane');

    DROP DATABASE;

