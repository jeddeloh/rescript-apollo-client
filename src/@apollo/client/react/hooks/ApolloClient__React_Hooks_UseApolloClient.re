module ApolloClient = ApolloClient__ApolloClient;

[@bs.module "@apollo/client"]
external useApolloClient: unit => ApolloClient.t = "useApolloClient";
