---
id: queries
title: Queries
sidebar_label: Queries
---

## Using React Hooks

Queries work just like in JavaScript. You can declaratively fetch data using the `useQuery` hook.

### Basics

Create a query module with `graphql-ppx`. We'll use this throughout the examples on this page.

```reason
module TodosQuery = %graphql(`
  query TodosQuery {
    todos: allTodos {
      id
      text
      completed
    }
  }
`)
```

To execute the query, just call the `use` hook in a component like so.

```reason
@react.component
let make = () =>
  switch TodosQuery.use() {
  | {loading: true} => "Loading..."->React.string
  | {error: Some(_error)} => "Error loading data"->React.string
  | {data: Some({todos})} =>
    <div>
      {"There are "->React.string} {todos->Belt.Array.length->React.int} {" To-Dos"->React.string}
    </div>
  | {data: None, error: None, loading: false} =>
    "You might think this is impossible, but depending on the situation it might not be!"->React.string
  }
```

### Typical Usage

While we wish it was always as easy as above, there are many situations where you may be fetching new data while rendering a cached results, etc. Here's a slightly more complex example:

```reason
@react.component
let make = () => {
  let queryResult = TodosQuery.use()

  <div>
    {switch queryResult {
    | {loading: true, data: None} => <p> {"Loading"->React.string} </p>
    | {loading, data: Some({todos}), error, fetchMore} =>
      <div>
        <dialog>
          {loading ? <p> {"Refreshing..."->React.string} </p> : React.null}
          {switch error {
          | Some(_) => <p> {"Something went wrong, data may be incomplete"->React.string} </p>
          | None => React.null
          }}
        </dialog>
        <p>
          {React.string("There are " ++ (todos->Belt.Array.length->string_of_int ++ " To-Dos"))}
        </p>
        <p>
          <button onClick={_ => fetchMore()->Utils.Promise.ignore}>
            {"Fetch More!"->React.string}
          </button>
        </p>
      </div>
    | {loading: false, data: None} => <p> {"Error loading data"->React.string} </p>
    }}
  </div>
}
```

### Lazy Fetching of Data

```reason
@react.component
let make = () => {
  let (executeQuery, queryResult) = TodosQuery.useLazy()
  <div>
    {switch queryResult {
    | Unexecuted(_) => <>
        {"Waiting to be executed... "->React.string}
        <button onClick={_ => executeQuery()} value="execute"> {"Execute"->React.string} </button>
      </>
    | Executed({loading: true, data: None}) => <p> {"Loading"->React.string} </p>
    | Executed({loading, data: Some({todos}), error}) => <>
        <dialog>
          {loading ? <p> {"Refreshing..."->React.string} </p> : React.null}
          {switch error {
          | Some(_) => <p> {"Something went wrong, data may be incomplete"->React.string} </p>
          | None => React.null
          }}
        </dialog>
        <p>
          {React.string("There are " ++ (todos->Belt.Array.length->string_of_int ++ " To-Dos"))}
        </p>
      </>
    | Executed({loading: false, data: None}) => <p> {"Error loading data"->React.string} </p>
    }}
  </div>
}
```

### Live Queries

It's possible to update a query by attaching a subscription. Please see the subscriptions section on how to do this.

## Directly Via the Apollo Client

There are many instances where you might want to query outside the context of React. You can use the `query` method directly on the client to do this.

```reason
let addTodo = _ =>
  // This assumes you've set up a Client module as in the Getting Started section
  Apollo.client.mutate(~mutation=module(AddTodoMutation), {text: "Another To-Do"})
  ->Promise.map(result =>
    switch result {
    | Ok({data}) => Js.log2("mutate result: ", data)
    | Error(error) => Js.log2("Error: ", error)
    },
  )
  ->ignore
```

If you need to react to changes in some data in the cache, not just a one-off fetch, you can use the `watchQuery` method.

```reason
// This assumes you've set up a Client module as in the Getting Started section
let observableQuery = Apollo.client.watchQuery(~query=module(TodosQuery), ())

let watchQuerySubscription = observableQuery.subscribe(~onNext=result =>
  switch result {
  | {data: Some({todos})} => Js.log2("watchQuery To-Dos: ", todos)
  | _ => ()
  }
, ())

// Unsubscribe like so:
// watchQuerySubscription.unsubscribe();
```
