'use strict';

global.fetch = require('node-fetch');

/**
 * @typedef {object} TripItem Город, который является частью маршрута.
 * @property {number} geoid Идентификатор города
 * @property {number} day Порядковое число дня маршрута
 */

const MAX_DAYS = 7;

const ConditionsEnum = {
  'clear': 'clear',
  'partly-cloudy': 'partly-cloudy',
  'cloudy': 'cloudy',
  'overcast': 'overcast',
  'sunny': 'sunny'
};
Object.freeze(ConditionsEnum);

class TripBuilder {
  constructor(geoids) {
    this.geoids = geoids;
    this.sequenceConditions = [];
    this.maxDays = MAX_DAYS;
  }

  /**
   * Метод, добавляющий условие наличия в маршруте
   * указанного количества солнечных дней
   * Согласно API Яндекс.Погоды, к солнечным дням
   * можно приравнять следующие значения `condition`:
   * * `clear`;
   * * `partly-cloudy`.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  sunny(daysCount) {
    this.sequenceConditions.push(...Array(daysCount).fill(ConditionsEnum['sunny']));

    return this;
  }

  /**
   * Метод, добавляющий условие наличия в маршруте
   * указанного количества пасмурных дней
   * Согласно API Яндекс.Погоды, к солнечным дням
   * можно приравнять следующие значения `condition`:
   * * `cloudy`;
   * * `overcast`.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  cloudy(daysCount) {
    this.sequenceConditions.push(...Array(daysCount).fill(ConditionsEnum['cloudy']));

    return this;
  }

  /**
   * Метод, добавляющий условие максимального количества дней.
   * @param {number} daysCount количество дней
   * @returns {object} Объект планировщика маршрута
   */
  max(daysCount) {
    this.maxDays = daysCount;

    return this;
  }

  /**
   * Метод, возвращающий Promise с планируемым маршрутом.
   * @returns {Promise<TripItem[]>} Список городов маршрута
   */
  async build() {
    try {
      const weather = await Promise.all(this.geoids.map(this._getWeather));

      const jsonWeather = await Promise.all(weather.map(response => response.json()));

      const forecasts = await Promise.all(jsonWeather.map(this._getCondition));

      const route = this._tryBuild(forecasts, [], 0);

      if (route) {
        return Promise.resolve(route);
      }

      return Promise.reject(new Error('Не могу построить маршрут!'));
    } catch (e) {
      console.log(e);
      throw e;
    }
  }

  _getWeather(id) {
    const url = `https://api.weather.yandex.ru/v1/forecast?hours=false&geoid=${id}&limit=7`;

    return global.fetch(url);
  }

  _getCondition(json) {
    return {
      geoid: json['info']['geoid'],
      condition: json.forecasts.map(day => day.parts['day_short'].condition)
    };
  }

  _tryBuild(forecasts, route, daysInLastTown) {
    if (route.length === this.sequenceConditions.length) {
      return route;
    }

    const lastTown = route[route.length - 1] || null;

    if (lastTown) {
      if (daysInLastTown < this.maxDays) {
        const newRoute = this._buildStep({
          forecasts,
          route,
          currentGeoid: lastTown.geoid,
          daysInTown: daysInLastTown
        });
        if (newRoute) {
          return newRoute;
        }
      }
    }

    for (const currentGeoid of this.geoids) {
      if (!route.some(({ geoid }) => currentGeoid === geoid)) {
        const newRoute = this._buildStep({ forecasts, route, currentGeoid, daysInTown: 0 });
        if (newRoute) {
          return newRoute;
        }
      }
    }

    return null;
  }

  _buildStep({ forecasts, route, currentGeoid, daysInTown }) {
    const day = route.length;
    const condition = forecasts.find(({ geoid }) => geoid === currentGeoid).condition[day];

    if (this._isWeatherFine(condition, day)) {
      return this._tryBuild(
        forecasts,
        route.concat([{ geoid: currentGeoid, day: day + 1 }]),
        daysInTown + 1
      );
    }

    return null;
  }

  _isWeatherFine(condition, day) {
    if (this.sequenceConditions[day] === 'sunny') {
      return condition === ConditionsEnum['clear'] || condition === ConditionsEnum['partly-cloudy'];
    } else if (this.sequenceConditions[day] === 'cloudy') {
      return condition === ConditionsEnum['cloudy'] || condition === ConditionsEnum['overcast'];
    }
  }
}

/**
 * Фабрика для получения планировщика маршрута.
 * Принимает на вход список идентификаторов городов, а
 * возвращает планировщик маршрута по данным городам.
 *
 * @param {number[]} geoids Список идентификаторов городов
 * @returns {TripBuilder} Объект планировщика маршрута
 * @see https://yandex.ru/dev/xml/doc/dg/reference/regions-docpage/
 */
function planTrip(geoids) {
  return new TripBuilder(geoids);
}

module.exports = {
  planTrip
};
