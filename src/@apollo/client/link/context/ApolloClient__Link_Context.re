module ApolloLink = ApolloClient__Link_Core_ApolloLink;
module GraphQLRequest = ApolloClient__Link_Core_Types.GraphQLRequest;

module Js_ = {
  // export declare type ContextSetter = (operation: GraphQLRequest, prevContext: any) => Promise<any> | any;
  // export declare function setContext(setter: ContextSetter): ApolloLink;
  [@bs.module "@apollo/client/link/context"]
  external setContext:
    ((~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Json.t) =>
    ApolloLink.t =
    "setContext";

  [@bs.module "@apollo/client/link/context"]
  external setContextAsync:
    (
      (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) =>
      Js.Promise.t(Js.Json.t)
    ) =>
    ApolloLink.t =
    "setContext";

  type asyncJs =
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) =>
    Js.Promise.t(Js.Json.t);
  type async =
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) =>
    Promise.t(Js.Json.t);
  external safeCastAsync: async => asyncJs = "%identity";
};

let setContext = Js_.setContext;

let setContextAsync:
  (
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) =>
    Promise.t(Js.Json.t)
  ) =>
  ApolloLink.t =
  fn => Js_.setContextAsync(Js_.safeCastAsync(fn));

// reason-specific
module ContextLink = {
  let make = setContext;
  let makeAsync = setContextAsync;
};
