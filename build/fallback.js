(function () {
    const message = `<pause=2000>
Error: Your browser does not support WebAssembly.<pause=700>
It is required for the website to render and work properly.<pause=500>
Please update to a modern browser 
(like Chrome, Firefox, Edge, or Safari)
and come back to check it out.<pause=1500>
:)
\n> <pause=15000> Transmission Received`;


    const fontLink = document.createElement('link');
    fontLink.href = 'https://fonts.googleapis.com/css2?family=VT323&display=swap';
    fontLink.rel = 'stylesheet';
    document.head.appendChild(fontLink);

    const style = document.createElement('style');
    style.textContent = `
    body {
      background-color: black;
      color: #ffbf00;
      font-family: 'VT323', monospace;
      margin: 0;
      padding: 40px;
      font-size: 30px;
      line-height: 1.6;
      text-shadow:
        0 0 4px #ffbf00,
        0 0 8px #ffbf00,
        0 0 12px rgba(255, 191, 0, 0.6);
    }
    .crt {
      max-width: 800px;
      margin: auto;
      white-space: pre-wrap;
      position: relative;
    }
    .cursor {
      display: inline-block;
      width: 12px;
      height: 20px;
      background-color: #ffbf00;
      margin-left: 4px;
      animation: blink 1s step-end infinite;
      box-shadow: 0 0 6px #ffbf00, 0 0 10px rgba(255, 191, 0, 0.5);
    }
    @keyframes blink {
      0%, 100% { opacity: 1; }
      50% { opacity: 0; }
    }
    .overlay {
      position: fixed;
      top: 0; left: 0;
      width: 100%;
      height: 100%;
      pointer-events: none;
      background: repeating-linear-gradient(
        to bottom,
        rgba(255, 191, 0, 0.025),
        rgba(255, 191, 0, 0.025) 1px,
        transparent 1px,
        transparent 3px
      );
    }
  `;
    document.head.appendChild(style);

    const crt = document.createElement('div');
    crt.className = 'crt';
    document.body.appendChild(crt);

    const overlay = document.createElement('div');
    overlay.className = 'overlay';
    document.body.appendChild(overlay);

    const cursor = document.createElement('span');
    cursor.className = 'cursor';
    crt.appendChild(cursor);

    const regex = /<pause=(\d+)>/g;
    const queue = [];
    let lastIndex = 0;
    let match;

    while ((match = regex.exec(message)) !== null) {
        if (match.index > lastIndex) {
            queue.push(...message.slice(lastIndex, match.index).split(''));
        }
        queue.push({ pause: parseInt(match[1]) });
        lastIndex = regex.lastIndex;
    }
    if (lastIndex < message.length) {
        queue.push(...message.slice(lastIndex).split(''));
    }

    function typeNext() {
        if (queue.length === 0) return;
        const next = queue.shift();
        if (typeof next === 'object' && next.pause) {
            setTimeout(typeNext, next.pause);
        } else {
            crt.insertBefore(document.createTextNode(next), cursor);
            setTimeout(typeNext, 35 + Math.random() * 40);
        }
    }

    typeNext();
})();
