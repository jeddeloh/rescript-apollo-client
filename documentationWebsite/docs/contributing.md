---
id: contributing
title: Contributing
---

Lets work to make the Apollo experience in ReScript the best experience out there!

## Core Philosopies

- Provide 1:1 mapping to Javascript _then_ use those as building blocks for more "reasonable" ergonomics
- Follow a consistent pattern for bindings
- Avoid partial types or bindings if possible
- Encourage incremental contribution from the community rather than biting off more than one person can chew

There's nothing fancy about this library. It tends to view the problem of bindings as a people problem rather than a programming problem (all the hard work has already been done for us by Graphql-ppx) As such, a lot of detail is paid to consistency and clarity with the hope of maximizing human ability to both add and verify that bindings are correct. The long-term success or failure of this library is will likely be dependent on active community contribution rather than the efforts of a few individuals.

### Following a Consistent Pattern

At the file level, bindings to Javascript packages should mirror the directory structure in the JS package. This is critically important! It should be easy for anyone else to see exactly what is being bound and if anything is missing or incorrect. This has the side benefit of being able to navigate to any import you see in the javascript docs via filepath pattern, but it's primary purpose is consistency.

At the code level, all JS bindings should go in a `Js_` module of some sort. At first it seems ridiculous, but it pays off at scale. (See **Reasoning Behind `Js_` modules**)

### Avoiding Partial Types

Please type something as completely as possible when you come across it or leave it for someone else (if nothing else, you can use an abstract type so things will still flow through everywhere and people can cast it when in a hurry). This way no one has to go back and duplicate that work of tracing through the same code you were just in _and_ we can trust that if a binding exists, it's probably complete and we can just reuse.

## Style Guidelines

### Directory Structure and Module Naming

Each directory should have a corresponding Reason module.

```
@apollo/client/react/hooks/useQuery.js
```

should become

```
src/react/hooks/ApolloClient__React_Hooks_UseQuery.res
```

#### Breaking it down: `/[1]/[2]__[3]_[4]`

1. ReScript files should be located in the same directory structure as the js counterpart (usually there is a `.d.ts` for every `.js` file so we can think of them interchangeably)
1. All module names should be prefixed with `ApolloClient__` "namespace"
1. File names reflect the directory structure
1. Files should be named the same as the js counterpart

### Types

- Please use the same naming as typescript where possible
- Every type goes in its own module with a `type t` (exception: see SubStypes)
- Every type module should contain a `type t`, a `Js_` module with a `type t`, and a `toJs` or `fromJs` conversion function. `t => Js_.t` or `Js_.t => t`
- Paste the type definition from the `.d.ts` file above the `type t` in the `Js_` module
- If data requires parsing/serializing create a new record even if the shape is the same. This ensures you don't forget to parse somewhere.
- Prefer single types when the more complicated type in a union can express both `shouldResubscribe?: boolean | ((options: BaseSubscriptionOptions<TData, TVariables>) => boolean);`
- Do all of this even if it doesn't need it (See Reasoning Behind `Js_` modules)

Example:

```
// #1 - create a Js_ module for your type
module Js_ = {
  // #2 - paste the definition from the .js file here
  // #3 - add the `.js` representation of type t = ...
}

// #4  - add the ReScript representation of type t
// #4a - you can use `type t = Js_.t` if they are _exactly_ the same
// #4b - if they are the exact same _shape_ but requires parsing or serializing, *define a new record of the same shape* so we can leverage the fact that records are nominally typed to prevent someone forgetting to convert somewhere

// #5 - add `toJs` or `fromJs`. They often require parsing: `let fromJs: Js_.t('jsData, ~parse: 'jsData => 'data) => t('data)`
```

#### SubTypes

Sometimes multiple types were required to represent a single type in TypeScript. In order to help make it clear what is a binding to an actual type and what is just needed by ReScript, we take a similar naming approach to the modules (prefixing with the parent). For instance, `Apollo_Client__React_Types.QueryResult.Raw` has a `type t` that uses `t_fetchMoreOptions` which in turn uses `t_fetchMoreOptions_updateQueryOptions`.

### Binding to Js Module Exports

`externals` go under a `Js_` module and any types they reference should be `Js_.t` versions.

### Binding to Methods

Prefer T-first with `[@send]`. Again, `externals` go under a `Js_` module with a `type t` and any types they reference should be `Js_.t` versions.

### Binding to Objects

Use records

### Binding to Enums

Prefer standard variants. `jsConverter` works great for ints, but otherwise use manual `toJs` and `fromJs` functions. Standard variants are just nicer to consume in other places and this keeps consistency

### General

- Prefer T-first because that's the Reason community default
- Hooks are T-last because that makes sense given their usage
- ApolloClient methods are a Frankenstein T-first _and_ T-last because they want to maintain similarity with hooks api, but are also T-first due to [@send] and T-first preference

### Reasoning behind `Js_` modules

Here's a typical example:

```
module TypeName = {
  module Js_ = {
    type t;
  }

  type t = Js_.t;
};
```

Not much point yet, but bear with me, it pays off in the big picture. What if we need to parse/serialize some data which happens a lot in this library?

```diff
module TypeName = {
  module Js_ = {
-   type t;
+   type t('jsData) = {
+     data: 'jsData,
+   };
  }

- type t = Js_.t;
+ type t('data) = {
+   data: 'data
+ };

+ let toJs: t => Js_.t = (t, ~serialize) => {
+   data: serialize(t.data)
+ };
};
```

Nice, now when wherever we say we want a `Typename.t`, we can never forget to parse because records are nominally typed.

What if you need to construct a class or object with a bunch of optional properties?

```diff
module TypeName = {
  module Js_ = {
    type t('jsData) = {
      data: 'jsData,
+     optionalProp: option(bool),
    };

+   type make_options('jsData) = {
+     data: 'jsData,
+     optionalProp: option(bool),
+   }

+   [@new] [@module "someModule"]
+   external make = (make_options('jsData)) => t = "someClass";
  }

  type t('data) = {
    data: 'data,
+   optionalProp: option(bool),
  };

  let toJs: t => Js_.t = (t) => {
    data: serialize(t.data)
+   optionalProp: t.optionalProp
  };

+ let make: (~data, ~optionalProp=?, ()) =>
+   Js_.make(
+     toJs({
+         data,
+         optionalProp
+       },
+       ~serialize,
+     )
+   );
};
```

It's nice to have all this conversion stuff wrapped in one module and have consistent naming. All of it together really begins to pay off when we have types that reference many other types.

```diff
module TypeName = {
  module Js_ = {
    type t('jsData) = {
      data: 'jsData,
+     reusedType: ReusedType.Js_.t
    };

    type make_options('jsData) = {
      data: 'jsData,
      optionalProp: option(bool),
+     reusedType: ReusedType.Js_.t
    }
    [@new] [@module "someModule"]
    external make = (make_options('jsData)) => t = "someClass";
  }

  type t('data) = {
    data: 'data,
    optionalProp: option(bool),
+   reusedType: ReusedType.t
  };

- let toJs: t => Js_.t = (t) => {
+ let toJs: t => Js_.t = (t, ~serialize) => {
    data: serialize(t.data)
    optionalProp: t.optionalProp
+   reusedType: t.reusedType->ReusedType.toJs(~serialize)
  };

- let make: (~data, ~optionalProp=?, ()) =>
+ let make: (~data, ~optionalProp=?, ~reusedType, ~serialize, ()) =>
    Js_.make(
      toJs({
          data,
          optionalProp
+         reusedType
        },
        ~serialize,
      )
    );
};
```

Does `reusedType` need some conversion or parsing or serializing? If we've done things right, all we need to confirm is that any `Js_` modules reference the `Js_.t` versions of types, the compiler will do the rest! In this case, it turns out it needs also needs parse!

```diff
module TypeName = {
  module Js_ = {
    type t('jsData) = {
      data: 'jsData,
      reusedType: ReusedType.Js_.t
    };

    type make_options('jsData) = {
      data: 'jsData,
      optionalProp: option(bool),
      reusedType: ReusedType.Js_.t
    }
    [@new] [@module "someModule"]
    external make = (make_options('jsData)) => t = "someClass";
  }

  type t('data) = {
    data: 'data,
    optionalProp: option(bool),
    reusedType: ReusedType.t
  };

- let toJs: t => Js_.t = (t, ~serialize) => {
+ let toJs: t => Js_.t = (t, ~parse, ~serialize) => {
    data: serialize(t.data)
    optionalProp: t.optionalProp
-   reusedType: t.reusedType->ReusedType.toJs(~serialize)
+   reusedType: t.reusedType->ReusedType.toJs(~parse, ~serialize)
  };

- let make: (~data, ~optionalProp=?, ~reusedType, ~serialize, ()) =>
+ let make: (~data, ~optionalProp=?, ~parse, ~reusedType, ~serialize, ()) =>
    Js_.make(
      toJs({
          data,
          optionalProp
          reusedType
        },
        ~serialize,
      )
    );
};
```
