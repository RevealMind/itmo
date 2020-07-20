'use strict';

/**
 * @typedef {Object} Friend
 * @property {string} name Имя
 * @property {'male' | 'female'} gender Пол
 * @property {boolean} best Лучший ли друг?
 * @property {string[]} friends Список имён друзей
 */

/**
 * Итератор по друзьям
 * @constructor
 * @param {Friend[]} friends Список друзей
 * @param {Filter} filter Фильтр друзей
 */
function Iterator(friends, filter) {
  if (!(filter instanceof Filter)) {
    throw new TypeError('Error: filter must be instanceof Filters');
  }

  this.guests = getInvitedList(friends, filter, this.maxLevel);
}

Iterator.prototype.done = function() {
  return !this.guests.length;
};

Iterator.prototype.next = function() {
  return this.done() ? null : this.guests.shift();
};

/**
 * Итератор по друзям с ограничением по кругу
 * @extends Iterator
 * @constructor
 * @param {Friend[]} friends Список друзей
 * @param {Filter} filter Фильтр друзей
 * @param {Number} maxLevel Максимальный круг друзей
 */
function LimitedIterator(friends, filter, maxLevel) {
  this.maxLevel = maxLevel;
  Iterator.call(this, friends, filter);
}

LimitedIterator.prototype = Object.create(Iterator.prototype);
LimitedIterator.prototype.constructor = LimitedIterator;

/**
 * Фильтр друзей
 * @constructor
 */
function Filter() {
  this.filterByGender = () => true;
}

/**
 * Фильтр друзей-парней
 * @extends Filter
 * @constructor
 */
function MaleFilter() {
  this.filterByGender = ({ gender }) => gender === 'male';
}

MaleFilter.prototype = Object.create(Filter.prototype);
MaleFilter.prototype.constructor = MaleFilter;

/**
 * Фильтр друзей-девушек
 * @extends Filter
 * @constructor
 */
function FemaleFilter() {
  this.filterByGender = ({ gender }) => gender === 'female';
}

FemaleFilter.prototype = Object.create(Filter.prototype);
FemaleFilter.prototype.constructor = FemaleFilter;

const sortByName = (first, second) => first.name.localeCompare(second.name);

function getInvitedList(friends, filter, level = Infinity) {
  const invitedGuestsList = [];

  let currentFriends = friends.filter(({ best }) => best).sort(sortByName);
  let currentLevel = 0;

  while (currentFriends.length !== 0 && currentLevel < level) {
    for (const guest of currentFriends) {
      invitedGuestsList.push(guest);
    }

    const nextFriends = new Set();

    for (const guest of currentFriends) {
      for (const nameFriendOfGuest of guest.friends) {
        const friendOfGuest = friends.find(
          friend => friend.name === nameFriendOfGuest && !invitedGuestsList.includes(friend)
        );

        if (friendOfGuest) {
          nextFriends.add(friendOfGuest);
        }
      }
    }

    currentFriends = Array.from(nextFriends).sort(sortByName);
    currentLevel++;
  }

  return invitedGuestsList.filter(filter.filterByGender);
}

module.exports = {
  Iterator,
  LimitedIterator,
  Filter,
  MaleFilter,
  FemaleFilter
};
