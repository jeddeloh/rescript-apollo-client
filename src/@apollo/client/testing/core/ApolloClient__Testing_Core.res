module Link = ApolloClient__Link_Core_ApolloLink
module Types = ApolloClient__Testing_Types

@new @module("@apollo/client/testing")
external mockLink: (~mocks: array<Types.mock<'jsVariables>>, ~addTypename: bool) => Link.t =
  "MockLink"
