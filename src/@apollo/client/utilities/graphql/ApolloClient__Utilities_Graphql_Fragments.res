module FragmentDefinitionNode = ApolloClient__Graphql.Language.Ast.FragmentDefinitionNode

module FragmentMap = {
  module Js_ = {
    type t = Js.Dict.t<FragmentDefinitionNode.t>
  }

  type t = Js_.t
}
