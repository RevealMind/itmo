import { LinkedList } from './linkedList';

export class RingBuffer<T> {
  private linkedList = new LinkedList<T>();

  constructor(private _capacity: number) {}

  get(index: number): T | undefined {
    return this.linkedList.get(index);
  }

  push(element: T): void {
    if (this.capacity === this.size) {
      this.shift();
    }
    if (this.capacity !== 0) {
      this.linkedList.push(element);
    }
  }

  shift(): T | void {
    return this.linkedList.shift();
  }

  concat(...buffers: RingBuffer<T>[]): RingBuffer<T> {
    const capacity = buffers.reduce((accumulator, buffer) => accumulator + buffer.capacity, 0);

    const newBuffer = new RingBuffer<T>(capacity);

    for (const buffer of buffers) {
      for (let i = 0; i < buffer.size; i++) {
        newBuffer.push(buffer.get(i)!);
      }
    }

    return newBuffer;
  }

  get size(): number {
    return this.linkedList.size;
  }

  get capacity(): number {
    return this._capacity;
  }
}
