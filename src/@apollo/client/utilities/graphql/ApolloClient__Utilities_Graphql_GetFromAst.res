module Graphql = ApolloClient__Graphql

@module("@apollo/client/utilities")
external getOperationDefinition: Graphql.documentNode => option<
  Graphql.Language.Ast.OperationDefinitionNode.t,
> = "getOperationDefinition"
