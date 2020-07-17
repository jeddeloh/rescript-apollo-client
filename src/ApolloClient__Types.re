module Graphql = ApolloClient__Graphql;

module type Fragment = {
  // This type is determined by the `-template-tag-return-type` ppx flag
  let query: Graphql.documentNode;

  module Raw: {type t;};
  type t;

  let parse: Raw.t => t;
  let serialize: t => Raw.t;
};

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
