module GraphQLError = ApolloClient__Graphql_Error_GraphQLError

module ExecutionResult = {
  module Js_ = {
    type t<'tData> = {
      errors: option<GraphQLError.t>,
      data: option<'tData>,
    }
  }

  // I don't think we want to parse this?
  type t<'tData> = Js_.t<'tData>
}
