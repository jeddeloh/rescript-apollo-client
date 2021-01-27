---
id: mutations
title: Mutations
sidebar_label: Mutations
---

## Using React Hooks

### Basic usage

Create a mutation module using `graphql-ppx`. We'll use this throughout the examples on this page.

```
module AddTodoMutation = %graphql(
  `
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        completed
        text
      }
    }
  `
)
```

Call the `use` hook in a component

```reason
@react.component
let make = () => {
  let (mutate, _mutationResult) = AddTodoMutation.use()

  <button onClick={_ => mutate({text: "Some text"})->ignore}>
    {"Add To-Do"->React.string}
  </button>
}
```

### Post-Mutation Updates

This section needs improvements, but for now here's an examples of refetching data after a mutation, updating the cache, and optimistic updates.

```reason
@react.component
let make = () => {
  let (mutate, result) = AddTodoMutation.use()

  switch result {
  | {called: false} => <>
      {"Not called... "->React.string}
      <button
        onClick={_ =>
          mutate(
            ~optimisticResponse=_variables => {
              todo: {
                __typename: "TodoItem",
                id: "optimisticResponseTodo",
                completed: None,
                text: "To-Do from optimisticRespomse",
              },
            },
            ~update=({writeFragment, writeQuery}, {data}) =>
              switch data {
              | Some({todo}) =>
                // Apollo docs use cache.modify, but it's not typesafe. I recommend some
                // combination of readQuery / writeQuery / writeFragment
                Js.log2("mutate.update To-Do: ", todo)
                let _unusedRef = writeFragment(
                  ~fragment=module(Fragments.TodoItem),
                  ~data={
                    __typename: todo.__typename,
                    id: "fragmentToDo",
                    completed: None,
                    text: "To-Do from writeFragment",
                  },
                  (),
                )
                let _unusedRef = writeQuery(
                  ~query=module(TodosQuery),
                  ~data={
                    todos: [
                      {
                        __typename: todo.__typename,
                        id: "writeQueryToDo",
                        completed: None,
                        text: "To-Do from writeQuery",
                      },
                    ],
                  },
                  (),
                )
              | None => ()
              },
            ~refetchQueries=[
              TodosQuery.refetchQueryDescription(),
              // - OR -
              String("TodosQuery"),
            ],
            {text: "Another To-Do"},
          )->ignore}>
        {"Add To-Do (all the bells and whistles)"->React.string}
      </button>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({todo: {text}}), error: None} =>
    <p> {React.string("To-Do added: \"" ++ (text ++ "\""))} </p>
  | {error} => <>
      {"Error loading data"->React.string}
      {switch error {
      | Some(error) => React.string(": " ++ error.message)
      | None => React.null
      }}
    </>
  }
}
```

## Directly Via the Apollo Client

```reason
let addTodo = _ =>
  // This assumes you've set up a Client module as in the Getting Started section
  Apollo.client.mutate(~mutation=module(AddTodoMutation), {text: "Another To-Do"})
  ->Promise.map(result =>
    switch result {
    | Ok({data}) => Js.log2("mutate result: ", data)
    | Error(error) => Js.log2("Error: ", error)
    }
  )
  ->ignore
```
