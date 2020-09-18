type t('a) = Promise.t('a);

let fromJs = Promise.Js.fromBsPromise;

let toJs = Promise.Js.toBsPromise;

let resultToJs = promise =>
  promise->Promise.Js.fromResult->Promise.Js.toBsPromise;

module Js = {
  let resolve = Js.Promise.resolve;
  let reject = Js.Promise.reject;

  let then_: (Js.Promise.t('a), 'a => Js.Promise.t('b)) => Js.Promise.t('b) =
    (promise, fn) => Js.Promise.then_(v => fn(v), promise);

  let catch:
    (Js.Promise.t('a), Js.Promise.error => Js.Promise.t('a)) =>
    Js.Promise.t('a) =
    (promise, fn) => Js.Promise.catch(e => fn(e), promise);
  let finalize: Js.Promise.t('a) => unit = ignore;
};
