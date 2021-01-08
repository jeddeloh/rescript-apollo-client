let cache = {
  open ApolloClient.Cache.InMemoryCache
  make(
    ~typePolicies=[
      (
        "Query",
        TypePolicy.make(
          ~fields=[("somefieldName", RelayStylePagination(KeySpecifier(["key1", "key2"])))],
          (),
        ),
      ),
    ],
    (),
  )
}
