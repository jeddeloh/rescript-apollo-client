> WARNING: This library is currently highly unstable and untested. It is mostly "complete", however, and is a superset of `reason-apollo` and `reason-apollo-hooks` functionality

# Reason Apollo Client

## Installation

### 1. Install `graphql-ppx`

We rely on Graphql-ppx for typesafe GraphQL operations and fragments in ReasonML. [Go to the official documentation](https://beta.graphql-ppx.com) for installation instructions.

You should now have a `graphql_schema.json` in your project somewhere. Make sure it's always up-to-date!

### 2. Install Apollo Client and Optional Dependencies

```sh
yarn add @apollo/client @jeddeloh/reason-apollo-client@dev
# optional
yarn add @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

or

```sh
npm install @apollo/client @jeddeloh/reason-apollo-client@dev
# optional
npm install @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

### 3. Apollo-Specific `graphql-ppx` Configuration

Add the following to `bs-dependencies`, `graphql`, and `ppx-flags` in your `bsconfig.json`

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
-     // don't enter this yet, but you'll need it soon
-     "-template-tag-import=gql",
-     "-template-tag-location=@apollo/client"
    ]
  ],
  "bs-dependencies: [
    "@reasonml-community/graphql-ppx"
+   "@jeddeloh/reason-apollo-client"
  ]
}
```

- `"apollo-mode"` automaticaly sprinkles `__typename` throughout our operation definitions
- `"-template-tag-*"` is how we tell `graphql-ppx` to wrap every operation with `gql`
- `"extend-*"` allows `reason-apollo-client` to automatically decorate the generated modules with Apollo-specific things like the correct hook for that operation!

## Usage

See the [Examples/](https://github.com/jeddeloh/reason-apollo-client/tree/master/EXAMPLES) directory for now, but in general the appropriate hook is exposed as a `use` function on the graphql module. If variables are required, they are the last argument:

```js

module Query = [%graphql {|
  query Example {
    users {
      id
      name
    }
  }
|}];

[@react.component]
let make = () => {
  switch (Query.use()) {
    | {data: Some({users})} =>
    ...
  }
}
```

## Bindings to Javascript Packages

Contains partial bindings to the following:

- `@apollo/client`
- `@apollo/link-context`
- `@apollo/link-error`
- `@apollo/link-ws`
- `graphql`
- `subscriptions-transport-ws`
- `zen-observable`

While we strive to provide ergonomics that are intuitive and "reasonable", we do expose the 1:1 mapping to the javascript module structures if that is your preference. For instance, if you're looking in the Apollo docs and see `import { setContext } from '@apollo/link-context'` and you'd prefer to be able to access with the same filepath, you could do it like so:

```js
module Apollo = {
  include ApolloClient.Bindings;
};

// `import { setContext } from '@apollo/link-context'`
let setContext = Apollo.LinkContext.setContext;
```
