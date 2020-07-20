'use strict';

/**
 * Складывает два целых числа
 * @param {Number} a Первое целое
 * @param {Number} b Второе целое
 * @throws {TypeError} Когда в аргументы переданы не числа
 * @returns {Number} Сумма аргументов
 */
function abProblem(a, b) {
  if (typeof a !== 'number') {
    throw TypeError(`Expected integer number: '${a}' is not a number`);
  }

  if (typeof b !== 'number') {
    throw TypeError(`Expected integer number: '${b}' is not a number`);
  }
  
  return a + b;
}

/**
 * Определяет век по году
 * @param {Number} year Год, целое положительное число
 * @throws {TypeError} Когда в качестве года передано не число
 * @throws {RangeError} Когда год – отрицательное значение
 * @returns {Number} Век, полученный из года
 */
function centuryByYearProblem(year) {
  if (typeof year !== 'number') {
    throw TypeError(`Expected number: '${year}' is not correct value`);
  }

  if (year <= 0 || !Number.isInteger(year)) {
    throw RangeError(`Expected positive integer: '${year}' is not correct value`);
  }

  return Math.ceil(year / 100);
}

/**
 * Переводит цвет из формата HEX в формат RGB
 * @param {String} hexColor Цвет в формате HEX, например, '#FFFFFF'
 * @throws {TypeError} Когда цвет передан не строкой
 * @throws {RangeError} Когда значения цвета выходят за пределы допустимых
 * @returns {String} Цвет в формате RGB, например, '(255, 255, 255)'
 */
function colorsProblem(hexColor) {
  if (typeof hexColor !== 'string') {
    throw TypeError(`Expected string: '${hexColor}' is not a string`);
  }

  const result = hexColor.match(/^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i);
  if (!result) {
    throw RangeError(`Expected correct hex color: '${hexColor}' is not correct value`);
  }

  const r = parseInt(result[1], 16);
  const g = parseInt(result[2], 16);
  const b = parseInt(result[3], 16);

  return `(${r}, ${g}, ${b})`;
}

/**
 * Находит n-ое число Фибоначчи
 * @param {Number} n Положение числа в ряде Фибоначчи
 * @throws {TypeError} Когда в качестве положения в ряде передано не число
 * @throws {RangeError} Когда положение в ряде не является целым положительным числом
 * @returns {Number} Число Фибоначчи, находящееся на n-ой позиции
 */
function fibonacciProblem(n) {
  if (typeof n !== 'number') {
    throw TypeError(`Expected number: '${n}' is not a number`);
  }

  if (n <= 0 || !Number.isInteger(n)) {
    throw RangeError(`Expected positive integer: '${n}' is not correct value`);
  }

  let prev = 1;
  let cur = 1;
  for (let i = 3; i <= n; i++) {
    const next = prev + cur;
    prev = cur;
    cur = next;
  }

  return cur;
}

/**
 * Транспонирует матрицу
 * @param {(Any[])[]} matrix Матрица размерности MxN
 * @throws {TypeError} Когда в функцию передаётся не двумерный массив
 * @returns {(Any[])[]} Транспонированная матрица размера NxM
 */
function matrixProblem(matrix) {
  if (!Array.isArray(matrix) || matrix.length === 0 || matrix.some(row => !Array.isArray(row))) {
    throw TypeError(`Expected 2D-array: '${matrix}' is not correct value`);
  }

  if (matrix.some(row => row.length !== matrix[0].length)) {
    throw TypeError(`Expected correct 2D-array: '${matrix}' is not correct value`);
  }

  return matrix[0].map((_, index) => matrix.map(row => row[index]));
}

/**
 * Переводит число в другую систему счисления
 * @param {Number} n Число для перевода в другую систему счисления
 * @param {Number} targetNs Система счисления, в которую нужно перевести (Число от 2 до 36)
 * @throws {TypeError} Когда переданы аргументы некорректного типа
 * @throws {RangeError} Когда система счисления выходит за пределы значений [2, 36]
 * @returns {String} Число n в системе счисления targetNs
 */
function numberSystemProblem(n, targetNs) {
  if (typeof targetNs !== 'number') {
    throw TypeError(`Expected number: '${targetNs}' is not a number`);
  }

  if (typeof n !== 'number') {
    throw TypeError(`Expected number: '${n}' is not a number`);
  }

  if ((targetNs < 2 && targetNs > 36) || !Number.isInteger(targetNs)) {
    throw RangeError(`Expected integer in range [2, 36]: '${targetNs}' is not correct value`);
  }

  return n.toString(targetNs);
}

/**
 * Проверяет соответствие телефонного номера формату
 * @param {String} phoneNumber Номер телефона в формате '8–800–xxx–xx–xx'
 * @returns {Boolean} Если соответствует формату, то true, а иначе false
 */
function phoneProblem(phoneNumber) {
  if (typeof phoneNumber !== 'string') {
    throw TypeError(`Expected string: '${phoneNumber}' is not a string`);
  }

  return /^8-800-\d\d\d-\d\d-\d\d$/.test(phoneNumber);
}

/**
 * Определяет количество улыбающихся смайликов в строке
 * @param {String} text Строка в которой производится поиск
 * @throws {TypeError} Когда в качестве аргумента передаётся не строка
 * @returns {Number} Количество улыбающихся смайликов в строке
 */
function smilesProblem(text) {
  if (typeof text !== 'string') {
    throw TypeError(`Expected string: '${text}' is not a string`);
  }

  const count = text.match(/(:-\))|(\(-:)/g) || [];

  return count.length;
}

/**
 * Определяет победителя в игре "Крестики-нолики"
 * Тестами гарантируются корректные аргументы.
 * @param {(('x' | 'o')[])[]} field Игровое поле 3x3 завершённой игры
 * @returns {'x' | 'o' | 'draw'} Результат игры
 */
function ticTacToeProblem(field) {
  const rows = field;
  const columns = field[0].map((_, ind) => field.map(row => row[ind]));
  const firstDiagonal = field.map((item, ind) => item[ind]);
  const secondDiagonal = field.map((item, ind) => item[field.length - (ind + 1)]);

  const isWin = symbol =>
    [rows, columns].some(lines => lines.some(line => line.every(elem => elem === symbol))) ||
    [firstDiagonal, secondDiagonal].some(diagonal => diagonal.every(elem => elem === symbol));

  return ['x', 'o'].find(isWin) || 'draw';
}

module.exports = {
  abProblem,
  centuryByYearProblem,
  colorsProblem,
  fibonacciProblem,
  matrixProblem,
  numberSystemProblem,
  phoneProblem,
  smilesProblem,
  ticTacToeProblem
};
