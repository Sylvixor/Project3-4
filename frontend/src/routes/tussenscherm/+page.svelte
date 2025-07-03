<script lang="ts">
  import { goto } from '$app/navigation';
  import { page } from '$app/stores';
  import { onMount } from 'svelte';
  let amount: number = 0;
  let kaartId: string | null = null;
  let error: string = '';
    let language: 'nl' | 'en' = 'nl';

  onMount(() => {
    const bedragParam = $page.url.searchParams.get('bedrag');
    if (bedragParam) {
      amount = parseFloat(bedragParam);
    }
    kaartId = $page.url.searchParams.get('kaart_id');
  });

    const switchLanguage = (): void => {
    language = language === 'nl' ? 'en' : 'nl';
  };

  const confirmWithdrawal = async () => {
    if (!kaartId) {
      error = 'Kaart ID ontbreekt. Kan opname niet verwerken.';
      return;
    }

    try {
      const response = await fetch('http://localhost:3000/api/opnemen', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          kaart_id: kaartId,
          bedrag: amount,
        }),
      });

      if (response.ok) {
        const data = await response.json();
        goto(`/eindscherm?bedrag=${data.opgenomenBedrag}`);
      } else {
        const errorData = await response.json();
        error = errorData.error || 'Opname mislukt.';
      }
    } catch (e) {
      error = 'Kon geen verbinding maken met de server.';
    }
  };

  const cancelWithdrawal = () => {
    // Ga terug naar het vorige scherm, dit kan 'beginscherm' of 'opnemen' zijn
    window.history.back();
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
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100vh;
    width: 100vw;
    padding: 2rem;
    box-sizing: border-box;
    text-align: center;
  }

  .instruction {
    font-size: 1.8rem;
    font-weight: 500;
    color: #ddd;
    margin-bottom: 2rem;
  }

  .amount-display {
    font-size: 2.5rem;
    font-weight: bold;
    color: #fff;
    margin-bottom: 3rem;
  }

  .button-container {
    display: flex;
    gap: 2rem;
  }

  .action-btn {
    background-color: #1e1e1e;
    color: white;
    border: 2px solid #333;
    border-radius: 12px;
    cursor: pointer;
    height: 64px;
    padding: 0 2rem;
    font-size: 1.2rem;
    white-space: nowrap;
    transition: background-color 0.2s ease, transform 0.2s ease;
  }

  .action-btn:hover {
    background-color: #333;
    transform: scale(1.05);
  }

  .action-btn:active {
    transform: scale(0.97);
  }

  .error {
    color: #ff5555;
    margin-top: 1rem;
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
  .error {
    color: #ff5555;
    margin-top: 1rem;
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
</style>
 <div class="side" style="--button-height: 72px">
    <button class="emoji-btn" on:click={switchLanguage}>
      {language === 'nl' ? ' NL' : ' EN'}
    </button>
      </div>
<div class="screen">
  <div class="instruction">
    {language === 'nl' ? `Weet u zeker dat u: €${amount.toFixed(2)} wilt opnemen?` : `Are you sure you want to withdraw: €${amount.toFixed(2)}?`}
  </div>
  <div class="button-container">
    <button class="action-btn" on:click={confirmWithdrawal}>{language === 'nl' ? 'Bevestigen [B]' : 'Confirm [B]'}</button>
    <button class="action-btn" on:click={cancelWithdrawal}>{language === 'nl' ? 'Annuleren [A]' : 'Cancel [A]'}</button>
  </div>
  {#if error}
    <div class="error">{error}</div>
  {/if}
</div>
