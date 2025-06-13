module ApolloLink = ApolloClient__Link_Core_ApolloLink
module Graphql = ApolloClient__Graphql

module WebSocketLink = {
  module ClientOptions = ApolloClient__GraphqlWs.ClientOptions
  module Client = ApolloClient__GraphqlWs.Client

  module Js_ = {
    // export class GraphQLWsLink extends ApolloLink {
    //     constructor(public readonly client: Client);
    //     request(operation: Operation): Observable<FetchResult>;
    // }
    @module("@apollo/client/link/subscriptions") @new
    external make: Client.t => ApolloLink.Js_.t = "GraphQLWsLink"
  }

  let make: ClientOptions.t => ApolloLink.t = options => Js_.make(Client.createClient(options))
}
