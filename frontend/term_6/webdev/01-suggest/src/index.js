const AUTOCOMPLETE_BLOCK = 'autocomplete-items';
const AUTOCOMPLETE_ITEM = `autocomplete-items__item`;
const AUTOCOMPLETE_INPUT = `autocomplete__input`;
const AUTOCOMPLETE_ITEM_ACTIVE = `autocomplete-items__item_active`;
const AUTOCOMPLETE_CODE = `autocomplete-items__item-code`;
const AUTOCOMPLETE_AIRPORT = `autocomplete-items__airport`;
const AUTOCOMPLETE_AIRPORT_IN_CITY = `autocomplete-items__airport_in-city`;
const AUTOCOMPLETE_LABEL_ACTIVE = `autocomplete__label_active`;
const AUTOCOMPLETE_SWAP = 'main-form__swap';

const DELAY = 500;

function throttle(func, ms) {
  let isThrottled = false;
  let savedArgs;
  let savedThis;

  function wrapper() {
    if (isThrottled) {
      savedArgs = arguments;
      savedThis = this;

      return;
    }

    func.apply(this, arguments);

    isThrottled = true;

    setTimeout(function() {
      isThrottled = false;

      if (savedArgs) {
        wrapper.apply(savedThis, savedArgs);
        savedArgs = null;
        savedThis = null;
      }
    }, ms);
  }

  return wrapper;
}

const swapButtonHandler = function() {
  const [from, to] = document.querySelectorAll(`.${AUTOCOMPLETE_INPUT}`);

  [from.value, to.value] = [to.value, from.value];

  [from, to].forEach(element => element.dispatchEvent(new Event('input')));
};

function autocomplete(input) {
  let prevItem;
  let currentItem;

  const selectClickHandler = function(event) {
    input.value = event.target.closest('div').querySelector('input').value;
    closeAllLists();
  };

  const inputControlHandler = async function() {
    const value = this.value;

    closeAllLists();
    if (!value.trim()) {
      this.parentNode.querySelector('label').classList.remove(AUTOCOMPLETE_LABEL_ACTIVE);

      return;
    }
    this.parentNode.querySelector('label').classList.add(AUTOCOMPLETE_LABEL_ACTIVE);

    currentItem = -1;

    const items = document.createElement('DIV');

    items.classList.add(AUTOCOMPLETE_BLOCK);
    this.parentNode.appendChild(items);

    items.addEventListener('click', selectClickHandler);

    const airports = await fetch(
      `https://places.aviasales.ru/v2/places.json?locale=ru&max=7&term=${value}&types[]=city&types[]=airport`
    ).then(response => response.json());

    let lastCity = null;

    for (const { name, code, country_name: country, city_name: city, type } of airports) {
      const item = document.createElement('DIV');
      const props = { name, code };

      item.classList.add(AUTOCOMPLETE_ITEM);

      if (type === 'city') {
        lastCity = name;
        props.cityName = country;
      } else {
        item.classList.add(AUTOCOMPLETE_AIRPORT);
        if (lastCity && city === lastCity) {
          item.classList.add(AUTOCOMPLETE_AIRPORT_IN_CITY);
        } else {
          props.cityName = city;
        }
      }

      item.innerHTML = createDiv(props);
      items.appendChild(item);
    }
  };

  const arrowsControlHandler = function(event) {
    let items = document.querySelector(`.${AUTOCOMPLETE_BLOCK}`);

    if (items) {
      items = items.getElementsByTagName('div');
    }

    if (event.code === 'ArrowDown') {
      prevItem = currentItem;
      currentItem++;
      addActive(items);
    } else if (event.code === 'ArrowUp') {
      event.preventDefault();
      prevItem = currentItem;
      currentItem--;
      addActive(items);
    } else if (event.code === 'Enter') {
      event.preventDefault();
      if (currentItem >= 0) {
        if (items) {
          items[currentItem].click();
        }
      }
    }
  };

  const closeListClickHandler = function(event) {
    closeAllLists(event.target);
  };

  input.addEventListener('input', throttle(inputControlHandler, DELAY));

  input.addEventListener('keydown', arrowsControlHandler);

  document.addEventListener('click', closeListClickHandler);

  function addActive(items) {
    if (!items) {
      return;
    }

    if (currentItem >= items.length) {
      currentItem = 0;
    } else if (currentItem < 0) {
      prevItem = 0;
      currentItem = items.length - 1;
    }

    if (prevItem >= 0) {
      items[prevItem].classList.remove(AUTOCOMPLETE_ITEM_ACTIVE);
    }

    items[currentItem].classList.add(AUTOCOMPLETE_ITEM_ACTIVE);

    input.value = items[currentItem].querySelector('input').value;
  }

  function closeAllLists(target) {
    const items = document.querySelector(`.${AUTOCOMPLETE_BLOCK}`);
    if (items !== null && target !== items) {
      items.removeEventListener('click', selectClickHandler);
      items.outerHTML = '';
    }
  }

  function createDiv({ name, cityName, code }) {
    let out = `<strong>${name}</strong>`;

    out += !cityName ? `` : `, ${cityName}`;
    out += `<input type="hidden" value="${name}">`;
    out += `<span class='${AUTOCOMPLETE_CODE}'>${code}</span>`;

    return out;
  }
}

document.querySelector(`.${AUTOCOMPLETE_SWAP}`).addEventListener('click', swapButtonHandler);

autocomplete(document.getElementById('from'));
autocomplete(document.getElementById('to'));
