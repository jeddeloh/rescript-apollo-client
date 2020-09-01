module Graphql = ApolloClient__Graphql;
module Types = ApolloClient__Types;

[@bs.new] external makeError: string => Js.Exn.t = "Error";

external asJson: 'any => Js.Json.t = "%identity";

let safeParse: ('jsData => 'data) => Types.safeParse('jsData, 'data) =
  (parse, jsData) =>
    switch (parse(jsData)) {
    | data => Data(data)
    | exception _ => ParseError({data: jsData->asJson})
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
