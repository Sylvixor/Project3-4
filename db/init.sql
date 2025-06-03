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