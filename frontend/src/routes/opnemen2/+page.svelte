<script lang="ts">
  import { createEventDispatcher } from 'svelte';

  interface CustomEvents {
    switchLanguage: undefined;
    back: undefined;
    withdraw: { amount: number | 'quick' };
  }

  const dispatch = createEventDispatcher<CustomEvents>();

  export let language: 'nl' | 'en' = 'nl';

  const switchLanguage = (): void => {
    dispatch('switchLanguage');
  };

  const goBack = (): void => {
    dispatch('back');
  };

  const withdraw = (amount: number | 'quick'): void => {
    dispatch('withdraw', { amount });
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
    gap: 1rem;
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

  .side {
    display: flex;
    flex-direction: column;
    align-items: flex-end;
    justify-content: flex-start;
    width: auto;
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
  <!-- Middeninhoud -->
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="instruction">
      {language === 'nl'
        ? 'Kies een bedrag om op te nemen'
        : 'Choose an amount to withdraw'}
    </div>
  </div>

  <!-- Rechterknoppen -->
  <div class="side" style="--button-height: 64px">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? 'GB2' : 'NL2'}
    </button>

    <button class="action-btn" on:click={goBack}>
      {language === 'nl' ? 'Terug' : 'Back'}
    </button>

    <button class="action-btn" on:click={() => withdraw('quick')}>
      {language === 'nl' ? 'Snel opnemen' : 'Quick withdraw'}
    </button>

    <button class="action-btn" on:click={() => withdraw(10)}>€10</button>
    <button class="action-btn" on:click={() => withdraw(20)}>€20</button>
    <button class="action-btn" on:click={() => withdraw(50)}>€50</button>
  </div>
</div>