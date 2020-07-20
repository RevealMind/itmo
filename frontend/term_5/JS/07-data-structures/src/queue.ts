import { LinkedList } from './linkedList';

export class Queue<T> {
  private list: LinkedList<T> = new LinkedList<T>();

  get(index: number): T | void {
    return this.list.get(index);
  }

  enqueue(element: T): void {
    return this.list.unshift(element);
  }

  dequeue(): T | void {
    return this.list.pop();
  }

  get size(): number {
    return this.list.size;
  }
}
