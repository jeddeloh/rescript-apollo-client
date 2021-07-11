module ApolloLink = ApolloClient__Link_Core_ApolloLink
module HttpOptions = ApolloClient__Link_Http_SelectHttpOptionsAndBody.HttpOptions
module UriFunction = ApolloClient__Link_Http_SelectHttpOptionsAndBody.UriFunction

module Js_ = {
  // export declare class HttpLink extends ApolloLink {
  //     options: HttpOptions;
  //     requester: RequestHandler;
  //     constructor(options?: HttpOptions);
  // }
  @module("@apollo/client") @new
  external make: HttpOptions.Js_.t => ApolloLink.Js_.t = "HttpLink"
}

let make: (
  ~uri: UriFunction.t=?,
  ~includeExtensions: bool=?,
  ~fetch: HttpOptions.Js_.t_fetch=?,
  ~headers: Js.Json.t=?,
  ~credentials: string=?,
  ~fetchOptions: Js.Json.t=?,
  ~useGETForQueries: bool=?,
  unit,
) => ApolloLink.t = (
  ~uri=?,
  ~includeExtensions=?,
  ~fetch=?,
  ~headers=?,
  ~credentials=?,
  ~fetchOptions=?,
  ~useGETForQueries=?,
  (),
) =>
  Js_.make({
    uri: uri,
    includeExtensions: includeExtensions,
    fetch: fetch,
    headers: headers,
    credentials: credentials,
    fetchOptions: fetchOptions,
    useGETForQueries: useGETForQueries,
  })
