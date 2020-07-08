> ⚠️ **WARNING:** This library is currently highly unstable and not fully tested. However, it is mostly "complete" and includes all `reason-apollo` and `reason-apollo-hooks` functionality

<p align="center">
    <img src="assets/logo-v1.png" alt="Logo">
  	<br><br>
    ReasonML / BuckleScript bindings for the Apollo Client ecosystem
</p>

<p align="center">
  <a href="https://www.npmjs.com/package/@jeddeloh/reason-apollo-client">
    <img src="https://badge.fury.io/js/%40jeddeloh%2Freason-apollo-client.svg" alt="npm version" />
  </a>
</p>

<p align="center">
  <a href="#installation">Installation</a> •
  <a href="#usage">Usage</a> •
  <a href="EXAMPLES/src">Examples</a> •
  <a href="#bindings-to-javascript-packages"> JavaScript</a> •
  <a href="#contributing">Contributing</a>
</p>

## Installation

### 1. `graphql-ppx`

We rely on Graphql-ppx for typesafe GraphQL operations and fragments in ReasonML. [Go to the official documentation](https://beta.graphql-ppx.com) for installation instructions.

You should now have a `graphql_schema.json` in your project somewhere. Make sure it's always up-to-date!

### 2. `@apollo/client` and Optional Dependencies

```sh
yarn add @jeddeloh/reason-apollo-client @apollo/client
# optional
yarn add @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

or

```sh
npm install @jeddeloh/reason-apollo-client @apollo/client
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
+     "-fragment-in-query=include",
+     "-template-tag-return-type=ApolloClient.GraphQL_PPX.templateTagReturnType",
+     "-template-tag-import=gql",
+     "-template-tag-location=@apollo/client"
    ]
  ],
  "bs-dependencies: [
    "@reasonml-community/graphql-ppx"
+   "@jeddeloh/reason-apollo-client"
  ]
}
```

- `"apollo-mode"` automaticaly sprinkles `__typename` throughout our operation and fragment definitions
- `"-template-tag-*"` is how we tell `graphql-ppx` to wrap every operation with `gql`
- `"extend-*"` allows `reason-apollo-client` to automatically decorate the generated modules with Apollo-specific things like the correct hook for that operation!

## Usage

The [EXAMPLES/](https://github.com/jeddeloh/reason-apollo-client/tree/master/EXAMPLES) directory is the best documentation at the moment, but in short, the appropriate hook is exposed as a `use` function on the graphql module. If variables are required, they are the last argument:

```js

module ExampleQuery = [%graphql {|
  query Example ($userId: String!) {
    user(id: $userId) {
      id
      name
    }
  }
|}];

[@react.component]
let make = () => {
  switch (ExampleQuery.use({userId: "1"})) {
    | {data: Some({users})} =>
    ...
  }
}
```

## Bindings to JavaScript Packages

Contains partial bindings to the following:

- `@apollo/client`
- `@apollo/link-context`
- `@apollo/link-error`
- `@apollo/link-ws`
- `graphql`
- `subscriptions-transport-ws`
- `zen-observable`

While we strive to provide ergonomics that are intuitive and "reasonable", we do expose a 1:1 mapping to the javascript package structures if that is your preference. For instance, if you're looking in the Apollo docs and see `import { setContext } from '@apollo/link-context'` and you'd prefer to interact with this libaray in the same way, you can always access with the same filepath and name like so:

```js
module Apollo = {
  include ApolloClient.Bindings;
};

// import { setContext } from '@apollo/link-context'
let contextLink = Apollo.LinkContext.setContext(...);
// import { createHttpLink } from '@apollo/client'
let httpLink = Apollo.Client.createHttpLink(...);
```

For comparison, this library packages things up into logical groups that have a consistent structure with the intent to be more disoverable and less reliant on docs:

```js
// Make a generic link
let customLink = ApolloClient.Link.make(...);
// Specific link types are nested under the more general module
let contextLink = ApolloClient.Link.ContextLink.make(...)
// See, they're all the same :)
let httpLink = ApolloClient.Link.HttpLink.make(...)
```

## Contributing

Yes, please! Check out the [Contributing Guide](CONTRIBUTING.md) or issues to get started.
