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
let fauxTodosQuery = ();
let fauxAddTodoMutation = ();

type fauxVariables = {text: string};
type fauxJsClient('query, 'mutation) = {
  query:
    (~query: 'query, unit) =>
    Js.Promise.t(ApolloClient.Types.ApolloQueryResult.t(Js.Json.t)),
  mutate:
    (~mutation: 'mutation, fauxVariables) =>
    Js.Promise.t(ApolloClient.Types.FetchResult.t(Js.Json.t)),
};

let client = Client.instance;
[@bs.val] external jsClient: fauxJsClient('query, 'mutation) = "jsClient";

client.query(~query=(module TodosQuery), ())
->Promise.flatMapOk(({data}) => {
    client.mutate(~mutation=(module AddTodoMutation), {text: ""})
  })
->Promise.get(result =>
    switch (result) {
    | Ok(_) => Js.log("Success for both!")
    | Error(error) =>
      Js.log2("Typed ApolloError if one of them failed!", error)
    }
  );

jsClient.query(~query=fauxTodosQuery, ())
|> Js.Promise.then_((apolloQueryResult: ApolloQueryResult.t(_)) => {
     switch (apolloQueryResult) {
     | {data: Some(data), error: None} =>
       jsClient.mutate(~mutation=fauxAddTodoMutation, {text: ""})
       |> Js.Promise.then_((fetchResult: FetchResult.t(_)) => {
            switch (fetchResult) {
            | {data: Some(data), error: None} => Js.Promise.resolve(data)
            | {error: Some(error)} => Js.Promise.reject(Obj.magic(error))
            | {data: None, error: None} =>
              Js.Promise.reject(Obj.magic(":_("))
            }
          })
     | {error: Some(error)} => Js.Promise.reject(Obj.magic(error))
     | {data: None, error: None} =>
       Js.Promise.reject(
         Obj.magic(
           "As a new user how do I create an exn? Should I raise instead?",
         ),
       )
     }
   })
|> Js.Promise.then_(_ => Js.Promise.resolve(Js.log("Success for both!")))
|> Js.Promise.catch(error =>
     Js.Promise.resolve(Js.log2("Untyped error of something!", error))
   );
