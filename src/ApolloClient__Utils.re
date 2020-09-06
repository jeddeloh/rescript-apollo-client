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
      const error = new Error(message || errorMessage || "[no message]");

      Object.keys(unknown).forEach(function(key) {
        error[key] = JSON.stringify(unknown[key]);
      });

      return error
    }
  }
  |}
];

external asJson: 'any => Js.Json.t = "%identity";

let safeParse: ('jsData => 'data) => Types.safeParse('jsData, 'data) =
  (parse, jsData) =>
    switch (parse(jsData)) {
    | data => Data(data)
    | exception _ => ParseError({data: jsData->asJson})
    };

let safeParseWithCommonProps:
  (
    ~jsData: option('jsData),
    ~graphQLErrors: array(Graphql.Error.GraphQLError.t)=?,
    ~apolloError: ApolloError.t=?,
    'jsData => 'data
  ) =>
  (option('data), option(ApolloError.t)) =
  (~jsData, ~graphQLErrors=?, ~apolloError=?, parse) => {
    let existingError =
      switch (apolloError, graphQLErrors) {
      | (Some(_), _) => apolloError
      | (_, Some(graphQLErrors)) =>
        Some(ApolloError.make(~graphQLErrors, ()))
      | (None, None) => None
      };
    switch (jsData->Belt.Option.map(jsData => safeParse(parse, jsData))) {
    | Some(ParseError({data})) => (
        None,
        Some(
          ApolloError.make(
            ~networkError=ParseError({data: data}),
            ~graphQLErrors?,
            (),
          ),
        ),
      )
    | Some(Data(data)) => (Some(data), existingError)
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
