document.querySelector('#width-button').addEventListener('click', async (event) => {
    event.preventDefault();
    const response = await fetch('/measurement/width', { method: 'GET' });
    const data = await response.text();
    document.getElementById('display-width').value = data;
});

document.querySelector('#height-button').addEventListener('click', async (event) => {
    event.preventDefault();
    const response = await fetch('/measurement/height', { method: 'GET' });
    const data = await response.text();
    document.getElementById('display-height').textContent = data;
});