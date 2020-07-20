import { Queue } from './queue';

enum Priority {
  Low = 1,
  Medium,
  High
}

export class PriorityQueue<T> {
  private lowQueue = new Queue<T>();
  private mediumQueue = new Queue<T>();
  private highQueue = new Queue<T>();

  enqueue(element: T, priority: number): void {
    let currentQueue = new Queue<T>();

    switch (priority) {
      case Priority.Low: {
        currentQueue = this.lowQueue;
        break;
      }
      case Priority.Medium: {
        currentQueue = this.mediumQueue;
        break;
      }
      case Priority.High: {
        currentQueue = this.highQueue;
        break;
      }
    }

    currentQueue.enqueue(element);
  }

  dequeue(): T | void {
    if (this.highQueue.size !== 0) {
      return this.highQueue.dequeue();
    } else if (this.mediumQueue.size !== 0) {
      return this.mediumQueue.dequeue();
    } else if (this.lowQueue.size !== 0) {
      return this.lowQueue.dequeue();
    }

    return;
  }

  get size(): number {
    return this.lowQueue.size + this.mediumQueue.size + this.highQueue.size;
  }
}
