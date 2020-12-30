const observer = new MutationObserver((mutationsList, observer) => {
    for(let mutation of mutationsList) {
        const addedNodes = Array.from(mutation.addedNodes);
        if (addedNodes && addedNodes.some(n => n.nodeName === 'SCRIPT')) {
        	script = document.querySelector("[src*='items.js'");
			if (script != null) {
				document.head.removeChild(script);
				observer.disconnect();
			}
        }
    }
});
observer.observe(document, { childList: true, subtree: true });