module Graphql = ApolloClient__Graphql

module type Fragment = {
  // This type is determined by the `-template-tag-return-type` ppx flag
  let query: Graphql.documentNode

  module Raw: {
    type t
  }
  type t

  let parse: Raw.t => t
  let serialize: t => Raw.t
}

module type Operation = {
  // This type is determined by the `-template-tag-return-type` ppx flag
  let query: Graphql.documentNode

  module Raw: {
    type t
    type t_variables
  }
  type t
  type t_variables

  let parse: Raw.t => t
  let serialize: t => Raw.t
  let serializeVariables: t_variables => Raw.t_variables
}

module type OperationNoRequiredVars = {
  include Operation
  let makeDefaultVariables: unit => t_variables
}

type parseError = {
  value: Js.Json.t,
  error: Js.Exn.t,
}

type parseResult<'data> = result<'data, parseError>

type safeParse<'data, 'jsData> = 'jsData => parseResult<'data>
