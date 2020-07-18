<p align="center">
    <img src="assets/logo-v1.png" alt="Logo">
  	<br><br>
    ReasonML / BuckleScript bindings for the Apollo Client ecosystem
</p>

<p align="center">
  <a href="https://www.npmjs.com/package/reason-apollo-client">
    <img src="https://badge.fury.io/js/reason-apollo-client.svg" alt="npm version" />
  </a>
</p>

<p align="center">
  <a href="#installation">Installation</a> •
  <a href="#usage">Usage</a> •
  <a href="EXAMPLES/src">Examples</a> •
  <a href="#bindings-to-javascript-packages"> JavaScript</a> •
  <a href="#about-this-library">About</a> •
  <a href="#contributing">Contributing</a>
</p>

## Installation

### 1. `graphql-ppx`

We rely on Graphql-ppx for typesafe GraphQL operations and fragments in ReasonML. [Go to the official documentation](https://beta.graphql-ppx.com) for installation instructions.

You should now have a `graphql_schema.json` in your project somewhere. Make sure it's always up-to-date!

### 2. `@apollo/client` and Optional Dependencies

```sh
npm install reason-apollo-client @apollo/client
# optional
npm install @apollo/link-context @apollo/link-error @apollo/link-ws subscriptions-transport-ws
```

### 3. Apollo-Specific `graphql-ppx` Configuration

Add the following under `bs-dependencies` and `graphql`, in your `bsconfig.json`

```diff
{
  "graphql": {
+   "apollo-mode": true,
+   "extend-mutation": "ApolloClient.GraphQL_PPX.ExtendMutation",
+   "extend-query": "ApolloClient.GraphQL_PPX.ExtendQuery",
+   "extend-subscription": "ApolloClient.GraphQL_PPX.ExtendSubscription",
+   "template-tag-return-type": "ApolloClient.GraphQL_PPX.templateTagReturnType",
+   "template-tag-import": "gql",
+   "template-tag-location": "@apollo/client"
  },
  "ppx-flags": ["@reasonml-community/graphql-ppx/ppx"],
  "bs-dependencies: [
    "@reasonml-community/graphql-ppx"
+   "reason-apollo-client"
  ]
}
```

- `"apollo-mode"` automaticaly sprinkles `__typename` throughout our operation and fragment definitions
- `"-template-tag-*"` is how we tell `graphql-ppx` to wrap every operation with `gql`
- `"extend-*"` allows `reason-apollo-client` to automatically decorate the generated modules with Apollo-specific things like the correct hook for that operation!

## Usage

The [EXAMPLES/](https://github.com/reasonml-community/reason-apollo-client/tree/master/EXAMPLES) directory is the best documentation at the moment (real docs are coming), but in short, the appropriate hook is exposed as a `use` function on the graphql module. If variables are required, they are the last argument:

```reason
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

Other than some slightly different ergonomics, the underlying functionality is almost identical to the [official Apollo Client 3 docs](https://www.apollographql.com/docs/react/v3.0-beta/get-started/), so that is still a good resource for working with this library.

## Recommended Editor Extensions (Visual Studio Code)

[vscode-reasonml-graphql](https://marketplace.visualstudio.com/items?itemName=GabrielNordeborn.vscode-reasonml-graphql) provides syntax highlighting, autocompletion, formatting and more for your graphql operations

[vscode-graphiql-explorer](https://marketplace.visualstudio.com/items?itemName=GabrielNordeborn.vscode-graphiql-explorer) provides a visual interface to explore the schema and generate operations

## Bindings to JavaScript Packages

Contains partial bindings to the following:

- [@apollo/client](https://github.com/apollographql/apollo-client)
- [@apollo/link-context](https://github.com/apollographql/apollo-link)
- [@apollo/link-error](https://github.com/apollographql/apollo-link)
- [@apollo/link-ws](https://github.com/apollographql/apollo-link)
- [graphql](https://github.com/graphql/graphql-js)
- [subscriptions-transport-ws](https://github.com/apollographql/subscriptions-transport-ws)
- [zen-observable](https://github.com/zenparsing/zen-observable)

While we strive to provide ergonomics that are intuitive and "reasonable", the intent is to also expose a 1:1 mapping to the javascript package structures if that is your preference. For instance, if you're looking in the Apollo docs and see `import { setContext } from '@apollo/link-context'` and you'd prefer to interact with this library in the same way, you can always access with the same filepath and name like so:

```reason
module Apollo = {
  include ApolloClient.Bindings;
};

// import { setContext } from '@apollo/link-context'
let contextLink = Apollo.LinkContext.setContext(...);
// import { createHttpLink } from '@apollo/client'
let httpLink = Apollo.Client.createHttpLink(...);
```

For comparison, this library packages things up into logical groups that have a consistent structure with the intent to be more disoverable and less reliant on docs:

```reason
// Make a generic link
let customLink = ApolloClient.Link.make(...);
// Specific link types are nested under the more general module
let contextLink = ApolloClient.Link.ContextLink.make(...)
// See, they're all the same :)
let httpLink = ApolloClient.Link.HttpLink.make(...)
```

## About This Library

Apollo bindings in the Reason / BuckleScript community are pretty confusing as a write this (July 14, 2020), so it's worth providing some context to help you make the right decisions about which library to use.

This library, `reason-apollo-client`, targets Apollo Client 3 and aims to take full advantage of v1.0.0 `graphql-ppx` features (still in beta) and is intended to be a replacement for `reason-apollo` and `reason-apollo-hooks` (all non-deprecated functionality should be here and more). You should avoid using those libraries at the same time as this one.

#### Alternatives

[reason-apollo](https://github.com/apollographql/reason-apollo), despite being under the apollographql github org, doesn't have any official Apollo team support behind it and currently seems like it may be abandoned. It binds to the `react-apollo` js package and some of the older apollo packages not under the `@apollo` npm namespace.

[reason-apollo-hooks](https://github.com/reasonml-community/reason-apollo-hooks) is the hooks companion to the `reason-apollo` library and binds to `@apollo/react-hooks`. Given the lack of development on `reason-apollo`, there has been a lot of active contribution pulling `reason-apollo` features in there. It's fairly battle-tested and it provides a nice, simple interface to hooks. It's not currently compatible with `graphql-ppx` v1.0.0, but there is a branch that adds basic support for it.

## Contributing

Lets work to make the Apollo experience in ReasonML the best experience out there! This is a solid base, but there's a lot of low-hanging fruit remaining—more bindings, docs, examples, tests, better ergonomics—there's so much left to do! Check out the [Contributing Guide](CONTRIBUTING.md) or issues to get started.
