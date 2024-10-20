let graphqlEndpoint = "localhost:4000/graphql"

let headers = {"high": "five"}

let httpLink = ApolloClient.Link.HttpLink.make(
  ~uri=_ => "http://" ++ graphqlEndpoint,
  ~headers=Obj.magic(headers),
  (),
)

let _retryLink = ApolloClient.Link.RetryLink.make(
  ~attempts=RetryFunction(async (~count, ~operation as _, ~error as _) => count < 3),
  ~delay=DelayFunction((~count as _, ~operation as _, ~error as _) => 1_000),
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

client.onClearStore(~cb=async () => {
  Js.log("store cleared")
})

client.onResetStore(~cb=async () => {
  Js.log("store reset")
})

let _ = client.clearStore()
let _ = client.resetStore()
