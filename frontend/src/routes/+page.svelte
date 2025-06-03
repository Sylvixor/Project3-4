<script>
  import { onMount } from 'svelte';
  import { goto } from '$app/navigation';

  let kaartId = null;
  let error = '';
  let polling = true;

  const pollForCard = async () => {
    try {
      const response = await fetch('http://localhost:3000/api/kaart/scan/last');

      if (response.status === 200) {
        const data = await response.json();
        kaartId = data.kaart_id;
        console.log("Kaart gescand:", kaartId);
        goto(`/pincode/${kaartId}`);
      } else if (response.status === 204) {
        console.log("Nog geen kaart gescand...");
      } else {
        console.error("Fout:", response.status);
        error = 'Serverfout. Probeer opnieuw.';
        polling = false;
      }
    } catch (err) {
      console.error("Verbindingsfout:", err);
      error = 'Kan geen verbinding maken met de server.';
      polling = false;
    }
  };

  onMount(() => {
    const interval = setInterval(() => {
      if (polling) pollForCard();
    }, 1000);

    return () => clearInterval(interval);
  });

  let showPinScreen = true;

  function handleCorrectPin() {
    showPinScreen = false;
  }
</script>

<div class="screen">
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="instruction">
      Scan je kaart om te beginnen
    </div>

    {#if error}
      <div class="error-message">{error}</div>
    {/if}
  </div>
</div>

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

  .error-message {
    color: red;
    font-size: 1rem;
    margin-top: 1rem;
  }
</style>
