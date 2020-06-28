module ApolloLink = ApolloClient__Link_Core_ApolloLink;
module GraphQLRequest = ApolloClient__Link_Core_Types.GraphQLRequest;

// export declare type ContextSetter = (operation: GraphQLRequest, prevContext: any) => Promise<any> | any;
// export declare function setContext(setter: ContextSetter): ApolloLink;
[@bs.module "@apollo/link-context"]
external setContext:
  ((~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) => Js.Json.t) =>
  ApolloLink.t =
  "setContext";

[@bs.module "@apollo/link-context"]
external setContextAsync:
  (
    (~operation: GraphQLRequest.t, ~prevContext: Js.Json.t) =>
    Js.Promise.t(Js.Json.t)
  ) =>
  ApolloLink.t =
  "setContext";

// reason-specific
module ContextLink = {
  let make = setContext;
  let makeAsync = setContextAsync;
};
