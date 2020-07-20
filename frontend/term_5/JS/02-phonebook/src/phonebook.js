'use strict';

/**
 * Если вы решили сделать дополнительное задание и реализовали функцию importFromDsv,
 * то выставьте значение переменной isExtraTaskSolved в true.
 */
const isExtraTaskSolved = true;

/**
 * Телефонная книга
 */
const phoneBook = {};

/**
 * Добавление записи в телефонную книгу
 * @param {string} phone
 * @param {string} [name]
 * @param {string} [email]
 * @returns {boolean}
 */
function add(phone, name, email) {
  if (typeof phone !== 'string' || !/^\d{10}$/.test(phone) || phone in phoneBook) {
    return false;
  }

  if (typeof name !== 'string' || name.length === 0) {
    return false;
  }

  if (typeof email !== 'string' && typeof email !== 'undefined') {
    return false;
  }

  phoneBook[phone] = { name, email: email || '' };

  return true;
}

/**
 * Обновление записи в телефонной книге
 * @param {string} phone
 * @param {string} [name]
 * @param {string} [email]
 * @returns {boolean}
 */
function update(phone, name, email) {
  if (typeof phone !== 'string' || !/^\d{10}$/.test(phone) || !(phone in phoneBook)) {
    return false;
  }

  if (typeof name !== 'string' || name.length === 0) {
    return false;
  }

  if (typeof email !== 'string' && typeof email !== 'undefined') {
    return false;
  }

  phoneBook[phone].name = name;
  phoneBook[phone].email = email || '';

  return true;
}

/**
 * Поиск записей по запросу в телефонной книге
 * @param {string} query
 * @returns {string[]}
 */
function find(query) {
  if (typeof query !== 'string' || query.length === 0) {
    return [];
  }

  const toCorrectFormat = rawNumber => {
    const match = rawNumber.match(/^(\d{3})(\d{3})(\d{2})(\d{2})$/);

    return `+7 (${match[1]}) ${match[2]}-${match[3]}-${match[4]}`;
  };

  const normalizeResponse = number => {
    const { name, email } = phoneBook[number];
    const normalizeNumber = toCorrectFormat(number);

    return email === '' ? `${name}, ${normalizeNumber}` : `${name}, ${normalizeNumber}, ${email}`;
  };

  return filteredPhoneNumbersByQuery(query)
    .map(normalizeResponse)
    .sort();
}

/**
 * Удаление записей по запросу из телефонной книги
 * @param {string} query
 * @returns {number}
 */
function findAndRemove(query) {
  if (typeof query !== 'string' || query.length === 0) {
    return 0;
  }

  let removedPhones = 0;

  filteredPhoneNumbersByQuery(query).forEach(phone => {
    removedPhones++;
    delete phoneBook[phone];
  });

  return removedPhones;
}

/**
 *  Возвращает номера из телефонной книги, в которых хотя одно контактное
 *  поле содержит строку запроса
 * @param {string} query
 * @returns {string[]}
 */
function filteredPhoneNumbersByQuery(query) {
  const fitQuery = number => {
    const { name, email } = phoneBook[number];

    return [name, email, number].some(field => field.includes(query));
  };

  const phones = Object.keys(phoneBook);

  return query === '*' ? phones : phones.filter(fitQuery);
}

/**
 * Импорт записей из dsv-формата
 * @param {string} dsv
 * @returns {number} Количество добавленных и обновленных записей
 */
function importFromDsv(dsv) {
  if (typeof dsv !== 'string') {
    return 0;
  }

  let successfulQuery = 0;

  for (const query of dsv.split('\n')) {
    const [name, phone, email] = query.split(';');

    if (add(phone, name, email) || update(phone, name, email)) {
      successfulQuery++;
    }
  }

  return successfulQuery;
}

module.exports = {
  add,
  update,
  find,
  findAndRemove,
  importFromDsv,

  isExtraTaskSolved
};
