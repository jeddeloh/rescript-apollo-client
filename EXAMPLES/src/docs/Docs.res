/**
 This file used for formatting/typechecking of code snippets on the documentation website
 */

module TodosQuery = %graphql(
  `
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  `
)

module Basics = {
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
      "I hope this is impossible, but sometimes it's not!"->React.string
    }
}

module Typical = {
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
            <button onClick={_ => fetchMore()->ignore}> {"Fetch More!"->React.string} </button>
          </p>
        </div>
      | {loading: false, data: None} => <p> {"Error loading data"->React.string} </p>
      }}
    </div>
  }
}

module Lazy = {
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
}

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

module MutationBasics = {
  @react.component
  let make = () => {
    let (mutate, _mutationResult) = AddTodoMutation.use()

    <button onClick={_ => mutate({text: "Some text"})->ignore}>
      {"Add To-Do"->React.string}
    </button>
  }
}

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
