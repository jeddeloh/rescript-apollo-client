// interface SubscriptionObserver<T> {
//     closed: boolean;
//     next(value: T): void;
//     error(errorValue: any): void;
//     complete(): void;
// }

// type Subscriber<T> = (observer: SubscriptionObserver<T>) => void | (() => void) | Subscription;

// interface ObservableLike<T> {
//     subscribe?: Subscriber<T>;
//     [Symbol.observable](): Observable<T> | ObservableLike<T>;
// }

module Subscription = {
  module Js_ = {
    // interface Subscription {
    //     closed: boolean;
    //     unsubscribe(): void;
    // }
    type t = {closed: bool}

    @send external unsubscribe: t => unit = "unsubscribe"
  }

  type t = {
    closed: bool,
    unsubscribe: unit => unit,
  }

  let fromJs: Js_.t => t = js => {closed: js.closed, unsubscribe: () => js->Js_.unsubscribe}
}

module Observer = {
  module Js_ = {
    // interface Observer<T> {
    //     start?(subscription: Subscription): any;
    //     next?(value: T): void;
    //     error?(errorValue: any): void;
    //     complete?(): void;
    // }
    type t<'t> = {
      start: option<Subscription.Js_.t => unit>,
      next: option<'t => unit>,
      error: option<Js.Json.t => unit>,
      complete: option<unit => unit>,
    }
  }

  type t<'t> = {
    start: option<Subscription.t => unit>,
    next: option<'t => unit>,
    error: option<Js.Json.t => unit>,
    complete: option<unit => unit>,
  }
}

module Observable = {
  module Js_ = {
    // declare class Observable<T> {
    //     constructor(subscriber: ZenObservable.Subscriber<T>)

    //     subscribe(observer: ZenObservable.Observer<T>): ZenObservable.Subscription;
    //     subscribe(onNext: (value: T) => void, onError?: (error: any) => void, onComplete?: () => void): ZenObservable.Subscription;

    //     [Symbol.observable](): Observable<T>;

    //     forEach(callback: (value: T) => void): Promise<void>;
    //     map<R>(callback: (value: T) => R): Observable<R>;
    //     filter(callback: (value: T) => boolean): Observable<T>;
    //     reduce(callback: (previousValue: T, currentValue: T) => T, initialValue?: T): Observable<T>;
    //     reduce<R>(callback: (previousValue: R, currentValue: T) => R, initialValue?: R): Observable<R>;
    //     flatMap<R>(callback: (value: T) => ZenObservable.ObservableLike<R>): Observable<R>;
    //     concat<R>(...observable: Array<Observable<R>>): Observable<R>;

    //     static from<R>(observable: Observable<R> | ZenObservable.ObservableLike<R> | ArrayLike<R>): Observable<R>;
    //     static of<R>(...items: R[]): Observable<R>;
    // }
    type t<'t, 'error>

    // <R>(callback: (value: T) => R): Observable<R>;
    @send external map: (t<'t, 'error>, 't => 'r) => t<'r, 'error> = "map"

    // (onNext: (value: T) => void, onError?: (error: any) => void, onComplete?: () => void): ZenObservable.Subscription;
    @send
    external subscribe: (
      t<'t, 'error>,
      ~onNext: 't => unit,
      ~onError: 'error => unit=?,
      ~onComplete: unit => unit=?,
      unit,
    ) => Subscription.Js_.t = "subscribe"

    // (observer: ZenObservable.Observer<T>): ZenObservable.Subscription;
    @send
    external subscribeWithObserver: (t<'t, 'error>, Observer.t<'t>) => Subscription.Js_.t =
      "subscribe"
  }

  // It's important that the rescript-wrapped version statisfy the Js_.t interface since they'll be used internally by Apollo
  type t<'t, 'error> = {
    subscribe: (
      ~onNext: 't => unit,
      ~onError: 'error => unit=?,
      ~onComplete: unit => unit=?,
      unit,
    ) => Subscription.t,
  }

  // This fromJs feels more like some kind of map over multiple callbacks
  let fromJs: Js_.t<'t, 'error> => t<'t, 'error> = t => {
    subscribe: (~onNext, ~onError=?, ~onComplete=?, ()) =>
      t->Js_.subscribe(~onNext, ~onError?, ~onComplete?, ())->Subscription.fromJs,
  }
}
