module ApolloLink = ApolloClient__Link_Core_ApolloLink
module GraphQLRequest = ApolloClient__Link_Core_Types.GraphQLRequest

module Js_ = {
  // export declare type ContextSetter = (operation: GraphQLRequest, prevContext: any) => Promise<any> | any;
  // export declare function setContext(setter: ContextSetter): ApolloLink;
  @module("@apollo/client/link/context")
  external setContext: (
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Json.t
  ) => ApolloLink.t = "setContext"

  @module("@apollo/client/link/context")
  external setContextAsync: (
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Promise.t<Js.Json.t>
  ) => ApolloLink.t = "setContext"

  type async = (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Promise.t<Js.Json.t>
}

let setContext = Js_.setContext

let setContextAsync: (
  (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Promise.t<Js.Json.t>
) => ApolloLink.t = fn => Js_.setContextAsync(fn)

// rescript-specific
module ContextLink = {
  let make = setContext
  let makeAsync = setContextAsync
}
