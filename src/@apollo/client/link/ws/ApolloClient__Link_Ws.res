module ApolloLink = ApolloClient__Link_Core_ApolloLink
module Graphql = ApolloClient__Graphql

module WebSocketLink = {
  module ClientOptions = ApolloClient__SubscriptionsTransportWs.ClientOptions
  module SubscriptionClient = ApolloClient__SubscriptionsTransportWs.SubscriptionClient

  module Configuration = {
    module Js_ = {
      // export declare namespace WebSocketLink {
      //     interface Configuration {
      //         uri: string;
      //         options?: ClientOptions;
      //         webSocketImpl?: any;
      //     }
      // }
      type any
      type t = {
        uri: string,
        options: option<ClientOptions.Js_.t>,
        webSocketImpl: option<any>,
      }
    }

    type t = Js_.t
  }

  module Js_ = {
    // export declare class WebSocketLink extends ApolloLink {
    //     private subscriptionClient;
    //     constructor(paramsOrClient: WebSocketLink.Configuration | SubscriptionClient);
    //     request(operation: Operation): Observable<FetchResult> | null;
    // }
    @module("@apollo/client/link/ws") @new
    external make: @unwrap
    [
      | #Configuration(Configuration.Js_.t)
      | #SubscriptionClient(SubscriptionClient.t)
    ] => ApolloLink.Js_.t = "WebSocketLink"
  }

  type webSocketImpl = Configuration.Js_.any

  let make: (
    ~uri: string,
    ~options: ClientOptions.t=?,
    ~webSocketImpl: webSocketImpl=?,
    unit,
  ) => ApolloLink.t = (~uri, ~options=?, ~webSocketImpl=?, ()) =>
    Js_.make(
      #Configuration({
        uri: uri,
        options: options->Belt.Option.map(ClientOptions.toJs),
        webSocketImpl: webSocketImpl,
      }),
    )

  let makeWithSubscriptionClient: SubscriptionClient.t => ApolloLink.t = subscriptionClient =>
    Js_.make(#SubscriptionClient(subscriptionClient))
}
