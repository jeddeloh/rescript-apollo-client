// let toReasonPromise: Js.Promise.t(result('a, 'e)) => Promise.t(result('a, 'e)) = ;

let toReasonPromise = promise =>
  promise
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.flatMap(result =>
      switch (result) {
      | Ok(result) => Promise.resolved(result)
      | Error(error) =>
        Js.Exn.raiseError(
          "Impossible: "
          ++ error
             ->Js.Json.stringifyAny
             ->Belt.Option.getWithDefault("[couldn't stringify]"),
        )
      }
    );
