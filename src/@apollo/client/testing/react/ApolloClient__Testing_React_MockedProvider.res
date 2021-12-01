module InMemoryCache = ApolloClient__Cache_InMemory_InMemoryCache
module ApolloClient = ApolloClient__Core_ApolloClient
module ApolloProvider = ApolloClient__React_Context_ApolloProvider
module Core = ApolloClient__Testing_Core
module Types = ApolloClient__Testing_Types

// export interface MockedProviderProps<TSerializedCache = {}> {
//   mocks?: ReadonlyArray<MockedResponse>;
//   addTypename?: boolean;
//   defaultOptions?: DefaultOptions;
//   cache?: ApolloCache<TSerializedCache>;
//   resolvers?: Resolvers;
//   childProps?: object;
//   children?: any;
//   link?: ApolloLink;
// }

/* Then making an ApolloClient in Rescript, additional wrapper methods (e.g. `rescript_query`)
 * are created for the underlying javascript methods. So for the client to be set up correctly,
 * we need to do so by calling the rescript method.
 */
@react.component
let make = (
  ~addTypename=true,
  ~cache=?,
  ~childProps=?,
  ~children,
  ~defaultOptions=?,
  ~link=?,
  ~mocks: array<Types.mock<'jsVariables>>,
  ~resolvers=?,
) => {
  let client = React.useRef(
    ApolloClient.make(
      ~cache=cache->Belt.Option.getWithDefault(InMemoryCache.make(~addTypename, ())),
      ~defaultOptions?,
      ~link=link->Belt.Option.getWithDefault(Core.mockLink(~mocks, ~addTypename)),
      ~resolvers?,
      (),
    ),
  )

  React.useEffect0(() => {
    Some(client.current.stop)
  })

  <ApolloProvider client=client.current>
    {React.cloneElement(
      React.Children.only(children),
      childProps->Belt.Option.mapWithDefault(Js.Obj.empty(), props =>
        Js.Obj.assign(props, Js.Obj.empty())
      ),
    )}
  </ApolloProvider>
}
