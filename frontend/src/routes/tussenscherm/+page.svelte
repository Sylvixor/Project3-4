<script lang="ts">
  import { goto } from '$app/navigation';
  import { createEventDispatcher } from 'svelte';

  interface CustomEvents {
    back: undefined;
    switchLanguage: undefined;
  }

  const dispatch = createEventDispatcher<CustomEvents>();
  
  export let language: 'nl' | 'en' = 'nl';

  const confirm = (): void => {
    goto('/eindscherm');
  };

  const goBack = (): void => {
    dispatch('back');
  };

  const switchLanguage = (): void => {
    dispatch('switchLanguage');
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
    justify-content: center;
    padding: 1rem;
    gap: 2rem;
  }

  .logo {
    width: 624px;
    filter: drop-shadow(0 0 10px rgba(255,255,255,0.1));
    margin-bottom: 2rem;
  }

  .message {
    font-size: 1.6rem;
    color: #ddd;
  }

  .side {
    display: flex;
    flex-direction: column;
    align-items: flex-end;
    justify-content: flex-start;
    gap: 1rem;
    padding-top: 2rem;
  }

  .emoji-btn, .action-btn {
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    font-size: 1rem;
    padding: 0.75rem 1.5rem;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .emoji-btn {
    font-size: 2rem;
    width: 64px;
    height: 64px;
    display: flex;
    align-items: center;
    justify-content: center;
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
  <!-- Midden -->
  <div class="center">
    <img class="logo" src="/logo.png" alt="Logo" />
    <div class="message">
      {#if language === 'nl'}
        Weet je zeker dat je deze handeling wilt bevestigen?
      {:else}
        Are you sure you want to confirm this transaction?
      {/if}
    </div>
  </div>

  <!-- Rechterzijde -->
  <div class="side">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? '🇬🇧' : '🇳🇱'}
    </button>
    <button class="action-btn" on:click={confirm}>
      {language === 'nl' ? 'Ja' : 'Yes'}
    </button>
    <button class="action-btn" on:click={goBack}>
      {language === 'nl' ? 'Terug' : 'Back'}
    </button>
  </div>
</div>