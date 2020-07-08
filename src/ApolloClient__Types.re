module Graphql = ApolloClient__Graphql;

type parse('raw_t, 't) = 'raw_t => 't;
type serialize('t, 'raw_t) = 't => 'raw_t;
type query = string;

type graphqlDefinition('t, 'raw_t) = (
  parse('raw_t, 't),
  query,
  serialize('t, 'raw_t),
);

module type Operation = {
  // This type is determined by the `-template-tag-return-type` ppx flag
  let query: Graphql.documentNode;

  module Raw: {
    type t;
    type t_variables;
  };
  type t;

  let parse: Raw.t => t;
  let serialize: t => Raw.t;
};

module type OperationNoRequiredVars = {
  include Operation;
  let makeDefaultVariables: unit => Raw.t_variables;
};
