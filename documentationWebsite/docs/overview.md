---
id: overview
title: Overview
sidebar_label: Overview
slug: /
---

This library provides rescript bindings to `@apollo/client` and related libraries. We rely on the amazing [Graphql-ppx](https://beta.graphql-ppx.com) for typesafe GraphQL operations and fragments in Rescript. This means that even when manipulating the cache directly, you'll always be working with rescript data structures and never have to concern yourself the javascript representation of your data!

We provide a few ergonomic improvements for working in ReScript, but our intention is not to provide another abstraction on top of Apollo. **The [official Apollo Client 3 docs](https://www.apollographql.com/docs/react/v3.0-beta/get-started/), should be your authoritative source for understanding how to work with Apollo Client!** This documentation site exists as a convenience for working with ReScript syntax and to document gotchas and inconsistencies with the underlying javascript libraries.

## Bindings to JavaScript Packages

Contains partial bindings to the following:

- [@apollo/client](https://github.com/apollographql/apollo-client)
- [graphql](https://github.com/graphql/graphql-js)
- [subscriptions-transport-ws](https://github.com/apollographql/subscriptions-transport-ws)
- [zen-observable](https://github.com/zenparsing/zen-observable)

While we strive to provide ergonomics that are intuitive and "reasonable", the intent is to also expose a 1:1 mapping to the javascript package structures if that is your preference. For instance, if you're looking in the Apollo docs and see `import { setContext } from '@apollo/link-context'` and you'd prefer to interact with this library in the same way, you can always access with the same filepath and name like so:

```reason
module Apollo = {
  include ApolloClient.Bindings
};

// import { setContext } from '@apollo/client/link/context'
let contextLink = Apollo.Client.Link.Context.setContext(...)
// import { createHttpLink } from '@apollo/client'
let httpLink = Apollo.Client.createHttpLink(...)
```

For comparison, this library packages things up into logical groups that have a consistent structure with the intent to be more disoverable and less reliant on docs:

```reason
// Make a generic link
let customLink = ApolloClient.Link.make(...)
// Specific link types are nested under the more general module
let contextLink = ApolloClient.Link.ContextLink.make(...)
// See, they're all the same :)
let httpLink = ApolloClient.Link.HttpLink.make(...)
```

## Alternatives

There are many great options for working with GraphQL in Rescript! I recommend giving them a look to see what works best for you.

- [Reason Relay](https://github.com/zth/reason-relay)
- [Reason Urql](https://github.com/FormidableLabs/reason-urql)
