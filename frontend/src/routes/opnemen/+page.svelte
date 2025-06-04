<script lang="ts">
  import { goto } from '$app/navigation';
  import { createEventDispatcher } from 'svelte';

  interface CustomEvents {
    switchLanguage: undefined;
    back: undefined;
    withdraw: { amount: number };
  }

  const dispatch = createEventDispatcher<CustomEvents>();

  export let language: 'nl' | 'en' = 'nl';
  let amount: string = '';
  let error: string = '';

  const switchLanguage = (): void => {
    dispatch('switchLanguage');
  };

  const goBack = (): void => {
    dispatch('back');
  };

  function isValidAmount(amount: number): boolean {
    const denominations: number[] = [50, 20, 10];
    for (let bill of denominations) {
      const count = Math.floor(amount / bill);
      amount -= count * bill;
    }
    return amount === 0;
  }

  const submitAmount = (): void => {
    const parsed = parseFloat(amount.replace(',', '.'));

    if (isNaN(parsed) || parsed <= 0) {
      error = language === 'nl' ? 'Ongeldig bedrag.' : 'Invalid amount.';
      return;
    }

    if (!isValidAmount(parsed)) {
      error =
        language === 'nl'
          ? 'Kan niet uitgekeerd worden met beschikbare biljetten.'
          : 'Cannot dispense with available notes.';
      return;
    }

    error = '';
    dispatch('withdraw', { amount: parsed });
    goto('/tussenscherm');
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
    margin-bottom: 1rem;
  }

  input {
    padding: 0.75rem 1rem;
    font-size: 1.2rem;
    border-radius: 8px;
    border: 2px solid #333;
    background-color: #1e1e1e;
    color: #fff;
    width: 200px;
    text-align: center;
    margin-bottom: 1rem;
  }

  input:focus {
    outline: none;
    border-color: #555;
  }

  .error {
    color: #ff5555;
    margin-bottom: 1rem;
    font-size: 1rem;
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

  .emoji-btn {
    font-size: 2rem;
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    width: 64px;
    height: var(--button-height, 64px);
    display: flex;
    align-items: center;
    justify-content: center;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .emoji-btn:hover {
    background-color: #333;
    transform: scale(1.05);
  }

  .emoji-btn:active {
    transform: scale(0.97);
  }

  .action-btn {
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    height: var(--button-height, 64px);
    padding: 0 1.5rem;
    font-size: 1rem;
    white-space: nowrap;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .action-btn:hover {
    background-color: #333;
    transform: scale(1.02);
  }

  .action-btn:active {
    transform: scale(0.97);
  }
</style>

<div class="screen">
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="instruction">
      {language === 'nl' ? 'Hoeveel wil je opnemen?' : 'How much would you like to withdraw?'}
    </div>
    <input
      type="text"
      bind:value={amount}
      placeholder={language === 'nl' ? 'Voer bedrag in (€)' : 'Enter amount (€)'}
    />
    {#if error}
      <div class="error">{error}</div>
    {/if}
    <button class="action-btn" on:click={submitAmount}>
      {language === 'nl' ? 'Bevestigen' : 'Confirm'}
    </button>
  </div>

  <div class="side" style="--button-height: 64px">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? '🇬🇧' : '🇳🇱'}
    </button>
    <button class="action-btn" on:click={goBack}>
      {language === 'nl' ? 'Terug' : 'Back'}
    </button>
  </div>
</div>