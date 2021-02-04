let graphqlEndpoint = "localhost:4000"

let headers = {"high": "five"}

let httpLink = ApolloClient.Link.HttpLink.make(
  ~uri=_ => "http://" ++ graphqlEndpoint,
  ~headers=Obj.magic(headers),
  (),
)

let wsLink = {
  open ApolloClient.Link.WebSocketLink
  make(
    ~uri="ws://" ++ graphqlEndpoint,
    ~options=ClientOptions.make(
      ~connectionParams=ConnectionParams(Obj.magic({"headers": headers})),
      ~reconnect=true,
      (),
    ),
    (),
  )
}

let terminatingLink = ApolloClient.Link.split(~test=({query}) => {
  let definition = ApolloClient.Utilities.getOperationDefinition(query)
  switch definition {
  | Some({kind, operation}) => kind === "OperationDefinition" && operation === "subscription"
  | None => false
  }
}, ~whenTrue=wsLink, ~whenFalse=httpLink)

let client = {
  open ApolloClient
  make(
    ~cache=Cache.InMemoryCache.make(),
    ~connectToDevTools=true,
    ~defaultOptions=DefaultOptions.make(
      ~mutate=DefaultMutateOptions.make(~awaitRefetchQueries=true, ()),
      (),
    ),
    ~link=terminatingLink,
    (),
  )
}
