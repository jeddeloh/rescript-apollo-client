module ApolloError = ApolloClient__Errors_ApolloError;
module Graphql = ApolloClient__Graphql;
module Types = ApolloClient__Types;

[@bs.new] external makeError: string => Js.Exn.t = "Error";

[@unboxed]
type any =
  | Any('a): any;

let ensureError: any => Js.Exn.t = [%bs.raw
  {|
  function (unknown) {
    if (unknown instanceof Error) {
      return unknown;
    } else {
      unknown = unknown || {};
      const message = unknown.message;
      const errorMessage = unknown.errorMessage;
      const keys = Object.keys(unknown);
      const error = new Error(message || errorMessage || "[Non-error exception with keys: " + keys.join(", ") + "]");

      keys.forEach(function(key) {
        error[key] = unknown[key];
      });

      return error;
    }
  }
  |}
];

external asJson: 'any => Js.Json.t = "%identity";

let safeParse: ('jsData => 'data) => Types.safeParse('data, 'jsData) =
  (parse, jsData) =>
    switch (parse(jsData)) {
    | data => Ok(data)
    | exception (Js.Exn.Error(error)) =>
      Error({value: jsData->asJson, error})
    };

let safeParseAndLiftToCommonResultProps:
  (
    ~jsData: option('jsData),
    ~graphQLErrors: array(Graphql.Error.GraphQLError.t)=?,
    ~apolloError: ApolloError.t=?,
    Types.safeParse('data, 'jsData)
  ) =>
  (option('data), option(ApolloError.t)) =
  (~jsData, ~graphQLErrors=?, ~apolloError=?, safeParse) => {
    let existingError =
      switch (apolloError, graphQLErrors) {
      | (Some(_), _) => apolloError
      | (_, Some(graphQLErrors)) =>
        Some(ApolloError.make(~graphQLErrors, ()))
      | (None, None) => None
      };

    switch (jsData->Belt.Option.map(jsData => safeParse(jsData))) {
    | Some(Error(parseError)) =>
      // Be careful we do not overwrite an existing error with a ParseError
      existingError->Belt.Option.isSome
        ? (None, existingError)
        : (
          None,
          Some(
            ApolloError.make(
              ~networkError=ParseError(parseError),
              ~graphQLErrors?,
              (),
            ),
          ),
        )
    | Some(Ok(data)) => (Some(data), existingError)
    | None => (None, existingError)
    };
  };

let useGuaranteedMemo1 = (f, dependency) => {
  let value = React.useRef(f());
  let previousDependency = React.useRef(dependency);

  if (dependency !== previousDependency.current) {
    value.current = f();
    previousDependency.current = dependency;
  };

  value.current;
};

external identity: 'a => 'a = "%identity";
