module Cache = ApolloClient.Cache;

module AddTodoMutation = [%graphql
  {|
    mutation AddTodo($text: String!) {
      todo: addTodoSimple(text: $text) {
        id
        completed
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
        completed
        text
      }
    }
  |}
];

[@react.component]
let make = () => {
  let (mutate, result) = AddTodoMutation.use();

  switch (result) {
  | {called: false} =>
    <>
      "Not called... "->React.string
      <button onClick={_ => mutate({text: "Another To-Do"})->ignore}>
        "Add To-Do"->React.string
      </button>
      " "->React.string
      <button
        onClick={_ =>
          mutate(
            ~optimisticResponse=
              _variables =>
                {
                  todo: {
                    __typename: "TodoItem",
                    id: "optimisticResponseTodo",
                    completed: None,
                    text: "To-Do from optimisticRespomse",
                  },
                },
            ~update=
              (cache, {data}) =>
                switch (data) {
                | Some({todo}) =>
                  /**
                   * Apollo docs use cache.modify, but it's not typesafe. I recommend some
                   * combination of readQuery / writeQuery / writeFragment
                   */
                  Js.log2("mutate.update To-Do: ", todo);
                  let _unusedRef =
                    cache->Cache.writeFragment(
                      ~fragment=(module Fragments.TodoItem),
                      ~data={
                        __typename: todo.__typename,
                        id: "fragmentToDo",
                        completed: None,
                        text: "To-Do from writeFragment",
                      },
                      (),
                    );
                  let _unusedRef =
                    cache->Cache.writeQuery(
                      ~query=(module TodosQuery),
                      ~data={
                        todos: [|
                          {
                            __typename: todo.__typename,
                            id: "writeQueryToDo",
                            completed: None,
                            text: "To-Do from writeQuery",
                          },
                        |],
                      },
                      (),
                    );
                  ();
                | None => ()
                },
            ~refetchQueries=[|
              TodosQuery.refetchQueryDescription(),
              // - OR -
              String("TodosQuery") // Should rarely be needed?
            |],
            {text: "Another To-Do"},
          )
          ->ignore
        }>
        "Add To-Do (all the bells and whistles)"->React.string
      </button>
    </>
  | {loading: true} => "Loading..."->React.string
  | {data: Some({todo: {text}}), error: None} =>
    <p> {React.string("To-Do added: \"" ++ text ++ "\"")} </p>
  | {error} =>
    <>
      "Error loading data"->React.string
      {switch (error) {
       | Some(error) => React.string(": " ++ error.message)
       | None => React.null
       }}
    </>
  };
};
