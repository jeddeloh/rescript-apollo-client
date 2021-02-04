---
id: subscriptions
title: Subscriptions
sidebar_label: Subscriptions
---

## Using React Hooks

### Basic Usage

Create a Subscription module using `graphql-ppx`. We'll use this throughout the examples on this page.

```
module StatsSubscription = %graphql(
  `
  subscription SorryItsNotASubscriptionForTodos {
    siteStatisticsUpdated {
      currentVisitorsOnline
    }
  }
  `
)
```

Call the `use` hook in a component

```reason
@react.component
let make = () =>
  <div>
    {switch StatsSubscription.use() {
    | {data: Some({siteStatisticsUpdated: Some({currentVisitorsOnline})})} =>
      <p>
        {React.string("There are " ++ (string_of_int(currentVisitorsOnline) ++ " visitors online"))}
      </p>
    | _ignoredForExample => React.null
    }}
  </div>
```

### Subscribing to Updates for a Query

Whenever a query returns a result in Apollo Client, that result includes a subscribeToMore function. You can use this function to execute a followup subscription that pushes updates to the query's original result.

> The `subscribeToMore `function is similar in structure to the `fetchMore` function that's commonly used for handling pagination. The primary difference is that `fetchMore` executes a followup query, whereas `subscribeToMore` executes a subscription.

The following example is totally nonsensical for reasons I won't go into, but should give you an idea of how to go about it.

```reason
@react.component
let make = () => {
  let queryResult = TodosQuery.use()

  React.useEffect0(() => {
    queryResult.subscribeToMore(
      ~subscription=module(StatsSubscription),
      ~updateQuery=(previous, {subscriptionData: {data: {siteStatisticsUpdated}}}) => {
        {
          todos: Belt.Array.concat(
            previous.todos,
            [
              {
                __typename: "TodoItem",
                id: "subscribeToMoreTodo",
                completed: None,
                text: "Check how many visitors are online!"),
              },
            ],
          ),
        }
      },
      (),
    )
    None
  })

  switch queryResult {
  | {data: Some({todos})} =>
    // render something
  }
}
```

## Directly Via the Apollo Client

```reason
let statsSubscription = Apollo.client.subscribe(
  ~subscription=module(StatsSubscription),
  (),
).subscribe(
  ~onNext=value => Js.log2("new value:", value),
  ~onError=error => Js.log2("subscription error:", error),
  (),
)
// Unsubscribe like so:
// statsSubscription.unsubscribe()
```
