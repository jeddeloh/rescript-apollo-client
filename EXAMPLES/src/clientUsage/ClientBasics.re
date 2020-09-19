module ApolloQueryResult = ApolloClient.Types.ApolloQueryResult;
module ObservableQuery = ApolloClient.Types.ObservableQuery;

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

let logTodos = _ =>
  Client.instance.query(~query=(module TodosQuery), ())
  ->Promise.get(
      fun
      | Ok({data: {todos}}) => Js.log2("query To-Dos: ", todos)
      | Error(error) => Js.log2("Error: ", error),
    );

let addTodo = _ =>
  Client.instance.mutate(
    ~mutation=(module AddTodoMutation),
    {text: "Another To-Do"},
  )
  ->Promise.get(
      fun
      | Ok({data}) => Js.log2("mutate result: ", data)
      | Error(error) => Js.log2("Error: ", error),
    );

let observableQuery =
  Client.instance.watchQuery(~query=(module TodosQuery), ());

let watchQuerySubscription =
  observableQuery.subscribe(
    ~onNext=
      result =>
        switch (result) {
        | {data: Some({todos})} => Js.log2("watchQuery To-Dos: ", todos)
        | _ => ()
        },
    (),
  );
// Unsubscribe like so:
// watchQuerySubscription.unsubscribe();

[@react.component]
let make = () => {
  <div>
    <p>
      <button onClick=logTodos>
        "Log To-Dos (Reason Promise)"->React.string
      </button>
    </p>
    <p> <button onClick=addTodo> "Add To-Do"->React.string </button> </p>
    <p> "[ To-Dos also logged in console with watchQuery ]"->React.string </p>
  </div>;
};
