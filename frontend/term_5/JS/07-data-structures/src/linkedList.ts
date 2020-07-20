class Node<T> {
  prev?: Node<T>;
  next?: Node<T>;

  constructor(public value: T) {}
}

export class LinkedList<T> {
  private head?: Node<T>;
  private tail?: Node<T>;
  private pointer!: Node<T>;
  private _size = 0;

  get(index: number): T | undefined {
    if (index < 0 || index >= this.size) {
      return;
    }

    let currentNode = this.head;

    for (let i = 0; i < index; i++) {
      currentNode = currentNode?.next;
    }

    return currentNode?.value;
  }

  push(element: T): void {
    const newNode = new Node<T>(element);

    if (this.isEmpty()) {
      this.head = newNode;
      this.pointer = newNode;
    } else {
      if (!this.tail) {
        throw new Error('ERROR: tail is undefined');
      }

      newNode.prev = this.tail;
      this.tail.next = newNode;
    }

    this.tail = newNode;

    this._size++;
  }

  pop(): T | void {
    if (this.isEmpty()) {
      return;
    }

    if (!this.tail) {
      throw new Error('ERROR: tail is undefined');
    }

    if (this.pointer === this.tail) {
      this.prev();
    }

    const result = this.tail.value;
    this.tail = this.tail.prev;

    this._size--;

    return result;
  }

  unshift(element: T): void {
    const newNode = new Node<T>(element);

    if (this.isEmpty()) {
      this.tail = newNode;
    } else {
      if (!this.head) {
        throw new Error('ERROR: head is undefined');
      }

      newNode.next = this.head;
      this.head.prev = newNode;
    }

    this.head = newNode;

    this._size++;
  }

  shift(): T | void {
    if (this.isEmpty()) {
      return;
    }

    if (!this.head) {
      throw new Error('ERROR: head is undefined');
    }

    if (this.pointer === this.head) {
      this.next();
    }

    const result = this.head.value;
    this.head = this.head.next;

    this._size--;

    return result;
  }

  prev(): T | void {
    if (this.isEmpty()) {
      return;
    }

    const result = this.pointer.value;

    if (this.pointer !== this.head) {
      if (!this.pointer.prev) {
        throw new Error('ERROR: pointer.prev is undefined');
      }

      this.pointer = this.pointer.prev;
    }

    return result;
  }

  next(): T | void {
    if (this.isEmpty()) {
      return;
    }

    const result = this.pointer.value;

    if (this.pointer !== this.tail) {
      if (!this.pointer.next) {
        throw new Error('ERROR: pointer.next is undefined');
      }

      this.pointer = this.pointer.next;
    }

    return result;
  }

  get size(): number {
    return this._size;
  }

  private isEmpty(): boolean {
    return this.size === 0;
  }
}
