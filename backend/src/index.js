// Importeren van express
require('dotenv').config();   //voor .env bestanden
const express = require("express");
const cors = require("cors");
const { Client } = require("pg");
const bcrypt = require("bcrypt");
const saltRounds = 10;


// PostgreSQL client instellen
const client = new Client({
  connectionString: process.env.DATABASE_URL,
});

client.connect()
  .then(() => console.log('Verbonden met PostgreSQL!'))
  .catch(err => console.error('Verbindingsfout:', err));

// Express app initialiseren
const app = express();
const port = process.env.PORT || 3000;
app.use(express.json());
app.use(cors());
// Basis GET route
app.get('/', (req, res) => {
  res.json({ message: 'Welkom bij de Express API!' });
});

// Variabele om laatst gescande kaart op te slaan
let laatstGescanndeKaart = null;
let laatstGescanndeTijd = null;

// POST: update laatst gescande kaart (door scanner)
app.post('/api/kaart/scan', (req, res) => {
  const { kaart_id } = req.body;

  if (!kaart_id) {
    return res.status(400).json({ error: 'kaart_id is verplicht' });
  }

  laatstGescanndeKaart = kaart_id;
  laatstGescanndeTijd = Date.now();

  console.log(`Nieuwe kaart gescand: ${kaart_id}`);

  res.status(200).json({ message: 'Scan geregistreerd' });
});

// GET: haal laatst gescande kaart op (voor frontend polling)
app.get('/api/kaart/scan/last', (req, res) => {
  // Alleen kaart teruggeven als recent gescand (binnen 10 seconden)
  const now = Date.now();
  if (laatstGescanndeKaart && (now - laatstGescanndeTijd) < 10000) {
    return res.status(200).json({ kaart_id: laatstGescanndeKaart });
  } else {
    return res.status(204).send(); // Geen content als niets recent gescand
  }
});

// GET gebruiker + pincode-hash via kaart_id
app.get('/kaart/:kaart_id', async (req, res) => {
  const { kaart_id } = req.params;
  try {
    const result = await client.query(`
      SELECT g.voornaam, k.pincode_hash
      FROM kaart k
      JOIN gebruiker g ON k.gebruiker_id = g.gebruiker_id
      WHERE k.kaart_id = $1
    `, [kaart_id]);

    if (result.rows.length === 0) {
      return res.status(404).send("Kaart niet gevonden");
    }

    console.log("DB resultaat:", result.rows[0]);
    res.json(result.rows[0]); // bevat voornaam + pincode_hash

  } catch (err) {
    console.error(err);
    res.status(500).send("Serverfout");
  }
});

// POST: registreer gebruiker + kaart + gehashte pincode
app.post('/registratie', async (req, res) => {
  const { gebruiker_id, voornaam, kaart_id, pincode, rekening_id } = req.body;

  try {
    const hashedPin = await bcrypt.hash(pincode, saltRounds);

    await client.query(
      'INSERT INTO gebruiker (gebruiker_id, voornaam) VALUES ($1, $2)',
      [gebruiker_id, voornaam]
    );

    await client.query(
      'INSERT INTO kaart (kaart_id, pincode_hash, gebruiker_id, rekening_id, pogingen, geblokkeerd) VALUES ($1, $2, $3, $4, $5, FALSE)',
      [kaart_id, hashedPin, gebruiker_id, rekening_id, 0]
    );

    res.status(201).send('Gebruiker en kaart succesvol toegevoegd');
  } catch (err) {
    console.error(err);
    res.status(500).send('Registratie mislukt');
  }
});

// POST: valideer ingevoerde pincode tegen gehashte waarde
app.post('/kaart/validate', async (req, res) => {
  const { kaart_id, pincode } = req.body;

  if (!kaart_id || !pincode) {
    return res.status(400).json({ error: 'kaart_id en pincode zijn verplicht' });
  }

  try {
    const result = await client.query(
      'SELECT pincode_hash, pogingen, geblokkeerd FROM kaart WHERE kaart_id = $1',
      [kaart_id]
    );

    if (result.rows.length === 0) {
      return res.status(404).json({ error: 'Kaart niet gevonden' });
    }

    const { pincode_hash, pogingen, geblokkeerd } = result.rows[0];

    if (geblokkeerd) {
      return res.status(403).json({ error: 'Kaart is geblokkeerd' });
    }

    if (pogingen >= 3) {
      await client.query('UPDATE kaart SET geblokkeerd = TRUE WHERE kaart_id = $1', [kaart_id]);
      return res.status(403).json({ error: 'Kaart is geblokkeerd wegens te veel verkeerde pogingen' });
    }

    const isValid = await bcrypt.compare(pincode, pincode_hash);

    if (isValid) {
      await client.query('UPDATE kaart SET pogingen = 0 WHERE kaart_id = $1', [kaart_id]);
      return res.status(200).json({ message: 'Pincode correct' });
    } else {
      await client.query('UPDATE kaart SET pogingen = pogingen + 1 WHERE kaart_id = $1', [kaart_id]);
      return res.status(401).json({ error: `Pincode onjuist. Pogingen: ${pogingen + 1}` });
    }

  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Validatiefout' });
  }
});

// GET: saldo ophalen via kaart_id
app.get('/api/saldo/:kaart_id', async (req, res) => {
  const { kaart_id } = req.params;

  try {
    const result = await client.query(`
      SELECT r.saldo
      FROM kaart k
      JOIN rekening r ON k.rekening_id = r.rekening_id
      WHERE k.kaart_id = $1
    `, [kaart_id]);

    if (result.rows.length === 0) {
      return res.status(404).json({ error: 'Saldo niet gevonden voor deze kaart' });
    }

    res.status(200).json({ saldo: result.rows[0].saldo });
  } catch (err) {
    console.error('Fout bij ophalen saldo:', err);
    res.status(500).json({ error: 'Interne serverfout bij saldo ophalen' });
  }
});


// Start server
app.listen(port, () => {
  console.log(`Server draait op http://localhost:${port}`);
});
