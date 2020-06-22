module Graphql = ApolloClient__Graphql;

external castStringAsDocumentNode: string => Graphql.documentNode =
  "%identity";

let useGuaranteedMemo1 = (f, dependency) => {
  let value = React.useRef(f());
  let previousDependency = React.useRef(dependency);

  if (dependency !== previousDependency.current) {
    value.current = f();
    previousDependency.current = dependency;
  };

  value.current;
};