<script lang="ts">
  import { goto } from '$app/navigation';
  import { onMount } from 'svelte';

  let kaartIdUitScan = '';
  let pollInterval: number | undefined;

  onMount(() => {
    pollScan();
    pollInterval = setInterval(pollScan, 2000);

    return () => clearInterval(pollInterval);
  });

  const pollScan = async () => {
    try {
      const response = await fetch('http://localhost:3000/api/kaart/scan/last');
      if (response.ok) {
        const data = await response.json();
        kaartIdUitScan = data.kaart_id;
      } else {
        kaartIdUitScan = '';
      }
    } catch (err) {
      console.error('Fout bij ophalen kaart scan:', err);
    }
  };

  let language = 'nl';
  let pin = '';
  const maxPinLength = 4;
  let attempts = 0;
  const maxAttempts = 3;
  let errorMessage = '';

  const switchLanguage = () => {
    language = language === 'nl' ? 'en' : 'nl';
  };

  const appendPin = (digit: number) => {
    if (pin.length < maxPinLength) {
      pin += digit;
      errorMessage = '';
    }
  };

  const removeLastDigit = () => {
    pin = pin.slice(0, -1);
  };

  const handlePinSubmit = async () => {
    if (pin.length !== maxPinLength) {
      errorMessage = language === 'nl'
        ? 'Voer een volledige pincode in'
        : 'Enter a full PIN code';
      return;
    }

    if (!kaartIdUitScan) {
      errorMessage = language === 'nl'
        ? 'Geen kaart gescand'
        : 'No card scanned';
      return;
    }

    try {
      const response = await fetch('http://localhost:3000/kaart/validate', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ kaart_id: kaartIdUitScan, pincode: pin })
      });

      const data = await response.json().catch(() => null);
      console.log('Response:', response.status, data);

      if (response.ok) {
        goto('/beginscherm');
      } else if (response.status === 401) {
        attempts += 1;
        errorMessage = attempts < maxAttempts
          ? (language === 'nl' ? 'Pincode incorrect, probeer opnieuw.' : 'Incorrect PIN, try again.')
          : (language === 'nl' ? 'Te veel verkeerde pogingen, probeer het later.' : 'Too many attempts, try again later.');
        pin = '';
      } else if (response.status === 403) {
        errorMessage = language === 'nl' ? 'Kaart is geblokkeerd.' : 'Card is blocked.';
        pin = '';
      } else {
        errorMessage = language === 'nl' ? 'Serverfout, probeer later opnieuw.' : 'Server error, try again later.';
      }
    } catch (err) {
      errorMessage = language === 'nl' ? 'Fout bij verbinden met server.' : 'Connection error.';
    }
  };
</script>

<style>
  :global(body) {
    margin: 0;
    font-family: 'Segoe UI', sans-serif;
    background-color: #0f0f0f;
    color: #f0f0f0;
    overflow: hidden;
  }

  .screen {
    display: flex;
    height: 100vh;
    width: 100vw;
    padding: 2rem;
    box-sizing: border-box;
  }

  .center {
    flex: 1;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    text-align: center;
  }

  .logo {
    width: 624px;
    margin-bottom: 2rem;
    filter: drop-shadow(0 0 10px rgba(255, 255, 255, 0.1));
  }

  .instruction {
    font-size: 1.6rem;
    font-weight: 500;
    max-width: 90%;
    color: #ddd;
  }

  .pin-bolletjes {
    display: flex;
    gap: 1rem;
    margin-top: 2rem;
  }

  .bol {
    width: 24px;
    height: 24px;
    border-radius: 50%;
    border: 2px solid #555;
    background-color: #1a1a1a;
    transition: background-color 0.3s ease, transform 0.2s ease;
  }

  .filled {
    background-color: #fff;
    transform: scale(1.2);
  }

  .side {
    display: flex;
    flex-direction: column;
    align-items: flex-end;
    justify-content: flex-start;
    width: 100px;
    padding-top: 3rem;
  }

  .emoji-btn {
    font-size: 2rem;
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    width: 64px;
    height: 64px;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .emoji-btn:hover {
    background-color: #333;
    transform: scale(1.05);
  }

  .digit-button {
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    width: 48px;
    height: 48px;
    font-size: 1.5rem;
    margin: 0.5rem;
    cursor: pointer;
  }

  .digit-button:hover {
    background-color: #333;
    transform: scale(1.1);
  }

  .digit-button:active {
    transform: scale(0.95);
  }

  .error-message {
    color: red;
    font-size: 1rem;
    margin-top: 1rem;
  }

  .digit-buttons {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    margin-top: 1rem;
  }

  .kaart-status {
    font-size: 0.9rem;
    margin-top: 1rem;
    color: gray;
  }
</style>

<div class="screen">
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="instruction">
      {#if language === 'nl'}
        Voer je pincode in
      {:else}
        Enter your PIN
      {/if}
    </div>

    <div class="pin-bolletjes">
      {#each Array(maxPinLength) as _, i}
        <div class="bol {pin.length > i ? 'filled' : ''}"></div>
      {/each}
    </div>

    {#if errorMessage}
      <div class="error-message">{errorMessage}</div>
    {/if}

    <div class="kaart-status">
      {#if kaartIdUitScan}
        {language === 'nl' ? 'Kaart gescand:' : 'Card scanned:'} {kaartIdUitScan}
      {:else}
        {language === 'nl' ? 'Wacht op kaartscan...' : 'Waiting for card scan...'}
      {/if}
    </div>
  </div>

  <div class="side">
    <button class="emoji-btn" on:click={switchLanguage}>
      {'<<'}
    </button>

    <div class="digit-buttons">
      {#each [1, 2, 3, 4, 5, 6, 7, 8, 9, 0] as digit}
        <button class="digit-button" on:click={() => appendPin(digit)}>{digit}</button>
      {/each}
      <button class="digit-button" on:click={removeLastDigit}>←</button>
      <button class="digit-button" on:click={handlePinSubmit}>✔</button>
    </div>
  </div>
</div>
