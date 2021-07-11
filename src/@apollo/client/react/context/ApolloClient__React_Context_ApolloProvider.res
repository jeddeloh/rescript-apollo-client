module ApolloClient = ApolloClient__Core_ApolloClient

// export interface ApolloProviderProps<TCache> {
//     client: ApolloClient<TCache>;
//     children: React.ReactNode | React.ReactNode[] | null;
// }
// export declare const ApolloProvider: React.FC<ApolloProviderProps<any>>;
@module("@apollo/client") @react.component
external make: (~client: ApolloClient.t, ~children: React.element) => React.element =
  "ApolloProvider"
