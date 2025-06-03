<script>
  import { createEventDispatcher, onMount } from 'svelte';
  const dispatch = createEventDispatcher();

  export let language = 'nl';

  onMount(() => {
    const timer = setTimeout(() => {
      dispatch('restart');
    }, 5000); // 5 seconden wachten

    return () => clearTimeout(timer); // opschonen bij unmount
  });
</script>

<style>
  :global(body) {
    margin: 0;
    font-family: 'Segoe UI', sans-serif;
    background-color: #0f0f0f;
    color: #f0f0f0;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
  }

  .container {
    text-align: center;
    max-width: 400px;
    padding: 2rem;
    border: 2px solid #444;
    border-radius: 16px;
    background-color: #1e1e1e;
    box-shadow: 0 0 20px rgba(255,255,255,0.1);
  }

  .message {
    font-size: 1.8rem;
  }
</style>

<div class="container">
  <div class="message">
    {#if language === 'nl'}
      Bedankt voor het gebruiken van de automaat!
    {:else}
      Thank you for using the ATM!
    {/if}
  </div>
</div>