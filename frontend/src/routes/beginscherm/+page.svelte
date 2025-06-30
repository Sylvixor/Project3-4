<script lang="ts">
  import { onMount } from 'svelte';
  import { goto } from '$app/navigation';

  let language: 'nl' | 'en' = 'nl';
  let saldo: number = 0;
  let showBalance: boolean = false;
  let kaartId: string | null = null;
  let balanceTimeout: number | undefined;

  // Bij component-mount: kaart ophalen
  onMount(async () => {
    await fetchKaartId();
    await fetchSaldo();
  });

  const switchLanguage = (): void => {
    language = language === 'nl' ? 'en' : 'nl';
  };

  const goToWithdraw = (): void => {
    goto('/opnemen');
  };

  const fetchKaartId = async (): Promise<void> => {
    try {
      const res = await fetch('http://localhost:3000/api/kaart/scan/last');
      if (!res.ok) throw new Error('Geen kaart gescand');
      const data = await res.json();
      kaartId = data.kaart_id;
      console.log("Gescande kaart ID:", kaartId);
    } catch (err) {
      console.error('Fout bij ophalen kaart ID:', err);
    }
  };

  const fetchSaldo = async (): Promise<void> => {
    try {
      if (!kaartId) {
        await fetchKaartId();
        if (!kaartId) throw new Error("kaart_id ontbreekt");
      }

      const res = await fetch(`http://localhost:3000/api/saldo/${kaartId}`);
      if (!res.ok) {
        const raw = await res.text();
        throw new Error(`Saldo niet gevonden: ${raw}`);
      }

      const data = await res.json();
      saldo = parseFloat(data.saldo) || 0;
      console.log("Saldo opgehaald:", saldo);
    } catch (err) {
      console.error("Fout bij ophalen saldo:", err);
      saldo = 0;
    }
  };

  const showBalanceTemporarily = async (): Promise<void> => {
    if (balanceTimeout) {
      clearTimeout(balanceTimeout);
    }
    await fetchSaldo();
    showBalance = true;
    balanceTimeout = setTimeout(() => {
      showBalance = false;
    }, 5000);
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
    align-items: center;
    text-align: center;
    padding-top: 5rem;
  }

  .logo {
    width: 624px;
    margin-bottom: 2rem;
    filter: drop-shadow(0 0 10px rgba(255,255,255,0.1));
  }

  .instruction {
    font-size: 1.6rem;
    font-weight: 500;
    color: #ddd;
    margin-bottom: 1.5rem;
  }

  .saldo {
    font-size: 1.4rem;
    color: #aaa;
    margin-bottom: 2rem;
  }

  .side {
    display: flex;
    flex-direction: column;
    align-items: flex-end;
    justify-content: flex-start;
    width: auto;
    padding-top: 3rem;
    gap: 1rem;
  }

  .emoji-btn,
  .action-btn {
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    height: var(--button-height, 64px);
    padding: 0 1.5rem;
    font-size: 1rem;
    display: flex;
    align-items: center;
    justify-content: center;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .emoji-btn {
    font-size: 2rem;
    width: 64px;
    padding: 0;
  }

  .emoji-btn:hover,
  .action-btn:hover {
    background-color: #333;
    transform: scale(1.05);
  }

  .emoji-btn:active,
  .action-btn:active {
    transform: scale(0.97);
  }
</style>

<div class="screen">
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="instruction">
      {#if language === 'nl'}
        Welkom! Kies een optie om door te gaan 
      {:else}
        Welcome! Choose an option to continue
      {/if}
    </div>
    <div class="saldo">
      {#if showBalance}
        {language === 'nl' ? `Saldo: €${saldo.toFixed(2)}` : `Balance: €${saldo.toFixed(2)}`}
      {/if}
    </div>
  </div>

  <div class="side" style="--button-height: 72px">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? '« NL' : '« EN'}
    </button>
    <button class="action-btn" on:click={showBalanceTemporarily}>
      {language === 'nl' ? 'Zie saldo' : 'Show balance'}
    </button>
    <button class="action-btn" on:click={goToWithdraw}>
      {language === 'nl' ? 'Opnemen' : 'Withdraw'}
    </button>
    <button class="action-btn" on:click={() => goto(`/tussenscherm?bedrag=${70}`)}>
      {language === 'nl' ? 'Snel €70 opnemen' : 'Quick Withdraw €70'}
    </button>
  </div>
</div>