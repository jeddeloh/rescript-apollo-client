let graphqlEndpoint = "api.graph.cool/simple/v1/cjdgba1jw4ggk0185ig4bhpsn";

let headers = {"high": "five"};

let httpLink =
  Apollo.Client.HttpLink.make(
    ~uri=_ => "https://" ++ graphqlEndpoint,
    ~credentials="include",
    ~headers=Obj.magic(headers),
    (),
  );

let wsLink =
  Apollo.LinkWs.(
    WebSocketLink.make(
      ~uri="wss://" ++ graphqlEndpoint,
      ~options=
        ClientOptions.make(
          ~connectionParams=
            ConnectionParams(Obj.magic({"headers": headers})),
          ~reconnect=true,
          (),
        ),
      (),
    )
  );

let terminatingLink =
  Apollo.Client.split(
    ~test=
      ({query}) => {
        let definition =
          Apollo.Client.Utilities.getOperationDefinition(query);
        switch (definition) {
        | Some({kind, operation}) =>
          kind === "OperationDefinition" && operation === "subscription"
        | None => false
        };
      },
    ~whenTrue=httpLink,
    ~whenFalse=wsLink,
  );

let instance =
  Apollo.Client.ApolloClient.(
    make(
      ~cache=Apollo.Client.InMemoryCache.make(),
      ~connectToDevTools=true,
      ~defaultOptions=
        DefaultOptions.make(
          ~mutate=
            DefaultMutationOptions.make(
              ~awaitRefetchQueries=true,
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~query=
            DefaultQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          ~watchQuery=
            DefaultWatchQueryOptions.make(
              ~fetchPolicy=NetworkOnly,
              ~errorPolicy=All,
              (),
            ),
          (),
        ),
      ~link=terminatingLink,
      (),
    )
  );