---
id: installation
title: Installation
sidebar_label: Installation
---

### 1. `graphql-ppx`

We rely on Graphql-ppx for typesafe GraphQL operations and fragments in ReasonML. [Go to the official documentation](https://beta.graphql-ppx.com) for installation instructions.

You should now have a `graphql_schema.json` in your project somewhere. Make sure it's always up-to-date!

### 2. Apollo Client

```sh
npm install rescript-apollo-client @apollo/client
```

### 3. Apollo-Specific `graphql-ppx` Configuration

Add the following under `bs-dependencies` and `graphql`, in your `bsconfig.json`

```diff
{
  "graphql": {
+   "apolloMode": true,
+   "extendMutation": "ApolloClient.GraphQL_PPX.ExtendMutation",
+   "extendQuery": "ApolloClient.GraphQL_PPX.ExtendQuery",
+   "extendSubscription": "ApolloClient.GraphQL_PPX.ExtendSubscription",
+   "templateTagReturnType": "ApolloClient.GraphQL_PPX.templateTagReturnType",
+   "templateTagImport": "gql",
+   "templateTagLocation": "@apollo/client"
  },
  "ppx-flags": ["@reasonml-community/graphql-ppx/ppx"],
  "bs-dependencies: [
    "@reasonml-community/graphql-ppx"
+   "rescript-apollo-client"
  ]
}
```

- `"apolloMode"` automaticaly sprinkles `__typename` throughout our operation and fragment definitions
- `"templateTag*"` is how we tell `graphql-ppx` to wrap every operation with `gql`
- `"extend*"` allows `rescript-apollo-client` to automatically decorate the generated modules with Apollo-specific things like the correct hook for that operation!
