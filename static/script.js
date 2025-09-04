/** FLASHLIGHT stolen from https://tonsky.me/ :D **/

var mousePos;

function updateFlashlight(e) {
	mousePos = {clientX: e.clientX,
				clientY: e.clientY,
				pageX: e.pageX,
				pageY: e.pageY};

	flashlight.style.left = mousePos.clientX - 250 + 'px';
	flashlight.style.top = mousePos.clientY - 250 + 'px';

	// const centreX = darkModeGlow.offsetLeft + 38;
	// const centreY = darkModeGlow.offsetTop + 12;
	// const dist = Math.hypot(mousePos.pageX - centreX, mousePos.pageY - centreY);
	// const opacity = Math.max(0, Math.min(1, (dist - 50) / (200 - 50)));
	// darkModeGlow.style.opacity = opacity;
}

function updateDarkMode(e) {
	// const theme = document.querySelector("meta[name=theme-color]");
	if (document.body.classList.contains('dark')) {
		localStorage.setItem('dark', 'true');
		dark_mode_switch.textContent = "Switch to light mode";
		// theme.content = "#000";
		updateFlashlight(e);
		['mousemove', 'touchstart', 'touchmove', 'touchend'].forEach(function(s) {
			document.documentElement.addEventListener(s, updateFlashlight, false);
		});
	} else {
		localStorage.removeItem('dark');
		localStorage.removeItem('mousePos');
		dark_mode_switch.textContent = "Switch to dark mode";
		// theme.content = "#FDDB29";
		['mousemove', 'touchstart', 'touchmove', 'touchend'].forEach(function(s) {
			document.documentElement.removeEventListener(s, updateFlashlight, false);
		});
	}
}

window.addEventListener("load", (event) => {
	let cl = document.body.classList;
	dark_mode_switch.onclick = function(e) {
		if (cl.contains('dark')) {
			cl.remove('dark');
			cl.add('dark0');
			updateDarkMode(e);
			setTimeout(() => {
				cl.remove('dark0');
			}, 1000);
		} else {
			cl.add('dark0');
			setTimeout(() => {
				cl.remove('dark0');
				cl.add('dark');
				updateDarkMode(e);
			}, 34);
		}
	};

	// first time initialisation
	if (localStorage.getItem('dark')) {
		cl.toggle('dark');
		var mousePos = {clientX: 0, clientY: 0, pageX: 0, pageY: 0};
		const stored = localStorage.getItem('mousePos');
		if (stored) {
			mousePos = JSON.parse(stored);
		}
		updateDarkMode(mousePos);
	}
	else {
		dark_mode_switch.textContent = "Switch to dark mode";
	}
});

window.addEventListener("beforeunload", (event) => {
	if (document.body.classList.contains('dark') && mousePos) {
		localStorage.setItem('mousePos', JSON.stringify(mousePos));
	}
});
