let someLocalState = ApolloClient.Cache.makeVar("a string");

let cache =
  ApolloClient.Cache.InMemoryCache.(
    make(
      ~typePolicies=[|
        (
          "Query",
          TypePolicy.make(
            ~fields=[|
              (
                "someLocalStateField",
                FieldReadFunction((_existing, _options) => someLocalState()),
              ),
            |],
            (),
          ),
        ),
      |],
      (),
    )
  );
