module ReasonPromise = {
  /**
   Promises of result('a, 'e) coming from `reason-apollo-client` will never reject.
   It's safe to simply cast these to a Promise.t(result('a, 'e)).
   See https://github.com/aantron/promise#Bindings
   */
  external fromJs:
    Js.Promise.t(result('a, 'e)) => Promise.t(result('a, 'e)) =
    "%identity";
};

/**
 This library leverages records heavily, which means T-first promise functions
 can help us a lot by inferring the type automatically which means we don't have
 to annotate it.

 These are T-first Js promise helpers for my own sanity in examples. Please see the
 promise chaining examples for alternatives.
 */
module Promise = {
  /**
   Promises in reason-apollo-client never reject, so we're not using catch here.
   Instead we'd add a global uncaught promise handler to report any situations where
   what should be impossible is ocurring.
   */
  let then_ = (promise, f) => Js.Promise.then_(f, promise);
  let ignore: Js.Promise.t(_) => unit = ignore;
};
