module ApolloLink = ApolloClient__Link_Core_ApolloLink
module HttpOptions = ApolloClient__Link_Http_SelectHttpOptionsAndBody.HttpOptions

module Js_ = {
  @module("@apollo/client")
  external createHttpLink: HttpOptions.Js_.t => ApolloLink.Js_.t = "createHttpLink"
}

let createHttpLink: HttpOptions.t => ApolloLink.t = Js_.createHttpLink
