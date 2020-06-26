> WARNING: This library is currently highly unstable and untested. It is mostly "complete", however, and is a superset of `reason-apollo` and `reason-apollo-hooks` functionality

# ReasonML / BuckleScript bindings for the Apollo Client ecosystem

## Installation

### 1 - Install `graphql-ppx`

We rely on Graphql-ppx for typesafe GraphQL operations and fragments in ReasonML. [Go to the official documentation](https://beta.graphql-ppx.com) for installation instructions.

### 2 - Install Apollo Client and Optional Dependencies

```sh
yarn add @apollo/client <tbd>
# optional
yarn add @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

or

```sh
npm install @apollo/client <tbd>
# optional
npm install @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

### 3 - Apollo-Specific `graphql-ppx` Configuration

Add the following to `ppx-flags` and `bs-dependencies` and `graphql` in your `bsconfig.json`

```diff
{
  "graphql": {
+   "apollo-mode": true,
+   "extend-mutation": "ApolloClient.GraphQL_PPX.ExtendMutation",
+   "extend-mutation-no-required-variables": "ApolloClient.GraphQL_PPX.ExtendMutationNoRequiredVariables",
+   "extend-query": "ApolloClient.GraphQL_PPX.ExtendQuery",
+   "extend-query-no-required-variables": "ApolloClient.GraphQL_PPX.ExtendQueryNoRequiredVariables",
+   "extend-subscription": "ApolloClient.GraphQL_PPX.ExtendSubscription",
+   "extend-subscription-no-required-variables": "ApolloClient.GraphQL_PPX.ExtendSubscriptionNoRequiredVariables"
  },
  "ppx-flags": [
    [
      "@reasonml-community/graphql-ppx/ppx",
+     "-template-tag-import=gql",
+     "-template-tag-location=@apollo/client"
    ]
  ],
  "bs-dependencies: [
    "@reasonml-community/graphql-ppx"
+   "<tbd>"
  ]
}
```

`"apollo-mode"` automaticaly adds `__typename` where appropriate, `"-template-tag-*"` is how we tell `graphql-ppx` to wrap all our query strings with `gql`, and finally the `"extend-*"` allow us to automatically decorate the modules that are generated with Apollo-specific things like the correct hook for the operation!

## Bindings to Javascript Packages

Contains partial bindings to the following:

- `@apollo/client`
- `@apollo/link-context`
- `@apollo/link-error`
- `@apollo/link-ws`
- `graphql`
- `subscriptions-transport-ws`
- `zen-observable`

While we strive to provide ergonomics that are "reasonable", we do expose the 1:1 bindings if you find it easier to use the Apollo Docs as reference

```js
module Apollo = {
  include Apollo.Bindings;
};

// import { getOperationDefinition } from '@apollo/client/utilities'
let getOperationDefinition = Apollo.Client.Utilities.getOperationDefinition;
```
