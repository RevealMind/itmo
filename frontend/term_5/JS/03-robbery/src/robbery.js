'use strict';
/**
 * Флаг решения дополнительной задачи
 * @see README.md
 */
const isExtraTaskSolved = true;

const MINUTES_PER_HOUR = 60;
const HOURS_PER_DAY = 24;
const MINUTES_PER_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR;

const availableDays = { ПН: 0, ВТ: 1, СР: 2 };
const days = ['ПН', 'ВТ', 'СР'];

/**
 * @param {Object} schedule Расписание Банды
 * @param {number} duration Время на ограбление в минутах
 * @param {Object} workingHours Время работы банка
 * @param {string} workingHours.from Время открытия, например, "10:00+5"
 * @param {string} workingHours.to Время закрытия, например, "18:00+5"
 * @returns {Object}
 */
function getAppropriateMoment(schedule, duration, workingHours) {
  const availableTime = [];
  const availableGaps = [];
  const timeZoneOfBank = workingHours.from.split('+')[1];
  let currentGap = 0;

  for (const arrayOfGaps of Object.values(schedule)) {
    for (const gap of arrayOfGaps) {
      setGap(splitGapByDate(gap));
    }
  }

  setBankGap(splitGapByDate(workingHours));

  let currentMinute = 0;

  while (currentMinute < 3 * MINUTES_PER_DAY) {
    let currentGap = 0;

    while (
      currentGap + currentMinute < 3 * MINUTES_PER_DAY &&
      currentGap < duration &&
      availableTime[currentGap + currentMinute]
    ) {
      currentGap++;
    }

    if (currentGap === duration) {
      availableGaps.push(currentMinute);
      currentMinute += 30;
    } else {
      currentMinute++;
    }
  }

  function splitGapByDate(gap) {
    return Object.values(gap).map(parseGap);
  }

  function setGap([from, to]) {
    for (let minute = from; minute < to; minute++) {
      availableTime[minute] = false;
    }
  }

  function setBankGap([from, to]) {
    for (let day = 0; day < 3; day++) {
      for (let minute = from; minute < to; minute++) {
        const currentMinute = day * MINUTES_PER_DAY + minute;
        if (availableTime[currentMinute] === undefined) {
          availableTime[currentMinute] = true;
        }
      }
    }
  }

  function parseGap(date) {
    const splitDateBySpace = date.split(' ');

    const [day, timeAndZone] = splitDateBySpace.length === 1 ? ['ПН', date] : splitDateBySpace;
    const [time, timeZone] = timeAndZone.split('+');
    const [hours, minutes] = time.split(':').map(string => parseInt(string));

    const timeZoneDiff = timeZoneOfBank - timeZone;

    return (
      (hours + timeZoneDiff) * MINUTES_PER_HOUR + minutes + availableDays[day] * MINUTES_PER_DAY
    );
  }

  return {
    /**
     * Найдено ли время
     * @returns {boolean}
     */
    exists() {
      return availableGaps.length !== 0;
    },

    /**
     * Возвращает отформатированную строку с часами
     * для ограбления во временной зоне банка
     *
     * @param {string} template
     * @returns {string}
     *
     * @example
     * ```js
     * getAppropriateMoment(...).format('Начинаем в %HH:%MM (%DD)') // => Начинаем в 14:59 (СР)
     * ```
     */
    format(template) {
      if (availableGaps.length === 0) {
        return '';
      }

      const startTime = availableGaps[currentGap];
      const numberOfDay = Math.floor(startTime / MINUTES_PER_DAY);
      const hours = Math.floor(startTime / MINUTES_PER_HOUR) % HOURS_PER_DAY;
      const minutes = startTime % MINUTES_PER_HOUR;

      return template
        .replace(/%DD/, days[numberOfDay])
        .replace(/%HH/, String(hours).padStart(2, '0'))
        .replace(/%MM/, String(minutes).padStart(2, '0'));
    },

    /**
     * Попробовать найти часы для ограбления позже [*]
     * @note Не забудь при реализации выставить флаг `isExtraTaskSolved`
     * @returns {boolean}
     */
    tryLater() {
      if (currentGap + 1 < availableGaps.length) {
        currentGap++;

        return true;
      }

      return false;
    }
  };
}

module.exports = {
  getAppropriateMoment,

  isExtraTaskSolved
};
