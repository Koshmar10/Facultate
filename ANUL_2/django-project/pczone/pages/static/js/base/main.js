console.log("✅ JS loaded (improved)!");

function parseDurationToMs(durStr) {
  if (!durStr) return 0;
  // pick first value if comma-separated
  durStr = durStr.split(',')[0].trim();
  if (durStr.endsWith('ms')) return parseFloat(durStr) || 0;
  if (durStr.endsWith('s')) return (parseFloat(durStr) || 0) * 1000;
  return parseFloat(durStr) || 0;
}

document.addEventListener('DOMContentLoaded', () => {
  const dropdownWrappers = Array.from(document.querySelectorAll('.dropdown'));

  if (!dropdownWrappers.length) return;

  const openMenu = (menu) => {
    menu.classList.remove('exiting');
    // restart animation if needed
    void menu.offsetWidth;
    menu.classList.add('show');
  };

  const closeMenu = (menu) => {
    if (!menu.classList.contains('show')) return;

    // start exit animation
    menu.classList.add('exiting');

    // compute animation duration (in ms)
    const animDuration = parseDurationToMs(getComputedStyle(menu).animationDuration);

    if (animDuration === 0) {
      menu.classList.remove('show', 'exiting');
      return;
    }

    // fallback in case animationend doesn't fire
    let finished = false;
    const onAnimEnd = (e) => {
      if (e.target !== menu) return;
      finished = true;
      menu.classList.remove('show', 'exiting');
      menu.removeEventListener('animationend', onAnimEnd);
    };
    menu.addEventListener('animationend', onAnimEnd);

    // safety timeout (slightly longer than animation)
    setTimeout(() => {
      if (!finished) {
        menu.classList.remove('show', 'exiting');
        menu.removeEventListener('animationend', onAnimEnd);
      }
    }, animDuration + 100);
  };

  // wire each dropdown wrapper separately (supports multiple dropdowns)
  dropdownWrappers.forEach((wrapper) => {
    const btn = wrapper.querySelector('.dropbtn');
    const menu = wrapper.querySelector('.dropdown-content');
    if (!btn || !menu) return;

    btn.addEventListener('click', (e) => {
      e.stopPropagation();
      if (menu.classList.contains('show')) closeMenu(menu);
      else openMenu(menu);
    });

    // close on click inside menu links (optional) — keeps UX simple
    menu.addEventListener('click', (e) => {
      const tgt = e.target.closest('a');
      if (tgt) closeMenu(menu);
    });
  });

  // click outside closes any open dropdown
  document.addEventListener('click', (e) => {
    dropdownWrappers.forEach((wrapper) => {
      const menu = wrapper.querySelector('.dropdown-content');
      const btn = wrapper.querySelector('.dropbtn');
      if (!menu) return;
      if (!menu.contains(e.target) && !btn.contains(e.target)) {
        closeMenu(menu);
      }
    });
  });})