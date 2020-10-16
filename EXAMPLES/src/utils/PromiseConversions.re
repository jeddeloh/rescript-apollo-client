/**
 Promises of result returned by `res-apollo-client` will never be rejected, so we directly cast to Promise.t
 https://github.com/aantron/promise#Bindings
 */
external toReasonPromise:
  Js.Promise.t(result('a, 'e)) => Promise.t(result('a, 'e)) =
  "%identity";
