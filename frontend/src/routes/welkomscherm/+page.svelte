<script>
  let language = 'nl';

  const switchLanguage = () => {
    language = language === 'nl' ? 'en' : 'nl';
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
    filter: drop-shadow(0 0 10px rgba(255,255,255,0.1));
  }

  .instruction {
    font-size: 1.6rem;
    font-weight: 500;
    max-width: 90%;
    color: #ddd;
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
    height: var(--button-height, 64px); /* � Hoogte makkelijk aanpasbaar */
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
</style>

<div class="screen">
  <!-- Middeninhoud -->
  <div class="center">
    <img class="logo" src="\src\logo.png" alt="Logo" />
    <div class="instruction">
      {#if language === 'nl'}
        Scan je pas om te beginnen
      {:else}
        Scan your card in order to start
      {/if}
    </div>
  </div>

  <!-- Rechterknoppen -->
  <div class="side">
 <button class="emoji-btn" on:click={switchLanguage}>
  {#if language === 'nl'}
    &laquo; NL
  {:else}
    &laquo; EN
  {/if}
</button>

  </div>
</div>