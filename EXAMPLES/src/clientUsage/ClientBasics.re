module ApolloQueryResult = ApolloClient.Types.ApolloQueryResult;
module ObservableQuery = ApolloClient.Types.ObservableQuery;
module Prometo = Yawaramin__Prometo;

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

let logTodos_good_reasonPromise = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module TodosQuery), ())
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.get(
      fun
      | Ok({data: Some({todos})}) => Js.log2("query To-Dos: ", todos)
      | Ok(_) => Js.log("Error: no To-Dos!")
      | Error(error) => Js.log2("Error: ", error),
    );

let logTodos_good_prometo = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module TodosQuery), ())
  ->Prometo.fromPromise
  ->Prometo.handle(~f=result => {
      switch (result) {
      | Ok({data: Some({todos})}) => Js.log2("query To-Dos: ", todos)
      | Ok(_) => Js.log("Error: no To-Dos!")
      | Error(error) => Js.log2("Error: ", error)
      };
      result;
    })
  ->ignore;

/**
 * The ergonomics of the Js module promise methods are such that the compiler cannot
 * infer the type of result which means the record fields are not in scope, forcing you
 * to annotate it. I would highly recommend using one of the promise libraries above!
 */
let logTodos_bad_jsPromise = _ =>
  Client.instance
  ->ApolloClient.query(~query=(module TodosQuery), ())
  ->Js.Promise.then_(
      (result: ApolloQueryResult.t(_)) =>
        switch (result) {
        | {data: Some({TodosQuery.todos})} =>
          Js.Promise.resolve(Js.log2("query To-Dos: ", todos))
        | _ => Js.Exn.raiseError("Error: no people!")
        },
      _,
    )
  ->Js.Promise.catch(
      eeyore => Js.Promise.resolve(Js.log2("Error: ", eeyore)),
      _,
    )
  ->ignore;

let addTodo = _ =>
  Client.instance
  ->ApolloClient.mutate(
      ~mutation=(module AddTodoMutation),
      {text: "Another To-Do"},
    )
  ->Promise.Js.fromBsPromise
  ->Promise.Js.toResult
  ->Promise.get(
      fun
      | Ok(result) => Js.log2("mutate result: ", result.data)
      | Error(error) => Js.log2("Error: ", error),
    );

let watchQuerySubscription =
  Client.instance
  ->ApolloClient.watchQuery(~query=(module TodosQuery), ())
  ->ObservableQuery.subscribe(
      ~onNext=
        result =>
          switch (result) {
          | {data: Some({todos})} => Js.log2("watchQuery To-Dos: ", todos)
          | _ => ()
          },
      (),
    );
// Unsubscribe like so:
// watchQuerySubscription->ApolloClient.ObservableQuery.Subscription.unsubscribe;

[@react.component]
let make = () => {
  <div>
    <p>
      <button onClick=logTodos_good_reasonPromise>
        "Log To-Dos (Reason Promise)"->React.string
      </button>
    </p>
    <p>
      <button onClick=logTodos_good_prometo>
        "Log To-Dos (Prometo)"->React.string
      </button>
    </p>
    <p>
      <button onClick=logTodos_bad_jsPromise>
        "Log To-Dos (Js Module)"->React.string
      </button>
    </p>
    <p> <button onClick=addTodo> "Add To-Do"->React.string </button> </p>
    <p> "[ To-Dos also logged in console with watchQuery ]"->React.string </p>
  </div>;
};
