/**
 Here is a contrived example of duplicating the first To-Do, but it is hopefully
 representative of real world use-cases. Working with the promises and types can
 be quite confusing at first and there are quite a few options of how to go about it,
 so we provide concrete examples of a few different options. Please note that the
 style here is quite messy for illustration, but in most cases I would encourage you
 to write something cleaner. You'll find it's much easier to reason about and debug
 when working in discrete chunks that state exactly what they do. Something like:
 ```
 getFirstTodo()
 ->Promise.mapOk(duplicateTodo)
 ->Promise.get(logResult);
 */
module ApolloError = ApolloClient.Types.ApolloError;
module ApolloQueryResult = ApolloClient.Types.ApolloQueryResult;
module FetchResult = ApolloClient.Types.FetchResult;

module DuplicateTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        text
      }
    }
  |}
];

module TodosQuery = [%graphql
  {|
    query TodosQuery {
      todos: allTodos {
        id
        text
        completed
      }
    }
  |}
];

let client = Client.instance;

/**
 Chaining with completely vanilla promises.
 Note that you will generally need to annotate one of the record fields
 with the module it comes from because the compiler cannot infer the type.
 */
client.query(~query=(module TodosQuery), ())
|> Js.Promise.then_(result =>
     Js.Promise.resolve(
       switch (result) {
       | Ok({ApolloQueryResult.data: {TodosQuery.todos}}) =>
         switch (todos->Belt.Array.get(0)) {
         | Some(firstTodo) => Ok(firstTodo)
         | None => Error(ApolloError.make(~errorMessage="No To-Dos!", ()))
         }
       | Error(_) as error => error
       },
     )
   )
|> Js.Promise.then_(result =>
     switch (result) {
     | Ok(firstTodo) =>
       client.mutate(
         ~mutation=(module DuplicateTodoMutation),
         {text: firstTodo.TodosQuery.text},
       )
     | Error(_) as error => Js.Promise.resolve(error)
     }
   )
|> Js.Promise.then_(result =>
     Js.Promise.resolve(
       switch (result) {
       | Ok(_) => Js.log("Duplicated first todo!")
       | Error(apolloError) =>
         Js.log2("Something went wrong: ", apolloError.ApolloError.message)
       },
     )
   )
|> ignore;

/**
  Chaining with vanilla promises and a couple utility functions in this repo.
  Hopefully Js.Promise API will be T-First soon and this won't be necessary.
  */
client.query(~query=(module TodosQuery), ())
->Utils.Promise.then_(result =>
    Js.Promise.resolve(
      switch (result) {
      | Ok({data: {todos}}) =>
        switch (todos->Belt.Array.get(0)) {
        | Some(firstTodo) => Ok(firstTodo)
        | None => Error(ApolloError.make(~errorMessage="No To-Dos!", ()))
        }
      | Error(_) as error => error
      },
    )
  )
->Utils.Promise.then_(result =>
    switch (result) {
    | Ok(firstTodo) =>
      client.mutate(
        ~mutation=(module DuplicateTodoMutation),
        {text: firstTodo.text},
      )
    | Error(_) as error => Js.Promise.resolve(error)
    }
  )
->Utils.Promise.then_(result =>
    Js.Promise.resolve(
      switch (result) {
      | Ok(_) => Js.log("Duplicated first todo!")
      | Error(apolloError) =>
        Js.log2("Something went wrong: ", apolloError.message)
      },
    )
  )
->Utils.Promise.ignore;

/**
 Chaining using `reason-promise` as an example of a different promise style
 Other great alternatives are:
 - bs-future
 - @yawaramin/prometo

 Feel free to add more examples!
 */
client.query(~query=(module TodosQuery), ())
->Utils.ReasonPromise.fromJs
->Promise.map(result =>
    switch (result) {
    | Ok({data: {todos}}) =>
      switch (todos->Belt.Array.get(0)) {
      | Some(firstTodo) => Ok(firstTodo)
      | None => Error(ApolloError.make(~errorMessage="No To-Dos!", ()))
      }
    | Error(_) as error => error
    }
  )
->Promise.flatMapOk(firstTodo => {
    client.mutate(
      ~mutation=(module DuplicateTodoMutation),
      {text: firstTodo.text},
    )
    ->Utils.ReasonPromise.fromJs
  })
->Promise.get(result =>
    switch (result) {
    | Ok(_) => Js.log("Duplicated first todo!")
    | Error(apolloError) =>
      Js.log2("Something went wrong: ", apolloError.message)
    }
  );
