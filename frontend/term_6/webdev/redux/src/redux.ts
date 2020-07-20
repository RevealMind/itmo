import { AnyAction, AnyState, Reducer, Store, Unsubscribe } from './types';

const createStore = (reducer: Reducer, initialState?: AnyState, enhancer?: any): Store => {
  if (typeof reducer !== 'function') {
    throw new Error('Reducer must be a function');
  }

  if (typeof enhancer !== 'function' && typeof enhancer !== 'undefined') {
    throw new Error('Enhancer must be function or undefined');
  }

  if (typeof enhancer === 'undefined' && typeof initialState === 'function') {
    enhancer = initialState;
    initialState = undefined;
  }

  if (enhancer) {
    return enhancer(createStore)(reducer, initialState);
  }

  let state: AnyState = initialState ? initialState : reducer(initialState, { type: undefined });
  const callbacks = new Map();

  return {
    dispatch: (action: AnyState): void => {
      if (typeof action.type === 'undefined') {
        throw new Error('Actions may not have an undefined "type" property');
      }

      state = reducer(state, action);
      for (const listener of [...callbacks.values()]) {
        listener();
      }
    },
    getState: (): AnyState => state,
    subscribe: (listener: () => void): Unsubscribe => {
      if (typeof listener !== 'function') {
        throw new Error('Listener must be a function');
      }

      const i = callbacks.size;
      callbacks.set(i, listener);

      return () => callbacks.delete(i);
    }
  };
};

const applyMiddleware = (...middleware: any[]) => (
  storeCreator: (reducer: Reducer, state?: AnyState) => Store
) => (reducer: Reducer, state?: AnyState) => {
  const store = storeCreator(reducer, state);

  let dispatch = (_: any): any => {
    throw new Error('Dispatching during middleware setup');
  };

  const init = {
    getState: store.getState,
    dispatch: (action: AnyAction) => dispatch(action)
  };

  dispatch = middleware.map(m => m(init)).reduce((acc, g) => (m: any) => acc(g(m)))(store.dispatch);

  return { ...store, dispatch };
};

export { createStore, applyMiddleware };
