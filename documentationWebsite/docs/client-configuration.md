---
id: client-configuration
title: Create a Client
sidebar_label: Create a Client
---

Let's initialize an ApolloClient instance. You'll need to provide it the URL of a running GraphQL server, such as the [Star Wars API](https://graphql.org/swapi-graphql).

First, we'll create a file `Apollo.res` to group all our Apollo stuff.

```reason title="Apollo.res"
let client = {
  open ApolloClient
  make(
    ~cache=Cache.InMemoryCache.make(),
    // I would turn this off in production
    ~connectToDevTools=true,
    ~uri="https://graphql.org/swapi-graphql"
    (),
  )
}
```

Now connect the client to React.

```reason
module App = {
  <ApolloClient.React.ApolloProvider client=Apollo.client>
    <div>
      <h2>My first Apollo app 🚀</h2>
    </div>
  </ApolloClient.React.ApolloProvider>
}

ReactDOMRe.renderToElementWithId(<App />, "root")
```

That's it! Our client is ready to start fetching data.

### Advanced (Typical) Configuration

Often, you'll want to take advantage of realtime data (subcriptions) and auth, so we'll go a little more in depth here. Feel free to skip this section and return to it when you have a need.

```reason title="Apollo.res"
let graphqlEndpoint = "graphql.org/swapi-graphql"

let headers = {"Authorization": "There are a bunch of ways to get a token in here"}

// This is the basic http link
let httpLink = ApolloClient.Link.HttpLink.make(
  ~uri=_ => "https://" ++ graphqlEndpoint,
  // Auth headers
  ~headers=Obj.magic(headers),
  (),
)

// This is a link to handle websockets (used by subscriptions)
let wsLink = {
  open ApolloClient.Link.WebSocketLink
  make(
    ~uri="ws://" ++ graphqlEndpoint,
    ~options=ClientOptions.make(
      // Auth headers
      ~connectionParams=ConnectionParams(Obj.magic({"headers": headers})),
      ~reconnect=true,
      (),
    ),
    (),
  )
}

// This is a splitter that intelligently routes requests through http or websocket depending on type
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
      ~mutate=DefaultMutateOptions.make(~awaitRefetchQueries=true, ~errorPolicy=All, ()),
      ~query=DefaultQueryOptions.make(~fetchPolicy=NetworkOnly, ~errorPolicy=All, ()),
      ~watchQuery=DefaultWatchQueryOptions.make(~fetchPolicy=NetworkOnly, ~errorPolicy=All, ()),
      (),
    ),
    ~link=terminatingLink,
    (),
  )
}
```
