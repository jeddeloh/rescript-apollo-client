module ApolloQueryResult = ApolloClient.Types.ApolloQueryResult;
module FetchResult = ApolloClient.Types.FetchResult;

module AddTodoMutation = [%graphql
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

// Chaining using default `reason-promise`
client.query(~query=(module TodosQuery), ())
->Promise.flatMapOk(({data: _}) => {
    client.mutate(~mutation=(module AddTodoMutation), {text: "example"})
  })
->Promise.get(result =>
    switch (result) {
    | Ok(_) => Js.log("Success for both!")
    | Error(error) =>
      Js.log2("Typed ApolloError if one of them failed!", error)
    }
  );

module Promise = ApolloClient__Promise;

// Chaining with our T-first Js promise helpers if you don't like reason-promise
client.query(~query=(module TodosQuery), ())
->Promise.resultToJs
->Promise.Js.then_(({data: _}) => {
    Promise.Js.resolve(
      client.mutate(~mutation=(module AddTodoMutation), {text: "example"})
      ->Promise.resultToJs,
    )
  })
->Promise.Js.then_(_ => Promise.Js.resolve(Js.log("Success for both!")))
->Promise.Js.catch(error =>
    Promise.Js.resolve(Js.log2("Untyped error", error))
  )
->Promise.Js.finalize;

// Chaining with regular Js promises
client.query(~query=(module TodosQuery), ())
|> ApolloClient__Promise.resultToJs
|> Js.Promise.then_(({data: _}: ApolloQueryResult.t__ok(_)) => {
     Js.Promise.resolve(
       client.mutate(~mutation=(module AddTodoMutation), {text: "example"})
       |> ApolloClient__Promise.resultToJs,
     )
   })
|> Js.Promise.then_(_ => Promise.Js.resolve(Js.log("Success for both!")))
|> Js.Promise.catch(error =>
     Js.Promise.resolve(Js.log2("Untyped error", error))
   )
|> ignore;
