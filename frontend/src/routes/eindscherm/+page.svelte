<script lang="ts">
  import { onMount } from 'svelte';
  import { goto } from '$app/navigation';
  import { page } from '$app/stores';

  let opgenomenBedrag = 0;
      let language: 'nl' | 'en' = 'nl';

  onMount(() => {
    const bedrag = $page.url.searchParams.get('bedrag');
    if (bedrag) {
      opgenomenBedrag = parseFloat(bedrag);
    }

    setTimeout(() => {
      goto('/');
    }, 5000);
  });

      const switchLanguage = (): void => {
    language = language === 'nl' ? 'en' : 'nl';
  };
</script>

<div class="eindscherm">
  <h1>{language === 'nl' ? 'Opname succesvol' : 'Withdraw succesful'}</h1>
  <p>{language === 'nl' ? `U heeft €${opgenomenBedrag.toFixed(2)} opgenomen.` : `You have withdrawn €${opgenomenBedrag.toFixed(2)}`}</p>
</div>

<style>
  .eindscherm {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100vh;
    text-align: center;
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
</style>
 <div class="side" style="--button-height: 72px">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? ' NL' : ' EN'}
    </button>
      </div>
