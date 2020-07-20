class Pair<V> {
  constructor(public key: string | object, public value: V) {}
}

export class HashTable<T> {
  private static TABLE_CAPACITY = 2048;
  private static MOD = 1000000007;
  private static PRIME = 59;

  private elements: Pair<T>[][];
  private _size: number;

  constructor() {
    this.elements = [];
    this._size = 0;
  }

  get(key: string | object): T | void {
    const hash = HashTable.hash(key) % this.elements.length;

    const pair = this.elements[hash].find(element => element.key === key);

    return pair?.value;
  }

  public put(key: string | object, element: T): void {
    const hash = HashTable.hash(key) % this.elements.length;

    if (this.elements[hash] === undefined) {
      this.elements[hash] = [];
    }

    this.elements[hash].push(new Pair<T>(key, element));
    this._size++;
  }

  get size(): number {
    return this._size;
  }

  clear(): void {
    this.elements = [];
    this._size = 0;
  }

  private static hash(key: string | object): number {
    const string = typeof key === 'string' ? key : JSON.stringify(key);
    let hash = 1;

    for (const char of string) {
      hash = (hash * HashTable.PRIME + Number(char)) % HashTable.MOD;
    }

    return hash;
  }
}
