module ApolloError = ApolloClient.Types.ApolloError

module DuplicateTodoMutation = %graphql(
  `
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        text
      }
    }
  `
)

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

let client = Apollo.client

client.query(~query=module(TodosQuery), ())->Promise.map(result =>
  switch result {
  | Ok({data: {todos}}) =>
    switch todos->Belt.Array.get(0) {
    | Some(firstTodo) => Ok(firstTodo)
    | None => Error(ApolloError.make(~errorMessage="No To-Dos!", ()))
    }
  | Error(_) as error => error
  }
)->Promise.then(result =>
  switch result {
  | Ok(firstTodo) => client.mutate(~mutation=module(DuplicateTodoMutation), {text: firstTodo.text})
  | Error(_) as error => Promise.resolve(error)
  }
)->Promise.then(result =>
  Promise.resolve(
    switch result {
    | Ok(_) => Js.log("Duplicated first todo!")
    | Error(apolloError) => Js.log2("Something went wrong: ", apolloError.message)
    },
  )
)->ignore
