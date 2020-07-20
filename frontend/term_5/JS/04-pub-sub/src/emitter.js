'use strict';
/**
 * Сделано дополнительное задание: реализованы методы several и through.
 */
const isExtraTaskSolved = true;

/**
 * Получение нового Emitter'а
 * @returns {Object}
 */
function getEmitter() {
  const eventList = {};

  function subscribeHandler({ event, context, handler, type, value }) {
    this.on(event, context, handler);

    if (value > 0) {
      const lastEventField = eventList[event].length - 1;

      eventList[event][lastEventField].typeInfo = {
        type,
        value,
        eventNumber: 0
      };
    }
  }

  return {
    /**
     * Подписка на событие
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     */
    on: function(event, context, handler) {
      if (!eventList[event]) {
        eventList[event] = [{ context, handler }];
      } else {
        eventList[event].push({ context, handler });
      }

      return this;
    },

    /**
     * Отписка от события
     * @param {string} event
     * @param {Object} context
     */
    off: function(event, context) {
      const filteredEvent = Object.keys(eventList).filter(
        currentEvent => currentEvent.startsWith(`${event}.`) || currentEvent === event
      );

      for (const currentEvent of filteredEvent) {
        eventList[currentEvent] = eventList[currentEvent].filter(
          eventField => eventField.context !== context
        );
      }

      return this;
    },

    /**
     * Уведомление о событии
     * @param {string} event
     */
    emit: function(event) {
      while (event !== '') {
        if (eventList[event]) {
          for (let i = 0; i < eventList[event].length; i++) {
            const { context, handler, typeInfo = {} } = eventList[event][i];
            const { type, value, eventNumber } = typeInfo;

            if (type === 'several') {
              if (eventNumber < value) {
                handler.call(context);

                eventList[event][i].typeInfo.eventNumber += 1;
              } else {
                eventList[event].splice(i, 1);
              }
            } else if (type === 'through') {
              if (!eventNumber) {
                handler.call(context);
              }

              eventList[event][i].typeInfo.eventNumber += 1;
              eventList[event][i].typeInfo.eventNumber %= value;
            } else {
              handler.call(context);
            }
          }
        }

        event = event.substring(0, event.lastIndexOf('.'));
      }

      return this;
    },

    /**
     * Подписка на событие с ограничением по количеству отправляемых уведомлений
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     * @param {number} times Сколько раз отправить уведомление
     */
    several: function(event, context, handler, times) {
      subscribeHandler.call(this, { event, context, handler, type: 'several', value: times });

      return this;
    },

    /**
     * Подписка на событие с ограничением по частоте отправки уведомлений
     * @param {string} event
     * @param {Object} context
     * @param {Function} handler
     * @param {number} frequency Как часто уведомлять
     */
    through: function(event, context, handler, frequency) {
      subscribeHandler.call(this, { event, context, handler, type: 'through', value: frequency });

      return this;
    }
  };
}

module.exports = {
  getEmitter,

  isExtraTaskSolved
};
