module Graphql = ApolloClient__Graphql
module ApolloError = ApolloClient__Errors_ApolloError
module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache

type rec request<'jsVariables> = {
  query: Graphql.documentNode,
  variables: 'jsVariables,
}

type result

type mock<'jsVariables> = {
  request: request<'jsVariables>,
  result: result,
}

type queryResult = {
  data: Js.Nullable.t<Js.Json.t>,
  error: Js.Nullable.t<ApolloError.t>,
  loading: bool,
}

external mockResult: queryResult => result = "%identity"

let makeResult = (
  ~data: option<'jsData>=?,
  ~error: option<ApolloError.t>=?,
  ~loading=false,
  toJson: 'jsData => Js.Json.t,
): result => {
  let queryResult = {
    data: data->Belt.Option.mapWithDefault(Js.Nullable.null, data =>
      data->toJson->Js.Nullable.return
    ),
    error: error->Belt.Option.mapWithDefault(Js.Nullable.null, Js.Nullable.return),
    loading: loading,
  }

  mockResult(queryResult)
}

module MockedProvider = {
  @react.component @module("@apollo/client/testing")
  external make: (
    ~mocks: array<mock<'jsVariables>>,
    ~addTypeName: bool=?,
    ~cache: InMemoryCache.t=?,
    ~children: React.element,
  ) => React.element = "MockedProvider"
}
